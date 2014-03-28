//******************************************************************************
//
//  Description: This file contains the Interrupt Routines for Timers
//               
//
//  Jim Carlson
//  Aug 2013
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (5.40.1)
//******************************************************************************

//------------------------------------------------------------------------------
#include  "msp430.h"
#include  "functions.h"
#include  "my_macros.h"

//------------------------------------------------------------------------------
//Globals Defined in interrupts_timers.c

// Used with Provided Compiled Code
// LEDs 
// GPS
// unsigned int gps_resetting;
// unsigned int gps_2b_reset;
// unsigned int reset_gps_time;
 volatile int time_pass_by;
// char transmit_delay;
// char transmit_time;

//Globals Defined in other files

// Used with Provided Compiled Code
// extern char *display_1;
// extern char *display_2;
// System info
// extern volatile unsigned char control_state[CNTL_STATE_INDEX];
// extern volatile unsigned int update_display_count;
// extern volatile unsigned int display_update_time;
// Time
// extern volatile unsigned int five_msec_count;
// extern volatile unsigned int sleeping;
// extern volatile char sleeptime;
// Serial
// extern volatile char slow_input_down;
// volatile unsigned char character_time_out;
extern volatile char switch_states;
extern volatile unsigned int count_debounce_SW1;
extern volatile unsigned int count_debounce_SW2;

//------------------------------------------------------------------------------

//******************************************************************************
//------------------------------------------------------------------------------
// TimerA0 0 Interrupt handler
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
  P3OUT ^= TEST_PROBE;

  if(switch_states & SW1_DEBOUNCE){
    count_debounce_SW1++;
    if(count_debounce_SW1 >= SOME_NUMBER_OF_MILLISECONDS){
      switch_states &= ~SW1_DEBOUNCE;
      enable_switch_SW1();
	}
  }
  
  if(switch_states & SW2_DEBOUNCE){
    count_debounce_SW2++;
    if(count_debounce_SW2 >= SOME_NUMBER_OF_MILLISECONDS){
      switch_states &= ~SW2_DEBOUNCE;
      enable_switch_SW2();
	}
  }
  
  TA0CCR0 += TA0CCR0_INTERVAL;         // Add Offset to TACCR0
}
//------------------------------------------------------------------------------
/*
//------------------------------------------------------------------------------
// TimerA0 1-2, Overflow Interrupt Vector (TAIV) handler
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_ISR(void){
  switch(__even_in_range(TA0IV,14)){
    case  0: break;                    // No interrupt
    case  2:                           // CCR1 not used
      TA0CCR1 += TA0CCR1_INTERVAL;     // Add Offset to TACCR1
      break;
    case  4:                           // CCR2 not used
      TA0CCR2 += TA0CCR2_INTERVAL;     // Add Offset to TACCR2
      break;
    case  6: break;                    // reserved
    case  8: break;                    // reserved
    case 10: break;                    // reserved
    case 12: break;                    // reserved
    case 14:                           // overflow
      break;
    default: break; 
  }
}
//------------------------------------------------------------------------------
*/
//******************************************************************************


//******************************************************************************

//------------------------------------------------------------------------------
// 
// 
// TimerA1 0 Interrupt handler
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void){
  TA1CCTL0 &= ~CCIE;                    // CCR0 Disable interrupt
  switch_control();
}
//------------------------------------------------------------------------------
/*
//------------------------------------------------------------------------------
// TimerA1 1-2, Overflow Interrupt Vector (TAIV) handler
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER1_A1_ISR(void){
  switch(__even_in_range(TA1IV,14)){
    case  0: break;                    // No interrupt
    case  2:                           // CCR1 not used
      TA1CCR1 += TA1CCR1_INTERVAL;     // Add Offset to TACCR1
      break;
    case  4:                           // CCR2 not used
      TA1CCR2 += TA1CCR2_INTERVAL;     // Add Offset to TACCR2
      break;
    case  6: break;                    // reserved
    case  8: break;                    // reserved
    case 10: break;                    // reserved
    case 12: break;                    // reserved
    case 14:                           // overflow
      break;
    default: break; 
  }
}
//------------------------------------------------------------------------------
*/
//******************************************************************************

//******************************************************************************
/*
//------------------------------------------------------------------------------
// TimerB0 0 Interrupt handler
#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
  TB0CCR0 += TB0CCR0_INTERVAL;         // Add Offset to TACCR0
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TimerB0 1-2, Overflow Interrupt Vector (TAIV) handler
#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(void){
  switch(__even_in_range(TB0IV,14)){
    case  0: break;                    // No interrupt
    case  2:                           // CCR1 
      TB0CCR1 += TB0CCR1_INTERVAL;     // Add Offset to TB0CCR1
      break;
    case  4:                           // CCR2 
      TB0CCR2 += TB0CCR2_INTERVAL;     // Add Offset to TB0CCR2
      break;
    case  6: break;                    // reserved
    case  8: break;                    // reserved
    case 10: break;                    // reserved
    case 12: break;                    // reserved
    case 14:                           // overflow
      break;
    default: break; 
  }
}
//------------------------------------------------------------------------------
*/
//******************************************************************************

//******************************************************************************
/*
//------------------------------------------------------------------------------
// TimerB1 0 Interrupt handler
#pragma vector=TIMER1_B0_VECTOR
__interrupt void Timer1_B0_ISR(void){
  TB1CCR0 += TB1CCR0_INTERVAL;         // Add Offset to TB1CCR0
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TimerB1 1-2, Overflow Interrupt Vector (TAIV) handler
#pragma vector=TIMER1_B1_VECTOR
__interrupt void TIMER1_B1_ISR(void){
  switch(__even_in_range(TB1IV,14)){
    case  0: break;                    // No interrupt
    case  2:                           // CCR1
      TB1CCR1 += TB1CCR1_INTERVAL;     // Add Offset to TB1CCR1
      break;
    case  4:                           // CCR2
      TB1CCR2 += TB1CCR2_INTERVAL;     // Add Offset to TB1CCR2
      break;
    case  6: break;                    // reserved
    case  8: break;                    // reserved
    case 10: break;                    // reserved
    case 12: break;                    // reserved
    case 14:                           // overflow
      break;
    default: break; 
  }
}
//------------------------------------------------------------------------------
*/
//******************************************************************************


//******************************************************************************
/*
//------------------------------------------------------------------------------
// TimerB2 0 Interrupt handler
#pragma vector=TIMER2_B0_VECTOR
__interrupt void Timer2_B0_ISR(void){
  TB2CCR0 += TB2CCR0_INTERVAL;         // Add Offset to TB1CCR0
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// TimerB2 1-2, Overflow Interrupt Vector (TAIV) handler
#pragma vector=TIMER2_B1_VECTOR
__interrupt void TIMER2_B1_ISR(void){
  switch(__even_in_range(TB2IV,14)){
    case  0: break;                    // No interrupt
    case  2:                           // CCR1
      TB2CCR2 += TB2CCR2_INTERVAL;     // Add Offset to TB1CCR1
      break;
    case  4:                           // CCR2
      TB2CCR2 += TB2CCR2_INTERVAL;     // Add Offset to TB1CCR2
      break;
    case  6: break;                    // reserved
    case  8: break;                    // reserved
    case 10: break;                    // reserved
    case 12: break;                    // reserved
    case 14:                           // overflow
      break;
    default: break; 
  }
}
//------------------------------------------------------------------------------
*/
//******************************************************************************

//------------------------------------------------------------------------------
