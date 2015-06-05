/**
 
 \brief Entry point into the Pulsatio ECG software package.
 \file  main.c
 \details Initiates program and loops indefinitely
 \date 03/06/15
 \author Henry Warhurst
 
 Last Modified: 03/06/15 by Henry Warhurst, added full documentation.
 
 Code intended for the HCS12 Microcontroller. (Dragon-12 Plus)
 
 */

#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */

#include "sev_seg.h"
#include "global_vars.h"
#include "defines.h"
#include "TC_ISR.h"
#include "ATD_ISR.h"
#include "SCI_ISR.h"

void main (void){
    EnableInterrupts;
    
    // Configure serial
    setup_serial();
    // Configure RGB LED
    DDRM = PORT_OUTPUT;
    PTM  |= PM3_ON;
    DDRP = PORT_OUTPUT;
    
    while(1) {
      extract_digits();
      process_data();
      read_data();
    }
}
