//
//  TC_ISR.c
//
//
//  Created by Henry Warhurst on 25/05/2015.
//
//
//  Part of the Pulsatio software package for the HCS12 Microcontroller.
//  Dragon-12 Plus.
//
//  Last modified: 03/06/15, added doc.

#include "TC_ISR.h"
#include "defines.h"
#include "global_vars.h"
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

static void incr_char_idx(void);

void incr_char_idx(void)  {
    if (char_idx < 3) {
        char_idx++;
    } else {
        char_idx = 0;
    }
}

interrupt 15 void TC7_ISR(void) {
    if (sev_seg_is_on) {
        PORTB = PORT_OFF;
        TC7 = TC7 + LO_TIME;
        sev_seg_is_on = 0;
        // Increment the character index
        incr_char_idx();
    } else if (!sev_seg_is_on) {
        PORTB = sev_seg_vals[char_idx];
        if (char_idx == 3 && dec_pt)
          PORTB += 0x80;
        PTP &= 0xF0;
        PTP = which_seg[char_idx];
        TC7 = TCNT + HI_TIME;
        sev_seg_is_on = 1;
    }
    TFLG1 |= 0x80;
}

interrupt 14 void TC6_ISR(void) {
    if (state == CALIBRATE && calib_cnt < calib_total_cnt) {
         TC6 = TCNT + 1000;
          calib_cnt++;
          return;
    }
    // Start a conversion sequence
    ATD1CTL5 = 0x82;
    
    // Trigger again in PERIOD_CYCLES seconds
    TC6 = TCNT + PERIOD_CYCLES;
}

interrupt 13 void TC5_ISR(void) {
    TC5 = TCNT + 200;
}


interrupt 12 void TC4_ISR(void) {
    // BE CAREFUL HERE WE ARE TURNING
    // OFF SOME TIMERS
    TIE = TIE_MASK;
}

interrupt 11 void TC3_ISR(void) {
    if (tc3_count < tc3_complete_count) {
        tc3_count++;
    } else {
        // Get rid of the decimal point
        dec_pt = 0;
        // Delay for 5 seconds next time
        tc3_complete_count = TC3_FIVE_SEC;
        tc3_count = 0;
        // Recalculate the BPM
        bpm = (beat_count*60)/5;
        disp_val = bpm;
        beat_count = 0;
    }
    TC3 = TCNT + TC3_DELAY_CYCLES;
}

void setup_timers(void) {
    TCTL1       = TCTL1_MASK;
    TSCR1       = TSCR1_MASK;
    TSCR2       = TSCR2_MASK;
    TIOS       |= TIOS_MASK;
    TIE         = TIE_MASK;
    TC7         = TCNT + LO_TIME;
    
    tc3_complete_count = TC3_FIVE_SEC;
}