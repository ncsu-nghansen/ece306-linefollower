#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

volatile int ADC_Thumb = 255;
volatile int ADC_LeftIR = 0; 
volatile int ADC_RightIR = 0;

volatile int LeftLight = 0;
volatile int LeftDark = 0;
volatile int RightLight = 0;
volatile int RightDark = 0;

volatile int leftThreshold;
volatile int rightThreshold;

int AdcChannel = ADC10INCH_0;

/** 
* ADC10 interrupt service routine
* ADC_Right_Detector; // A00 ADC10INCH_0 - P1.0
* ADC_Left_Detector; // A01 ADC10INCH_1 - P1.1
* ADC_Thumb; // A03 ADC10INCH_3 - P1.3
* ADC_Temp; // A10 ADC10INCH_10 – Temperature REF module
* ADC_Bat; // A11 ADC10INCH_11 - Internal
**/
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
	switch(__even_in_range(ADC10IV,12)) 
	{
		case 0: break; // No interrupt
		case 2: break; // conversion result overflow
		case 4: break; // conversion time overflow
		case 6: break; // ADC10HI
		case 8: break; // ADC10LO
		case 10: break; // ADC10IN
		case 12:
                  
                        ADC10CTL0 &= ~ADC10ENC;
				
			switch(AdcChannel)//Put an incrementing break statement to update different channels in turn
			{
				case 0: 
					ADC_LeftIR = ADC10MEM0;
					ADC10MCTL0 = ADC10INCH_1;
					AdcChannel = 1;
					break;
				case 1:
					ADC_RightIR = ADC10MEM0;
					ADC10MCTL0 = ADC10INCH_3;
					AdcChannel = 2;
					break;
				case 2:
					ADC_Thumb = ADC10MEM0; 
					ADC10MCTL0 = ADC10INCH_0;
					AdcChannel = 0;
					break;
				default:
					break;
			}
                        
                        ADC10CTL0 |= ADC10ENC | ADC10SC;
                        break;
                        
		default: 
			break;
	}
}

void ADC_Process(void)
{
	P1OUT |= IR_LED;
        
	while (ADC10CTL1 & BUSY); // Wait if ADC10 core is active
	ADC10CTL0 |= ADC10ENC | ADC10SC; // Sampling and conversion start
}

void CalibrateIR(void)
{
	leftThreshold = (LeftDark + LeftLight)/2;
	rightThreshold = (RightDark + RightLight)/2;
}

char IsRightIrLight()
{
	return (ADC_RightIR < rightThreshold);
}

char IsLeftIrLight()
{
	return (ADC_LeftIR < leftThreshold);
}
