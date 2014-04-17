#include  "msp430.h"
#include  "functions.h"
#include  "macros.h"

//volatile int Time = 0;
volatile int sw1Debounce = DISABLE_DEBOUNCE, sw2Debounce = DISABLE_DEBOUNCE;

void Init_Interrupts(void)
{
	Serial_Init();
	
	P4IFG &= ~SW1;
	P4IFG &= ~SW2;
	P4IE |= SW1;
	P4IE |= SW2;
	P4IES |= SW1 | SW2;
	
	TA0CTL |= TASSEL__SMCLK;
	TA0CTL |= TACLR;
	TA0CTL |= MC__UP;
	TA0CTL |= ID__2;
	TA0CTL &= ~TAIE;
	TA0CTL &= ~TAIFG;
	
	TA0EX0 = TAIDEX_7;
	TA0CCR0 = TA0_ROLLOVER; //1ms
	TA0CCTL0 |= CCIE; 
        
        TA1CTL |= TASSEL__SMCLK;
	TA1CTL |= TACLR;
	TA1CTL |= MC__UP;
	TA1CTL |= ID__2;
	TA1CTL &= ~TAIE;
	TA1CTL &= ~TAIFG;
        
        TA1EX0 = TAIDEX_3;
        TA1CCR0 = 100;
        //TA1CCTL0 |= CCIE;
		
		
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