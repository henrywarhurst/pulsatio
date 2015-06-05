/** 
 \brief Interrupts for all timer channels
 \details We use Timers 3, 4, 5, 6, 7 (all in Output Compare mode)
 \file  TC_ISR.h
 \author Henry Warhurst
 \version 1
 \date 03/06/15
 
 Last Modified: 03/06/15 by Henry Warhurst, added full doc.
 
 Code intended for the HCS12 Microcontroller. (Dragon-12 Plus)
 
 */

#ifndef _TC7_ISR_h
#define _TC7_ISR_h

/**
    \brief Controls the refresh rate of the 7 segs.
    \details Uses global variable hi_or_lo and assumes a timer
             clock prescaler of 128.
 */
interrupt 15 void TC7_ISR(void);

/**
 \brief Starts an ATD conversion sequence every 1/SAMPLE_FREQ seconds
 */
interrupt 14 void TC6_ISR(void);

/**
 \brief Controls frequency of the buzzer
 */
interrupt 13 void TC5_ISR(void);

/**
  \brief Stops the speaker from being on
  */
interrupt 12 void TC4_ISR(void);

/**
 \brief Controls the 3 sec calibration delay and the window over which
        to calculate the BPM
 */
interrupt 11 void TC3_ISR(void);

/**
 \brief Sets timer registers.
 \details Enables interrupts on all timer channels except TC5.
 */
void setup_timers(void);


#endif
