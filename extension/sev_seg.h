/**
 \brief Functions related to the operation of the 7 segment display
 \file  sev_seg.h
 \author Henry Warhurst
 \version 1
 \date 03/06/15
 
 Last Modified: 03/06/15 by Henry Warhurst, added full doc.
 
 Code intended for the HCS12 Microcontroller. (Dragon-12 Plus)
 
 */

#ifndef _sev_seg_h
#define _sev_seg_h

/**
 \brief Sets up the 7segs for usage.
 \details Sets PORTB, PTP, PTJ to output and disables LEDs
 */
void setup_sev_seg(void);

/**
 \brief Extracts the 4 digits in the global variable disp_val
 \details Uses continued division by 10 to extract the 4 digits
            stored in the global variable disp_val. These
            extracted digits are stored into global array 
            sev_seg_vals.
 */
void extract_digits(void);

#endif
