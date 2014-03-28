/******************************************************************************
Port Configuration

DESC: This file contains the initialization methods for all five ports, setting up the Pins
defined in macros.h for the desired operation modes. The modes are also defined in 
macros.c

GLOBALS: None defined, none modified.

Nathan Hansen, 7 Feb 2014, Built with IAR Embedded Workbench Version: 5.60.5
******************************************************************************/

#include  "functions.h"
#include  "macros.h"
#include  "msp430.h"

/*
Init_Ports

DESC: Calls other methods to initialize pins on each port

ARGS: None

RET: None
*/
void Init_Ports()
{
	Init_Port1();
	Init_Port2();
	Init_Port3();
	Init_Port4();
	Init_PortJ();
}

/*
Init_Port1

DESC: Uses predefined macros to set up pins for the P1 port's assigned functions.
See project spec for full documentation of wiring.

Port 	Pin 	Signal Name  	GP I/O or Function 	Direction / Function 
1 		0 		V_DETECT_R 		Function 			ADC - A0 	
1 		1 		V_DETECT_L 		Function 			ADC - A1 	
1 		2 		IR_LED 			GP I/O 				Output 	
1 		3 		V_THUMB 		Function 			ADC - A3	
1 		4 		SPI_CS_LCD 		GP I/O 				Output 	
1 		5 		RESET_LCD 		GP I/O 				Output
1 		6 		SPI_SIMO 		Function 			UCB0SIMO/UCB0SDA
1 		7 		RS_LCD 			GP I/O 				Output

ARGS: None

RET: None
*/
void Init_Port1(void)
{
	P1SEL0 = STD_IO;
	P1SEL0 |= (V_DETECT_R * FUNC3_0) | 
		(V_DETECT_L * FUNC3_0) | 
		(V_THUMB * FUNC3_0) |
		(SPI_SIMO * FUNC2_0);
	
	P1SEL1 = STD_IO;
	P1SEL1 |= (V_DETECT_R * FUNC3_1) |
		(V_DETECT_L * FUNC3_1) |
		(V_THUMB * FUNC3_1) |
		(SPI_SIMO * FUNC2_1);
	
	P1OUT = SET_LOW;
	P1OUT |= (SPI_CS_LCD * SET_HIGH) |
		(RESET_LCD * SET_HIGH) |
		(SPI_SIMO * SET_HIGH) |
		(RS_LCD * SET_HIGH);
	
	P1DIR = INPUT;
	P1DIR |= (IR_LED * OUTPUT) | 
		(SPI_CS_LCD * OUTPUT) |
		(RESET_LCD * OUTPUT) |
		(RS_LCD * OUTPUT) |
		(SPI_SIMO * OUTPUT);
			
	P1REN = NO_RESIST;
	P1REN |= (SPI_CS_LCD * RESIST) |
		(RESET_LCD * RESIST) |
		(SPI_SIMO * RESIST) |
		(RS_LCD * RESIST);	
}

/*
Init_Port2

DESC: Uses predefined macros to set up pins for the P2 port's assigned functions.
See project spec for full table of port/pin designations.

2 	0 	USB_TXD 	Function 	UCA0TXD/UCA0SIMO 
2 	1 	USB_RXD 	Function 	UCA0RXD/UCA0SOMI
2 	2 	SPI_SCK 	Function 	UCB0CLK
2 	3 	UNKNOWN 	GP I/O 		Input
2 	4 	UNKNOWN 	GP I/O 		Input
2 	5 	CPU_TXD 	Function 	UCA1TXD/UCA1SIMO
2 	6 	CPU_RXD 	Function 	UCA1RXD/UCA1SOMI
2 	7 	UNKNOWN 	GP I/O 		Input

ARGS: None

RET: None
*/
void Init_Port2(void)
{
	P2SEL0 = STD_IO;
	P2SEL0 |= (USB_TXD * FUNC2_0) |
		(USB_RXD * FUNC2_0) |
		(SPI_SCK * FUNC2_0) |
		(CPU_TXD * FUNC2_0) |
		(CPU_RXD * FUNC2_0);
		
	P2SEL1 = STD_IO;
	P2SEL1 |= (USB_TXD * FUNC2_1) |
		(USB_RXD * FUNC2_1) |
		(SPI_SCK * FUNC2_1) |
		(CPU_TXD * FUNC2_1) |
		(CPU_RXD * FUNC2_1);
	
	P2OUT = SET_LOW;
	P2OUT |= (SPI_SCK * SET_HIGH);
	
	P2DIR = INPUT;
	P2DIR |= (USB_TXD * OUTPUT) |
		(SPI_SCK * OUTPUT) | 
		(CPU_TXD * OUTPUT);
	
	P2REN = NO_RESIST;
	P2REN |= (SPI_SCK * RESIST);	
}

/*
Init_Port3

DESC: Uses predefined macros to set up pins for the P3 port's assigned functions.
See project spec for full table of port/pin designations.

IF USING AS MOTOR OUTPUT:

3 	0 	ACEL_X 			GP I/O 	Input
3 	1 	ACEL_Y 			GP I/O 	Input
3 	2 	ACEL_Z 			GP I/O 	Input
3 	3 	TEST_PROBE 		GP I/O 	Output
3 	4 	R_FORWARD 		GP I/O 	Output
3 	5 	R_REVERSE 		GP I/O 	Output
3 	6 	L_FORWARD 		GP I/O 	Output
3 	7 	L_REVERSE 		GP I/O 	Output

IF USING AS SMCLK OUTPUT:

3       4       LED5                    SMCLK   Output

ARGS: None

RET: None
*/
void Init_Port3(void)
{
	
	P3SEL0 = STD_IO;
	P3SEL1 = STD_IO;
	
	P3OUT = SET_LOW;
	
	P3DIR = INPUT;
	P3DIR |= (TEST_PROBE * OUTPUT) |
		(R_FORWARD * OUTPUT) |
		(R_REVERSE * OUTPUT) |
		(L_FORWARD * OUTPUT) |
		(L_REVERSE * OUTPUT);

	P3REN = NO_RESIST;
	
	//P3OUT = SET_LOW;
	//P3OUT |= LED5;
	
	//P3REN = NO_RESIST;	
}

/*
Init_Port4

DESC: Uses predefined macros to set up pins for the P4 port's assigned functions.
See project spec for full table of port/pin designations.

4 	0 	SW1 	GP I/O 	Input 	
4 	1 	SW2 	GP I/O 	Input

ARGS: None

RET: None
*/
void Init_Port4(void)
{
	P4SEL0 = STD_IO;
	P4SEL1= STD_IO;
	
	P4OUT = SET_LOW;
	P4OUT |= (SW1 * SET_HIGH) |
		(SW2 * SET_HIGH);
	
	P4DIR = INPUT;
		
	P4REN = NO_RESIST;
	P4REN = (SW1 * RESIST) |
		(SW2 * RESIST);
}

/*
Init_PortJ

DESC: Uses predefined macros to set up pins for the PJ port's assigned functions.
See project spec for full table of port/pin designations.

J 	0 	GPS_PWR 		GP I/O 	Output  	
J 	1 	GPS_RESET 		GP I/O 	Output
J 	2 	GPS_PWRCNTL 	GP I/O 	Output	
J 	3 	GPS_PWRCHK 		GP I/O 	Input

ARGS: None

RET: None
*/
void Init_PortJ(void)
{
	PJSEL0 = STD_IO;
	PJSEL1 = STD_IO;
	
	PJOUT = SET_LOW;
	
	PJDIR = INPUT;
	PJDIR = (GPS_PWR * OUTPUT) |
		(GPS_RESET * OUTPUT) |
		(GPS_PWRCNTL * OUTPUT);
		
	PJREN = NO_RESIST;
}