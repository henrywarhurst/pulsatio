//
//  ATD_ISR.c
//
//
//  Created by Henry Warhurst on 17/05/2015.
//
//
//  Part of the Pulsatio software package for the HCS12 Microcontroller.
//  Dragon-12 Plus.
//
//  Last modified: 03/06/15, added doc.

#include "ATD_ISR.h"
#include "global_vars.h"
#include "defines.h"
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

unsigned int temp;
interrupt 23 void ATD0_ISR(void) {
    
    unsigned char idx1 = atd_cache_enqueue;
    atd_cache[atd_cache_enqueue] = ATD1DR0;
    // Increment cache enqueue index
    inc_atd_cache_enqueue();
    // to display on 7 seg
    if (state == CALIBRATE && calib_cnt >= calib_total_cnt) {
              temp = atd_cache[atd_cache_enqueue];
              offset_voltage = (temp/51)*1000;
              temp = (temp % 51)*10;
              offset_voltage += (temp/51)*100;
        
              PTM = 0x80; // Unshort the relay
              state = ON;
              tc3_count = 0;
              tc3_complete_count = TC3_THREE_SEC;
              disp_val = offset_voltage;
              beat_count = 0;
              dec_pt = 1;
    }   
}

void setup_atd(void) {
    ATD1CTL2 = 0xC2;  // 1100 0010
    //Maybe try waiting 20 us here
    ATD1CTL3 = 0x08;  // 0000 1000
    ATD1CTL4 = 0xEB;  // 1110 1011
    DDRM     = 0x80;
    PTM      = 0x80;
}

int diff;
int cur_grad;
unsigned char idx1;

void process_data(void) {

   if (state == CALIBRATE)
      return;
    
   idx1 = atd_cache_enqueue - 1;
   if (atd_cache_enqueue == 0) idx1 = ATD_BUFF_SIZE - 1; // Handle wrap around
   diff = atd_cache[idx1] 
            - atd_cache[atd_cache_enqueue];
   cur_grad = diff/ATD_BUFF_SIZE;
   if (cur_grad > grad_threshold && time_cnt > 1000) {
       // Turn on TC4 and TC5
       TIE |= 0x30;
       // Keep timer on for 0.2 seconds (128 prescale)
       TC5 = TCNT + 100; // Start the buzzing
       TC4 = TCNT + 37500; // To stop the buzzing
      
       beat_count++;
       time_cnt = 0;
   }
   time_cnt++;
}

void setup_speaker(void) {
   DDRT = SPEAKER_OUT;
}

void inc_atd_cache_enqueue(void) {
    if (atd_cache_enqueue < ATD_BUFF_SIZE - 1) {
        atd_cache_enqueue++;
    } else {
        atd_cache_enqueue = 0;
    }
}

void inc_atd_cache_dequeue(void) {
    if (atd_cache_dequeue < ATD_BUFF_SIZE - 1) {
        atd_cache_dequeue++;
    } else {
        atd_cache_dequeue = 0;
    }
}

