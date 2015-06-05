//
//  global_vars.c
//
//
//  Created by Henry Warhurst on 25/05/2015.
//
//
//  Part of the Pulsatio software package for the HCS12 Microcontroller.
//  Dragon-12 Plus.
//
//  Last modified: 03/06/15, added doc.

#include "global_vars.h"
#include "defines.h"

 unsigned char              sev_seg_is_on = 0;
 unsigned char              sev_seg_vals[4];
 unsigned char              char_idx = 0;
 unsigned int               update_per;
 unsigned int               sample_count;
 unsigned int               beat_count;
 unsigned int               tc3_count = 0;
 unsigned int               tc3_complete_count;
 unsigned int               time_cnt = 0;
 unsigned int              calib_cnt;
 unsigned int              calib_total_cnt;
 unsigned int               bpm;
 unsigned char              new_line = 0;
 unsigned char              cur_dat;
 unsigned char              new_dat;
 unsigned int              offset_voltage;
 unsigned char              dec_pt;
 const unsigned char        grad_threshold = 9;
 const unsigned char        height_threshold = 80;
 unsigned int               divisor;
 unsigned int               disp_val;
 unsigned char              newline = 0;
 unsigned char              atd_cache[ATD_BUFF_SIZE];
 unsigned int               atd_cache_enqueue = 0;
 unsigned int               atd_cache_dequeue = 0;
 
 unsigned char              input_buff[INPUT_BUFF_SIZE];
 unsigned char              in_idx = 0;
 unsigned char              out_idx = 0;
 
 unsigned char              new_data = 1;
 
 unsigned char              state;                       //machine start in OFF state
 const unsigned char        power_off_message[] = "\nMachine is powered off\n\rPress 'p' to power on\n\r#";
 const unsigned char        power_on_message[] = "\nWelcome to Pulsatio\n\rPress 'h' to display help message\n\r#" ;
 const unsigned char        calibrate_message[] = "\nCalibrating...\n\r#" ;
 const unsigned char        help_message[] = "\nPress 'c' to calibrate\n\rPress 'p' to power off\n\rPress 'h' to display help message\n\r#";  

int transmitInProgress = 0;
unsigned char transmitBuffer[100];
int transmitIndex = 0;                //point to the char to be transmitted in transmitBuffer
int receiveIndex = 0;                 //point to where in transmitQueueIndex the next string should be stored
unsigned char* transmitQueue[30];
int transmitQueueIndex = 0;           //point to the next string in transmitQueue to be stored in transmitBuffer
int queueSize = 30;
int firsttransmit = 1;

 const unsigned char lookup[16] = {
        0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F,
        0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
 };

 const unsigned char which_seg[4] = {
        7, 11, 13, 14
 };



