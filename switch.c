/******************************************************************************
Switch Configurations

DESC: Contains methods that poll the switches and act on that information

GLOBALS: display_1 and display_2, current_SW1_state, and current_SW2_state are changed
None defined.

Nathan Hansen, 7 Feb 2014, Built with IAR Embedded Workbench Version: 5.60.5
******************************************************************************/


#include  "functions.h"
#include  "macros.h"
#include  "msp430.h"

#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void)
{
	if(P4IFG & SW1)
	{
		P4IFG &= ~SW1;
		
		if(DebounceTimer == 0)
		{
			LeftDark = ADC_LeftIR;
			RightDark = ADC_RightIR;
			DebounceTimer = 100;
			
			CalibrateIR();
		}
	}
			
	if(P4IFG & SW2)
	{
		P4IFG &= ~SW2;
		
		if(DebounceTimer == 0)
		{
			LeftLight = ADC_LeftIR;
			RightLight = ADC_RightIR;
			DebounceTimer = 100;
			
			CalibrateIR();
		}
	}		
}

//Switches_Process
//DESC: Detects switch toggle (press & release) by polling current states
//and comparing to records of the past state. On switch toggle, motor forward outputs
//and LCD readout of motor status are toggled on/off accordingly
//ARGS: None
//RET: None
void Switches_Process(void)
{
	char current_sw1_state = isPressed(SW1);
	char current_sw2_state = isPressed(SW2);
	
	if ( !Last_SW1_State && current_sw1_state )
	{               
		
	}
	
	if ( !Last_SW2_State && current_sw2_state ) 
	{

	}
	
	Last_SW1_State = current_sw1_state;
	Last_SW2_State = current_sw2_state;
}

//isPressed
//DESC: Used for polling the current pressed/not pressed status of either switch
//ARGS: Macro or mask that acts to select the corresponding bit for the desires switch
//RET: 1 if 'isPressed'; 0 if not 'isPressed'
char isPressed(int switchNum)
{
	if( (switchNum == SW1) || (switchNum == SW2) )
		return !(P4IN & switchNum);
	return 0;
}