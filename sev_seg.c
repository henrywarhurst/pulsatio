#include "sev_seg.h"
#include "defines.h"
#include "global_vars.h"
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

void setup_sev_seg() {
    // Ports B, J, and P are all output
    DDRB    = PORT_OUTPUT;
    DDRJ    = PORT_OUTPUT;
    DDRP    = PORT_OUTPUT;
    // Disable the LEDs
    PTJ     = PORT_ON;
}

void extract_digits() {
    
    unsigned int divisor = 1000;
    unsigned char i = 0;
    unsigned char temp = 0;
    unsigned int local_val = disp_val;
    
    if (state == CALIBRATE) {
        for (i=0; i<4; i++) {
           sev_seg_vals[i] = 0;
        }
        return;
    }
    
    for (i=0; i<4; ++i) {
        temp = local_val/divisor;
        sev_seg_vals[3-i] = lookup[temp];
        local_val %= divisor;
        divisor /= 10;
    }
}
