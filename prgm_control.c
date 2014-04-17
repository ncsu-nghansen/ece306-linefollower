#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"


volatile int LeftMotorPower = 0;
volatile int RightMotorPower = 0;
int ProgramState = 0;
int OldState = -1;
volatile int StateTransitions = 0;

char IsLight = 1;
char WasLight = 1;

void Control_Process(void)
{
	if(ADC_Thumb > 200)  //Disables motors while calibrating
	{
		LeftMotorPower = 0;
		RightMotorPower = 0;
		MotorTimer = 0;
                SecTimer = 180;
		
		//          "0123456789abcdef"   
		display_2 = "Motors  Disabled";
		
		return;
	}

	if(MotorTimer == 0)
	{
		if(IsRightIrLight() && IsLeftIrLight()) //Quickly turn left when off line
			RightMotorPower = 100, LeftMotorPower = 0, display_2 = "       Light    ", display_1 = "       Light    ";
		if(IsRightIrLight() && !IsLeftIrLight()) //Slowly turn left when on edge
			RightMotorPower = 80, LeftMotorPower = 50, display_2 = "       Light    ", display_1 = "       Dark     ";
		if(!IsRightIrLight() && !IsLeftIrLight()) //Slowly turn right when on line
			RightMotorPower = 50, LeftMotorPower = 80, display_2 = "       Dark     ", display_1 = "       Dark     ";
		if(!IsRightIrLight() && IsLeftIrLight()) //Quickly turn right when on far edge
			RightMotorPower = 0, LeftMotorPower = 100, display_2 = "       Dark     ", display_1 = "       Light    ";

		MotorTimer = 1;
	}
		
	if(SecTimer == 90)  //If need to turn around
	{
		SecTimer--;
		timedSpinCW(2000);
	}
        
	if(SecTimer == 0)
	{
		RightMotorPower = 0;
		LeftMotorPower = 0;
	}
}