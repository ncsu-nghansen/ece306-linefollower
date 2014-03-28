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


// Shared Globals
//char *display_1; now specified in functions.h and defined in LCD
//char *display_2; now specified in functions.h and defined in LCD

volatile char Last_SW1_State = NOT_PRESSED;
volatile char Last_SW2_State = NOT_PRESSED;

volatile int ADC_Thumb = 0;
volatile int ADC_LeftIR = 0; 
volatile int ADC_RightIR = 0;
char IsLight = 1;
char WasLight = 1;

int AdcChannel = ADC10INCH_0;

volatile int MotorTimer = 0;
volatile int LeftMotorPower = LPOWER;
volatile int RightMotorPower = RPOWER;
volatile int ProgramState = 0;
volatile int OldState = -1;
volatile int StateTransitions = 0;


// Global Variables
volatile unsigned char control_state[CNTL_STATE_INDEX];
volatile unsigned int TimeUsec = RESET_TIME, TimeMsec = RESET_TIME, Time_Sequence = RESET_TIME;
char led_smclk;
volatile char one_time;



//******************************************************************************
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
//******************************************************************************

void main(void)
{
	Init_Ports();                             // Initialize Ports
	Init_Clocks();                            // Initialize Clock System 
	Init_Conditions();
	Init_Interrupts();
       
	//PJOUT |= LED1;                          // Turn LED 1 on to indicate boot
	  
	TimeMsec = RESET_TIME;
	Init_Timers(); 				// Initialize Timers
	Init_LCD();				// Initialize LCD
	//Init_LEDs();                            // Initialize LEDs       
        
        
        
	//          "0123456789abcdef"
	display_1 = "   PROJECT  5   ";
	display_2 = "                ";
	Display_Process();
	
	P1OUT |= IR_LED;
	waitMsec(10);
	
/* ---------- Begining of the "While" Operating System ------------- */
	while(ALWAYS) 										// Can the Operating system run
	{                            
		if(TimeMsec % EVERY_50 == RESET_TIME)
			Display_Process();					//Refreshes screen every 50 'ticks'
                
		if(TimeMsec % EVERY_2 == RESET_TIME)
		{
			Switches_Process();                 // Poll for switch state change every other 'tick'
			ADC_Process();
		}
		
		Motors_Process();
		Control_Process();
	}
}

void Control_Process(void)
{
	IsLight = (ADC_LeftIR + ADC_RightIR)/2 < ADC_Thumb;
        
	if(!IsLight)
	{
		//          "0123456789abcdef"
		display_2 = "       Dark     ";
	}
	else
	{
		display_2 = "       Light    ";
	}
        
	if(MotorTimer <= 0)
	{
		if(!IsLight)
			ProgramState = 1;
		
		if(IsLight)
			ProgramState = 2;
	}	 
        
	if(ProgramState != OldState)
		StateTransitions++;
		  
	/*if(StateTransitions == 50)
		ProgramState = 3, StateTransitions++;
		
	if(StateTransitions >= 100)
		ProgramState = 0;
	  */
	if(MotorTimer <= 0)
	{
		switch(ProgramState)
		{
			case 1: 
				//allStop();
				MotorTimer = 1;
				LeftMotorPower = 50;
				RightMotorPower = 0;
              
				//          "0123456789abcdef"
				display_1 = "  Turning Right ";
				break;
            case 2:
				//allStop();
				MotorTimer = 1;
				LeftMotorPower = 0;
				RightMotorPower = 50;
				              
				//          "0123456789abcdef"
				display_1 = "  Turning Left  ";
				break;
			case 3: 
				allStop();
				MotorTimer = 1000;
				LeftMotorPower = -LPOWER;
				RightMotorPower = RPOWER;
            default:
              allStop();
              //MotorTimer = 6000;              
              //          "0123456789abcdef"
              display_1 = "     Default    ";
              break;
			}
			
			
			if(!IsLight)
				ProgramState = 1;
		
			if(IsLight)
				ProgramState = 2;
             
		}
        
	WasLight = IsLight;
	OldState = ProgramState;
}

void ADC_Process(void)
{
	while (ADC10CTL1 & BUSY); // Wait if ADC10 core is active
	ADC10CTL0 |= ADC10ENC + ADC10SC; // Sampling and conversion start
}