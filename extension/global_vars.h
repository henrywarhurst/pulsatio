/**
 
 \brief Stores global variables to be accessed throughout this piece of software.
 \file  global_vars.h
 \details Stores global variables used throughout the ECG program for the HCS12
 microcontroller.
 \date 17/05/15
 \author Henry Warhurst
 
 Last Modified: 03/06/15 by Henry Warhurst, added full documentation.
 
 Code intended for the HCS12 Microcontroller. (Dragon-12 Plus)
 
 */
#ifndef _global_vars_h
#define _global_vars_h

#include "defines.h"

//! Used to determine whether we should turn a 7seg display on or off
extern unsigned char sev_seg_is_on;
//! Stores the 4 characters to be sent to the 7 seg.
extern unsigned char sev_seg_vals[4];
//! Tells us which char in sev_seg_vals we are up to
extern unsigned char char_idx;
//! How often should we re-calculate the BPM based on the beat count (in seconds)
extern unsigned int update_per;
//! Calculates how many times we have sampled since the last reset of beat_count
extern unsigned int sample_count;
//! Counts how many beats have occured since the last reset of beat count
extern unsigned int beat_count;
//! Counts how many times we have gone into the tc3 interrupt since the last refresh of this value
extern unsigned int tc3_count;
//! Number of cycles in a 3 or 5 second delay
extern unsigned int tc3_complete_count;
//! Stops us triggering a beat too soon after another one
extern unsigned int time_cnt;
//! Stores the current beats per minute
extern unsigned int bpm;
//! How long have we been delaying for clibration
extern unsigned int calib_cnt;
//! How long should we be delaying for calibration
extern unsigned int calib_total_cnt;
//! Offset voltage 
extern unsigned int offset_voltage;
//! Should we display a decimal point?
extern unsigned char dec_pt;
//! The gradient threshold used in signal processing
extern const unsigned char grad_threshold;
//! The threshold voltage for peak height used in signal processing
extern const unsigned char height_threshold;
//! Used for extracting the digits from a decimal number
extern unsigned int divisor;
//! Value to be displayed on the 7seg
extern unsigned int disp_val;
//! Whether to send disp_val over serial or a new line
extern unsigned char new_line;
//! The current byte of ATD data
extern unsigned char cur_dat;
//! Is new ATD data available
extern unsigned char new_dat;
//! Maps values (0 --> A) to their equivalent 7 seg values.
extern const unsigned char lookup[16];
//! Controls which 7 seg is active
extern const unsigned char which_seg[4];
//! Caches the last few ATD readings (in a circular buffer).
extern unsigned char atd_cache[ATD_BUFF_SIZE];
//! The index to add things to the atd buffer
extern unsigned int atd_cache_enqueue;
//! The index to remove things from the atd buffer
extern unsigned int atd_cache_dequeue;
//! Stores the input from serial
extern  unsigned char input_buff[INPUT_BUFF_SIZE];
//! Enqueue index to input_buff
extern unsigned char in_idx;
//! Dequeue index to input_buff
extern unsigned char out_idx;
//! Do we have new ATD data to read
extern unsigned char new_data;
//! machine start in OFF state
extern unsigned char state;                       
extern const unsigned char power_off_message[49];
extern const unsigned char power_on_message[58];
extern const unsigned char calibrate_message[18];
extern const unsigned char help_message[85];  

extern int transmitInProgress;
extern unsigned char transmitBuffer[100];
//! Point to the char to be transmitted in transmitBuffer
extern int transmitIndex;                
//! Point to where in transmitQueueIndex the next string should be stored
extern int receiveIndex;                 
extern unsigned char* transmitQueue[30];
//! Point to the next string in transmitQueue to be stored in transmitBuffer
extern int transmitQueueIndex;           
extern int queueSize;
extern int firsttransmit;



#endif
