/**
 
 \brief A global file to define constants relevant to all modules.
 \file  defines.h
 \details Note that global variables are not defined here, we only use #define.
            Please see global_vars.h.
 \date 03/06/15
 \author Henry Warhurst
 
 Modifications:
 
 17/05/15 - Created file.
 25/05/15 - Added ATD defines.
 02/06/16 - Added TC3 ISR
 
 Code intended for the HCS12 Microcontroller. (Dragon-12 Plus)
 
 */

#ifndef _defines_h
#define _defines_h

// ****** Parallel I/O ******
// **************************
#define PORT_ON                 0xFF
#define PORT_OFF                0x00
#define PORT_OUTPUT             0xFF
#define PORT_INPUT              0x00

// ****** Timer *************
// **************************
#define TCTL1_MASK              0x04        // Enable toggle for TC5
#define TSCR1_MASK              0x90        // Enable timer and enable timer fast flag clear.
#define TSCR2_MASK              0x06        // Set timer prescale factor to 128.
#define TIOS_MASK               0xF8        // TC7, TC6, TC4, TC3, TC2. 1101 1100
#define TIE_MASK                0xC8        // TC7, TC6, TC3. 1100 1000
#define SECS_PER_MIN            60          // Number of seconds in a minute.
#define LO_TIME                 50          // How long to keep each 7seg off
#define HI_TIME                 1400        // How long to keep each 7seg on
#define TC7_FLG                 0x80
#define PRESCALER               128
#define TC3_THREE_SEC           30          // Number of times to enter the tc3 isr for a 3s delay
#define TC3_FIVE_SEC            50          // Number of times to entery the tc3 isr for a 5s delay
#define TC3_DELAY_CYCLES        18750       // Number of cycles to delay 0.1s (128 prescaler)

// ******* ATD **************
// **************************
#define ATD_BUFF_SIZE           5       // The size of the buffer storing the ATD data
#define SAMPLE_FREQ             300       // Sampling frequency in Hertz
#define PERIOD_CYCLES           (24000000/PRESCALER)/SAMPLE_FREQ // Period in between ATD samples
#define ATD_CTL2_MASK           0xC2      // 1100 0010.
#define ATD_CTL3_MASK           0x08      // 0000 1000.
#define ATD_CTL4_MASK           0xEB      // 1110 1011.



// ******* SCI **************
// **************************
#define ALL_ZEROS       0
#define BAUD_RATE       0x9C
#define SCI_CR1_MASK    0x00
#define SCI_CR2_MASK    0x88      // Enable transmission and TDRE interrupts
#define TDRE_MASK       0x80      // To clear the TDRE flag
#define RDRF_MASK       0x20      // Bit mask for RDR
#define OFF             0
#define ON              1
#define CALIBRATE       2
#define INPUT_BUFF_SIZE 64        // Buffer for holding input

// ****** MISC **************
// **************************
#define SPEAKER_OUT     0x20      // Sets PT5 as output

#endif
