/******************************************************************************
Timer Configuration

DESC: Contains methods serves to set up a timer based in a precompiled file

GLOBALS: None

Nathan Hansen, 7 Feb 2014, Built with IAR Embedded Workbench Version: 5.60.5
******************************************************************************/

#include  "functions.h"
#include  "macros.h"
#include  "msp430.h"

void Init_Timers(void)
{
	//Init_Timer_A0(); //
	//Init_Timer_A1(); //
	//Init_Timer_B0(); //
	//Init_Timer_B1(); //
	Init_Timer_B2();   //  Required for provided compiled code to work
}

void waitMsec(int time)
{
	int lastTime = TimeMsec, timeElapsed = RESET_TIME;
	
	while(timeElapsed < time)
	{
		if(lastTime != TimeMsec)
		{
			timeElapsed++;
			lastTime = TimeMsec;
		}
	}
}