/******************************************************************************
LED.c

DESC: This file contains a method that initializes the LEDs

GLOBALS: None

Nathan Hansen, Feb 2014, Built with IAR Embedded Workbench Version: 5.60.5
******************************************************************************/

#include  "functions.h"
#include  "macros.h"
#include  "msp430.h"

//Init_LEDs
//
//DESC: LED drive pins are all set to zero using macros for the addresses. Half are 
//on Port3 and half on PortJ
//ARGS: None
//RET: None
void Init_LEDs(void)
{
  PJOUT &= ~LED1;
  PJOUT &= ~LED2;
  PJOUT &= ~LED3;
  PJOUT &= ~LED4;
  
  /*P3OUT &= ~LED5;
  P3OUT &= ~LED6;
  P3OUT &= ~LED7;
  P3OUT &= ~LED8;*/
}
