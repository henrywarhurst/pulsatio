/**
 \brief Interrupt for serial.
 \details Used to send data over serial to a terminal.
 \file  SCI_ISR.h
 \author Isky Yi
 \date 25/05/15
 
 Modifications:
 
 25/05/15 - File created.
 
 Code intended for the HCS12 Microcontroller. (Dragon-12 Plus)
 
 */

#ifndef ____SCI_ISR__
#define ____SCI_ISR__

//********* Functions for transmitting ATD data over serial 
 
///**
// \brief Triggers when TDRE or RDRF triggers.
//\details When RDRF triggers, this interrupt reads data into input buffer. When TDRE triggers, this interrupt sends a character from transmission buffer.
// */
//interrupt 21 void SCI_ISR(void);

/**
 \brief Setup serial registers
 \details Sets up serial to trigger interrupts when TDRE is ready
 */
 //void setup_serial(void);
 
 // **********************************************************
 
 // **************** Regular serial functions ****************
 /*
 \brief Triggers when TDRE or RDRF triggers.
  \details When RDRF triggers, this interrupt reads data into input buffer. When TDRE triggers, this interrupt sends a character from transmission buffer.
 */ 
interrupt 21 void Serial_ISR(void);

void setup_serial(void);
 
void power_on(void);
void power_off(void);
void calibrate(void);
void transmit(unsigned char string[]);

/*
\brief Reads data from the input serial buffer, if data is available.
\details Reads data that has been stored into an input circular buffer (A.K.A. a queue).
*/
void read_data(void);
 
 


#endif /* defined(____SCI_ISR__) */
