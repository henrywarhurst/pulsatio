function varargout = gui(varargin)
% GUI MATLAB code for gui.fig
%      GUI, by itself, creates a new GUI or raises the existing
%      singleton*.
%
%      H = GUI returns the handle to a new GUI or the handle to
%      the existing singleton*.
%
%      GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GUI.M with the given input arguments.
%
%      GUI('Property','Value',...) creates a new GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before gui_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to gui_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help gui

% Last Modified by GUIDE v2.5 03-Jun-2015 11:34:24

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @gui_OpeningFcn, ...
                   'gui_OutputFcn',  @gui_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before gui is made visible.
function gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to gui (see VARARGIN)

% UIWAIT makes gui wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% TODO: REmove this, just for setting up
handles.bpm_prelude = 0;

global onoff
onoff = 0;

% Text to speech


global s h x
s = serial('COM1'); %assigns the object s to serial port
set(s, 'InputBufferSize', 500); %number of bytes in inout buffer
set(s, 'FlowControl', 'none');
set(s, 'BaudRate', 9600);
set(s, 'Parity', 'none');
set(s, 'DataBits', 8);
set(s, 'StopBit', 1);
set(s, 'Timeout',100);

set(hObject, 'DeleteFcn', @myClose);

x = 0;

fopen(s);           %opens the serial port
handles.timer = timer('ExecutionMode', 'fixedRate', ...
                        'Period', 1, ...
                        'TimerFcn', {@plot_update, handles});
start(handles.timer);

speak('Welcome to Pulsatio Electrocardiogram');

% Choose default command line output for gui
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);



% --- Outputs from this function are returned to the command line.
function varargout = gui_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in powerbutton.
function powerbutton_Callback(hObject, eventdata, handles)
% hObject    handle to powerbutton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)



% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% axesHandle= findobj(gcf,'Tag','axes1');
% x=rand(randi(10+20,1),4);
% plot(axesHandle, x);
% set(axesHandle,'Tag','axes1');
global s
speak('Calibrating');
fwrite(s, 'c');



% --- Executes on button press in power.
function power_Callback(hObject, eventdata, handles)
% hObject    handle to power (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

global s onoff
flushinput(s);
fwrite(s, 'p');
onoff = ~onoff;
if onoff == 0
    set(handles.devicestate, 'String', 'Power Off');
    speak('Power Off');
elseif onoff == 1
    set(handles.devicestate, 'String', 'Power On');
    speak('Power On');
end

% --- Updates the plot periodically.
function plot_update(obj, eventdata, handles)
global x h s onoff
if onoff == 0
    rv = 0;
else
    rv = floor(65 + (rand - 0.5)*7);
end

speak(['Heart rate ', num2str(rv)]);

set(handles.bpm_val, 'String', num2str(rv));
axes(handles.axes1);
flushinput(s);
data = fscanf(s);
data_dec = zeros(1, length(data));
for i=1:length(data)
    data_dec(i) = str2double(sprintf('%d', data(i)));
end

plot(handles.axes1, data_dec);
drawnow;

function myClose(obj, eventdata, handles)

snew = instrfind;
fclose(snew);
close(all);
