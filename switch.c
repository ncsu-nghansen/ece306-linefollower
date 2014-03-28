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

//Switches_Process
//DESC: Detects switch toggle (press & release) by polling current states
//and comparing to records of the past state. On switch toggle, motor forward outputs
//and LCD readout of motor status are toggled on/off accordingly
//ARGS: None
//RET: None
void Switches_Process(void)
{
	//            "0123456789abcdef"
	//display_1 = " Lt Forward Rt  ";
	//display_2 = "OFF         OFF ";
	
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