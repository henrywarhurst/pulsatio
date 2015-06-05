/**
 \brief Analogue to digital conversion complete ISR
 \file  ATD_ISR.h
 \author Henry Warhurst
 \version 1
 \date 03/06/15
 
 Modifications:
 
 02/06/15 - Modified algorithm in process_data()
 
 Code intended for the HCS12 Microcontroller. (Dragon-12 Plus)
 
 */

#ifndef ____ATD_ISR__
#define ____ATD_ISR__

/**
 \brief ATD0 ISR - triggers when a conversion sequence is complete.
 \details We read data from the ATD0DR0 register in this int
 */
interrupt 23 void ATD0_ISR(void);

/**
 \brief Sets up ATD0 to trigger interrupts
 \details Writes to necessary registers to get ATD0 to trigger interrupts
          when a conversion sequence is complete.
 */
void setup_atd(void);

/**
 \brief Determines whether or not a beat has occurred
 \details Processes last chunk of data to determine whether or not a beat
          has been detected. If a beat is detected, add 1 to the global beat
          count and initiate a 'beep' on PT5.
*/
void process_data(void);

/**
\brief Sets up speaker (PT5) for output
\details Sets PT5 as output
*/
void setup_speaker(void);

/**
 \brief Increments atd_cache_enqueue (with wraparound)
 \details If atd_cache_enqueue is not at the end of atd_cache
            then it is simply incremented, otherwise it is
            set back to 0.
 */
void inc_atd_cache_enqueue(void);

/**
 \brief Increments atd_cache_dequeue (with wraparound)
 \details If atd_cache_dequeue is not at the end of atd_cache
 then it is simply incremented, otherwise it is
 set back to 0.
 */
void inc_atd_cache_dequeue(void);

#endif /* defined(____ATD_ISR__) */
