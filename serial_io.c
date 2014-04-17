#include "functions.h"
#include "macros.h"
#include "msp430.h"

char UsbRx[128];
int usbRx_R = 0, usbRx_W = 0;
char UsbTx[128];
int usbTx_R = 0, usbTx_W = 0;
char SerialRx[128];
int serialRx_R = 0, serialRx_W = 0;
char SerialTx[128];
int serialTx_R = 0, serialTx_W = 0;

char GpsCounter = 0;



#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
	switch(__even_in_range(UCA0IV,0x08))
	{
		case 0: // Vector 0 - no interrupt
			break;
		case 2: // Vector 2 - RXIFG			
			UsbRx[usbRx_W++] = UCA0RXBUF;
			usbRx_W %= sizeof UsbRx;
			break;
		case 4: // Vector 4 – TXIFG
			break;
		default: 
			break;
	}
}

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
	switch(__even_in_range(UCA1IV,0x08))
	{
		case 0: // Vector 0 - no interrupt
			break;
		case 2: // Vector 2 - RXIFG			
			SerialRx[serialRx_W] = UCA1RXBUF;
			writeUsb(SerialRx[serialRx_W]); //Echo to COM
			/*
			if(SerialRx[serialRx_W] == '$')
			{
			  if(GpsCounter == 0)
				GpsCounter = 64;
			  else
				GpsPacketChk();
			}
                         */ 
			serialRx_W++;
			serialRx_W %= sizeof SerialRx;     
			break;
		case 4: // Vector 4 – TXIFG
			break;
		default: 
			break;
	}
}

void Serial_Init(void)
{
        for(int i = 0; i < sizeof UsbRx; i++)
		{
			UsbRx[i] = 0;
			UsbTx[i] = 0;
			SerialRx[i] = 0;
			SerialTx[i] = 0;
		}
        
		// Configure UART 0
		UCA0CTLW0 = 0; // Use word register
		UCA0CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
		UCA0CTLW0 |= UCSWRST; // Set Software reset enable
		UCA0BRW = 52 ; // 9,600 baud
		UCA0MCTLW = 0x4911 ;
		UCA0CTL1 &= ~UCSWRST; // Release from reset
		UCA0IE |= UCRXIE; // Enable RX interrupt

		// Configure UART 1
		UCA1CTLW0 = 0; // Use word register
		UCA1CTLW0 |= UCSSEL__SMCLK; // Set SMCLK as fBRCLK
		UCA1CTLW0 |= UCSWRST; // Set Software reset enable
		UCA1BRW = 104 ; // 4800 baud	
		UCA1MCTLW = 0xD621; // UCA0MCTLW = UCSx | UCFx | UCOS16 = 0xD600 | 0x0020 | 0x0001;
		UCA1CTL1 &= ~UCSWRST; // Release from reset
		UCA1IE |= UCRXIE; // Enable RX interrupt
}

void writeUsb(char c)
{
        usbTx_W %= sizeof UsbTx;
  
        UsbTx[usbTx_W++] = c;
        UCA0TXBUF = c;
}

char readUsb(void)
{
	usbRx_R %= sizeof UsbRx;
  
        if(usbRx_R != usbRx_W)
		return UsbRx[usbRx_R++];
	else
		return 0xFF;
}

void writeSerial(char c)
{
	serialTx_W %= sizeof SerialTx;
  
        SerialTx[serialTx_W++] = c;
        UCA1TXBUF = c;
}

char readSerial(void)
{
        serialRx_R %= sizeof SerialRx;
  
	if(serialRx_R != serialRx_W)
		return SerialRx[serialRx_R++];
	else
		return 0xFF;
}