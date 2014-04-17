/******************************************************************************
Timer Configuration

DESC: Contains methods serves to set up a timer based in a precompiled file

GLOBALS: None

Nathan Hansen, 7 Feb 2014, Built with IAR Embedded Workbench Version: 5.60.5
******************************************************************************/

#include  "functions.h"
#include  "macros.h"
#include  "msp430.h"

volatile unsigned int TimeMsec = 0;
volatile unsigned int TimeUsec = 0;
volatile unsigned int CommTimer = 0;
volatile unsigned int MotorTimer = 0;
volatile unsigned int DebounceTimer = 0;
volatile unsigned int SecTimer = 0;

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{
	P3OUT ^= TEST_PROBE;
        
	TimeMsec++;
        
	if(MotorTimer > 0)
		MotorTimer--;
	if(DebounceTimer > 0)
		DebounceTimer--;
	if(CommTimer > 0)
		CommTimer--;
        if(SecTimer > 0 && TimeMsec % 1000 == 0)
                SecTimer--;
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0(void)
{
        TimeUsec += 100;
}

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