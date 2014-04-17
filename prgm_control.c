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

#define OFF_RIGHT (0)
#define RIGHT_EDGE (1)
#define CENTER (2)
#define LEFT_EDGE (3)
#define OFF_LEFT (4)

void Control_Process(void)
{
	if(ADC_Thumb > 200)  //Disables motors while calibrating
	{
		LeftMotorPower = 0;
		RightMotorPower = 0;
		MotorTimer = 0;
                SecTimer = 120;
		
		//          "0123456789abcdef"   
		display_2 = "Motors  Disabled";
		
		return;
	}

	/*if(MotorTimer == 0)
	{
		if(IsRightIrLight() && IsLeftIrLight()) //Semi-Quickly turn left when off line
			RightMotorPower = 40, LeftMotorPower = 0, display_2 = "       Light    ", display_1 = "       Light    ";
		if(IsRightIrLight() && !IsLeftIrLight()) //Slowly turn left when on edge
			RightMotorPower = 40, LeftMotorPower = 40, display_2 = "       Light    ", display_1 = "       Dark     ";
		if(!IsRightIrLight() && !IsLeftIrLight()) //Slowly turn right when on line
			RightMotorPower = 30, LeftMotorPower = 80, display_2 = "       Dark     ", display_1 = "       Dark     ";
		if(!IsRightIrLight() && IsLeftIrLight()) //Quickly turn right when on far edge
			RightMotorPower = 0, LeftMotorPower = 100, display_2 = "       Dark     ", display_1 = "       Light    ";
	}*/
        
        switch(ProgramState)
        {
          case OFF_RIGHT:
            if(IsRightIrLight() && !IsLeftIrLight())
              ProgramState = RIGHT_EDGE;
            break;
            
          case RIGHT_EDGE:
            if(IsRightIrLight() && IsLeftIrLight())
              ProgramState = OFF_RIGHT;
            if(!IsRightIrLight() && !IsLeftIrLight())
              ProgramState = CENTER;
            break;
            
          case CENTER:
            if(IsRightIrLight() && !IsLeftIrLight())
              ProgramState = RIGHT_EDGE;
            if(!IsRightIrLight() && IsLeftIrLight())
              ProgramState = LEFT_EDGE;
            break;
            
          case LEFT_EDGE:
            if(!IsRightIrLight() && !IsLeftIrLight())
              ProgramState = CENTER;
            if(IsRightIrLight() && IsLeftIrLight())
              ProgramState = OFF_LEFT;
            break;
            
          case OFF_LEFT:
            if(!IsRightIrLight() && IsLeftIrLight())
              ProgramState = LEFT_EDGE;
            break;            
        }
        
        if(MotorTimer == 0)
        {
          MotorTimer = 1;
          
          switch(ProgramState)
          {
          case OFF_RIGHT:
            RightMotorPower = 100, LeftMotorPower = 0,   display_2 = " Off Right Side ";
            break;
            
          case RIGHT_EDGE:         
          case CENTER:
          case LEFT_EDGE:
            RightMotorPower = 80, LeftMotorPower = 80,   display_2 = "     On Line    ";
            break;
            
          case OFF_LEFT:
            RightMotorPower = 0, LeftMotorPower = 100,   display_2 = "  Off Left Side ";
            break;
          }
        }
		
	if(SecTimer == 60)  //If need to turn around
	{
		SecTimer--;
		timedSpinCW(1000);
	}
        
	if(SecTimer == 0)
	{
		RightMotorPower = 0;
		LeftMotorPower = 0;
	}
}