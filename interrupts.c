#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

//volatile int Time = 0;
volatile int sw1Debounce = DISABLE_DEBOUNCE, sw2Debounce = DISABLE_DEBOUNCE;

void Init_Interrupts(void)
{
	P4IFG &= ~SW1;
	P4IFG &= ~SW2;
	P4IE |= SW1;
	P4IE |= SW2;
	P4IES |= SW1 | SW2;
	
	TA0CTL |= TASSEL__SMCLK;
	TA0CTL |= TACLR;
	TA0CTL |= MC__UP;
	TA0CTL |= ID__2; //ID__2
	TA0CTL &= ~TAIE;
	TA0CTL &= ~TAIFG;
	
	TA0EX0 = TAIDEX_7;
	
	TA0CCR0 = TA0_ROLLOVER;//TA0_ROLLOVER; //rollover of 500 => 1ms
	TA0CCTL0 |= CCIE;
        
        /*TA1CTL |= TASSEL__SMCLK;
	TA1CTL |= TACLR;
	TA1CTL |= MC__UP;
	TA1CTL |= ID__2;
	TA1CTL &= ~TAIE;
	TA1CTL &= ~TAIFG;
	
	TA1EX0 = TAIDEX_7;
	
	TA1CCR1 = 2500; //5ms
	TA1CCTL1 |= CCIE; //On at start
        */
		
		
	//Init ADC
#define RESET_STATE (0); 
	ADC10CTL0 = RESET_STATE; // Clear ADC10CTL0
	ADC10CTL0 |= ADC10SHT_2; // 16 ADC clocks
	ADC10CTL0 &= ~ADC10MSC; // Single Sequence
	ADC10CTL0 |= ADC10ON; // ADC ON - Core Enabled
	
	ADC10CTL1 = RESET_STATE; // Clear ADC10CTL1
	ADC10CTL1 |= ADC10SHS_0; // ADC10SC bit
	ADC10CTL1 |= ADC10SHP; // SAMPCON signal sourced from sampling timer
	ADC10CTL1 &= ~ADC10ISSH; // The sample-input signal is not inverted.
	ADC10CTL1 |= ADC10DIV_0; // ADC10_B clock divider – Divide by 1.
	ADC10CTL1 |= ADC10SSEL_0; // MODCLK
	ADC10CTL1 |= ADC10CONSEQ_0; // Single-channel, single-conversion
	
	ADC10CTL2 = RESET_STATE; // Clear ADC10CTL2
	ADC10CTL2 |= ADC10DIV_0; // Pre-divide by 1
	ADC10CTL2 |= ADC10RES; // 10-bit resolution
	ADC10CTL2 &= ~ADC10DF; // Binary unsigned
	ADC10CTL2 &= ~ADC10SR; // supports up to approximately 200 ksps
	
	ADC10MCTL0 = RESET_STATE; // Clear ADC10MCTL0
	ADC10MCTL0 |= ADC10SREF_0; // V(R+) = AVCC and V(R-) = AVSS
	ADC10MCTL0 |= ADC10INCH_3; // Channel A3 Thumb Wheel
	ADC10IE |= ADC10IE0; // Enable ADC conversion complete interrupt
}

// ADC10 interrupt service routine
// ADC_Right_Detector; // A00 ADC10INCH_0 - P1.0
// ADC_Left_Detector; // A01 ADC10INCH_1 - P1.1
// ADC_Thumb; // A03 ADC10INCH_3 - P1.3
// ADC_Temp; // A10 ADC10INCH_10 – Temperature REF module
// ADC_Bat; // A11 ADC10INCH_11 - Internal
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

#pragma vector=PORT4_VECTOR
__interrupt void Port_4(void)
{
	if(P4IFG & SW1)
	{
		P4IFG &= ~SW1;
		P1OUT |= IR_LED;
		PJOUT |= LED1;
	}
			
	if(P4IFG & SW2)
	{
		P4IFG &= ~SW2;
		P1OUT &= ~IR_LED;
		PJOUT &= ~LED1;
	}		
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0_A0(void)
{
	P3OUT ^= TEST_PROBE;
	
        TimeMsec++;
		
        if(MotorTimer > 0)
          MotorTimer--;
}

/*
#pragma vector=TIMER0_A1_VECTOR
__interrupt void Timer0_A1(void)
{
	P4IE |= SW1 | SW2;
        PJOUT &= ~LED3;   		 //Turn off debouce LED
  
  
  
        switch(TA0IV)
	{
		case 2: 					//CCR1
			if( !(P4IE & SW1) ) 	//sw1 was disabled
				P4IE |= SW1;
			else if( !(P4IE & SW2) ) //sw2 was disabled
				P4IE |= SW2;
			
                  
                        P4IE |= SW1 | SW2;
			PJOUT &= ~LED4;   		 //Turn off debouce LED
			TA0CCTL1 &= ~CCIE; 		 //Turn off this interrupt
			break;
			
		case 4:						//CCR2
			break;
			
		default:
			break;
	}
}*/