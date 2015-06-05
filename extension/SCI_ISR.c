//
//  SCI_ISR.c
//  
//
//  Created by Isky Yi and Henry Warhurst on 25/05/2015.
//
//

#include "SCI_ISR.h"
#include "ATD_ISR.h"
#include "global_vars.h"
#include "defines.h"
#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */


/***** Functions for transmitting atd data over serial ************** 
interrupt 21 void SCI_ISR(void) {
    unsigned char temp;
    // At this stage we assume only TDRE interrupts are being triggered
    
    // Nothing to transmit
    //if (atd_cache_enqueue == atd_cache_dequeue)
       //return;
    
    //atd_cache[atd_cache_dequeue] = SCI1DRL;
    // Increment the dequeue index
    //inc_atd_cache_dequeue();
    // TODO: REmove the followiung section eventually
    if (newline) {
      SCI1DRL = 10; // LF dec code
      newline = 0;
    } else {
      SCI1DRL = disp_val;
      newline = 1;
    }
    // Clear the TDRE flag
    temp = SCI1SR1;
}

void setup_serial(void) {
  SCI1BDH = ALL_ZEROS;
  SCI1BDL = BAUD_RATE;
  SCI1CR1 = SCI_CR1_MASK;
  SCI1CR2 = SCI_CR2_MASK;  
}

************************************************************/

interrupt 21 void Serial_ISR(void) 
{
      //*****TDRE triggered interrupt*****
     if(((SCI1SR1&TDRE_MASK) != 0)&&((SCI1SR1&RDRF_MASK) == 0) )
     {    
          //if (new_dat == 0) return;
          
            // Transmit current atd data over serial
          SCI1DRL = cur_dat;
          new_dat = 0;
          
          // Disable TDRE interrupt 
          //SCI1CR2 &= ~(1 << 3);  
     }
      //*****RDRF triggered interrupt*****
     else if((SCI1SR1&RDRF_MASK) != 0)
     {    
          input_buff[in_idx] = SCI1DRL;
          // Increment using circular buff
          if (in_idx != INPUT_BUFF_SIZE - 1) {
            in_idx++;
          } else {
            in_idx = 0;
          }

     }
 }
 
void read_data(void) {
    if (in_idx != out_idx) {
        unsigned char cur_char = input_buff[out_idx];
             if(state == ON)
         {
              if(cur_char == 'p')
              {       //if user input 'p'  (power off)    
                    power_off();       
              } 
              else if(cur_char == 'c') 
              {  //if user input 'c' (calibrate)
                    calibrate();  
              } 
              else if(cur_char == 'h')
              {   //if user input 'h' (help)
                    transmit(help_message);        
              }    
         } 
         else if(state == OFF)
         {
              if(cur_char == 'p')
              {
                    power_on();
              }
         } 
         else if(state == CALIBRATE) 
         {
              if(cur_char == 'p')
              {
                    power_off();
              }
         }
         // Circular buffer increment
         if (out_idx != INPUT_BUFF_SIZE - 1) {
            out_idx++;
         } else {
            out_idx = 0;
         }
    }
}
 
 //check if there is transmission in progress
//if not, turn on TIE to go into serial ISR immediately because TDRE is already set to 1
void transmit(unsigned char string[])
{
       transmitQueue[receiveIndex] = string;

       if(receiveIndex == queueSize)
       {
                 receiveIndex = 0;
       }
       else
       {
                 receiveIndex++;
       }

       if(transmitInProgress == 0)
       {
                 strncpy ( transmitBuffer, transmitQueue[transmitQueueIndex], sizeof(help_message));
                 transmitInProgress = 1;
                 SCI1CR2 = 0xAC;     //turn on TIE(TDRE interrupt enable)
       }
       
       
       if(firsttransmit == 1) 
       {
               //transmitIndex++;
               firsttransmit = 0;
               SCI1DRL = string[0];
       }                             
}
 
 void power_on(void){    

        transmit(power_on_message);

        // Configure 7 seg
        setup_sev_seg();
        // Configure timers
        setup_timers();
        // Configure analogue to digital converter.
        setup_atd();
        
        calibrate();
        // We are in calibrate state
        PTP &= 0x0F;
        PTP = ~(CALIB_LED);
}

void setup_serial(void) {
       SCI1BDL = BAUD_RATE;//set baud rate to 9600
       SCI1BDH = ALL_ZEROS;  //devisor is 156
       SCI1CR2 = 0x2C;//enable transmitter, receiver, disable TDRE interrupt, enable RDRF interrupt

       firsttransmit = 1;
       transmitIndex = 0;
       receiveIndex = 0;
       transmitQueueIndex = 0;
       queueSize = 30;
       transmitInProgress = 0;
       
       power_off(); // Start machine in off state
}

void power_off(void){

       transmit(power_off_message);
       state = OFF;
       //PORTE = 0x00;    //PE6 relay is off
       //TSCR1 = 0x00; //disable timer
       //ATD1CTL2 = 0x00; //ADC power down
          
       TIE &= 0;
       PTP = 0xFF;
         
}

void calibrate(void){

       transmit(calibrate_message);

       state = CALIBRATE;
       
       PTM      = 0x00; // Short the relay
       calib_cnt = 0;
       calib_total_cnt = 20;
}  
