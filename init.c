/******************************************************************************
 Initializations Configurations
 Currently, just enables interrupts

 No globals used
******************************************************************************/

#include  "functions.h"
#include  "macros.h"
#include  "msp430.h"

//Init_Conditions
//
//DESC: Calls a precompiled method that enables interrupts
//ARGS: None
//RET: None
void Init_Conditions(void)
{
	enable_interrupts(); // Interrupts are disabled by default, this enables them 
}

