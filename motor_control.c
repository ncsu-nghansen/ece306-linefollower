/******************************************************************************
Main

DESC: This file contains the Main Routine - "While" Operating System

GLOBALS: Last_SW1_State and Last_SW2_State are defined;
display_1 and display_2 are changed

Nathan Hansen, Feb 2014, Built with IAR Embedded Workbench Version: 5.60.5
******************************************************************************/


//Include Statements
#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

void Motors_Process(void)
{
	if(MotorTimer <= RESET_TIME)
	{
		allStop();
		return;
	}

	allStop();
	
	if(LeftMotorPower > 0)
		if(TimeMsec % MAX_POWER < LeftMotorPower)
			leftForward();
        if(LeftMotorPower < 0)
		if(TimeMsec % MAX_POWER < -LeftMotorPower)
			leftReverse();
	
	if(RightMotorPower > 0)
		if(TimeMsec % MAX_POWER < RightMotorPower)
			rightForward();
	if(RightMotorPower < 0)
		if(TimeMsec % MAX_POWER < -RightMotorPower)
			rightReverse();
	

	/*	
	leftReverse();
	for(int i = 0; LeftMotorPower < 0 && i < -LeftMotorPower; i++);          
	allStop();
	
	rightForward();
	for(int i = 0; RightMotorPower >= 0 && i < RightMotorPower; i++);
	allStop();
	
	rightReverse();
	for(int i = 0; RightMotorPower < 0 && i < -RightMotorPower; i++);  
	allStop();
        
	unsigned int LastMsec = TimeMsec;
	for(int i = RESET_TIME; TimeMsec == LastMsec; i++)
	{
		if(LeftMotorPower > OFF_POWER && (i%MAX_POWER) < LeftMotorPower)
			leftForward();
		else if(LeftMotorPower < OFF_POWER && (i%MAX_POWER) < -LeftMotorPower)
			leftReverse();
			
		if(RightMotorPower > OFF_POWER && (i%MAX_POWER) < RightMotorPower)
			rightForward();
		else if(RightMotorPower < OFF_POWER && (i%MAX_POWER) < -RightMotorPower)
			rightReverse();	
	}*/	
	
        //if(TimeMsec != LastMsec)
        //  MotorTimer--;	
}

void leftForward(void)
{
	leftStop(); //Zero L_Reverse first
	P3OUT |= L_FORWARD;  //Then set L_Forward
}

void leftReverse(void)
{
	leftStop(); //Zero L_Forward first
	P3OUT |= L_REVERSE;  //Then ser L_Reverse
}

void rightForward(void)
{
	rightStop(); //Zero R_Reverse first
	P3OUT |= R_FORWARD;  //Then set R_Forward
}

void rightReverse(void)
{
	rightStop(); //Zero R_Forward first
	P3OUT |= R_REVERSE;  //Then set R_Reverse
}

void rightStop(void)
{
	P3OUT &= ~R_FORWARD;
	P3OUT &= ~R_REVERSE;
}

void leftStop(void)
{
	P3OUT &= ~L_FORWARD;
	P3OUT &= ~L_REVERSE;
}

void allStop(void)
{
	leftStop();
	rightStop();
}

void timedForward(int time)
{
	MotorTimer = time;
	LeftMotorPower = LPOWER;
	RightMotorPower = RPOWER;
}

void timedReverse(int time)
{
	MotorTimer = time;
	LeftMotorPower = -LPOWER;
	RightMotorPower = -RPOWER;
}

void timedLeft(int time)
{
	MotorTimer = time;
	LeftMotorPower = OFF_POWER;
	RightMotorPower = RPOWER;
}

void timedRight(int time)
{
	MotorTimer = time;
	LeftMotorPower = LPOWER;
	RightMotorPower = OFF_POWER;
}

void timedSpinCW(int time)
{
	MotorTimer = time;
	LeftMotorPower = LPOWER;
	RightMotorPower = -RPOWER;
}

void timedSpinCCW(int time)
{
	MotorTimer = time;
	LeftMotorPower = -LPOWER;
	RightMotorPower = RPOWER;
}

void circleCW(void)
{
	MotorTimer = CIRCLE_CW_TIME;
	LeftMotorPower = LPOWER;
	RightMotorPower = RPOWER/CIRCLE_DIV;
}

void circleCCW(void)
{
	MotorTimer = CIRCLE_CCW_TIME;
	LeftMotorPower = LPOWER/CIRCLE_DIV;
	RightMotorPower = RPOWER;
}

void figureEight(void)
{
	circleCW();
	circleCCW();
}

void triangle(void)
{
	for(int i = RESET_0; i < TRI_SIDES; i++)
	{
		timedForward(TRI_TIME);   
		timedLeft(TURN_60);
		timedForward(TRI_TIME);
	}
}