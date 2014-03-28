/******************************************************************************
LCD Control
Description: This file contains the LCD Functions that will be called by other
methods to interface with the LCD.

Original Author:
Jim Carlson, Jan 2014, Built with IAR Embedded Workbench Version: V4.10A/W32 (5.60.5)

Edit 1:
Nathan Hansen, Feb 2014, Built with IAR Embedded Workbench Version: 5.60.5
******************************************************************************/

#include  "msp430.h"
#include  "functions.h"
#include "macros.h"

// LCD Configurations
void five_msec_sleep(unsigned int fivemsec);// Systems



// DOG-M162 LCD Driver
//   Uses SPIB (eUCSI_B0)
//   P1.4 -> SPI_CS_LCD
//   P1.7 -> RS_LCD
extern volatile unsigned char control_state[CNTL_STATE_INDEX];
unsigned char lcd_control;
extern volatile unsigned char current_character;
char display_line_1[INDEX_17];
char display_line_2[INDEX_17];
char *display_1;
char *display_2;

unsigned int char_count;
char current_line;
volatile unsigned int update_display_count;
volatile unsigned int display_update_time;
// Initialization sequence as described in MSP430FR57xx User Guide, 19.3.1  
// Peripheral defaults to 3-pin SPI mode  
void Init_SPI_B0(void){
// Reset peripheral  
    UCB0CTLW0 = UCSWRST;
// ACLK is clock source  
    UCB0CTLW0 |= UCSSEL__SMCLK;
// master mode, MSB transmitted first  
    UCB0CTLW0 |= UCMST | UCMSB | UCSYNC | UCCKPL;

    UCB0BRW = SPI_CLK_PRESCALER;
// Enable peripheral  
    UCB0CTLW0 &= ~(UCSWRST);
// Wait to ensure the peripheral is up  
    __delay_cycles(WAIT_100);
}
//------------------------------------------------------------------------------
// Writes a byte out of SPIB, assumes CSB already low  
void SPI_B0_write(char byte){
// Wait for TX empty  
  while (!(UCB0IFG & UCTXIFG));
  UCB0TXBUF = byte;
// Wait for TX empty  
  while (!(UCB0IFG & UCTXIFG));
}
//------------------------------------------------------------------------------
// These inline functions provide convenient controls
// for the CSB and RS bits used by the LCD.

// Low - Command  High - Data
void spi_rs_data(void){
  P1OUT |= RS_LCD;
}

void spi_rs_command(void){
  P1OUT &= ~RS_LCD;
}

void spi_chipselect_idle(void){
  P1OUT |= SPI_CS_LCD;
}

void spi_chipselect_active(void){
  P1OUT &= ~SPI_CS_LCD;
}

void spi_reset_idle(void){
  P1OUT |= RESET_LCD;
}

void spi_reset_active(void){
  P1OUT &= ~RESET_LCD;
}

void Init_LCD(void){
  Init_SPI_B0();            // Initialize SPI Bus
// Initialization sequence from DOG-M162 reference, 8-bit, 3.3V
  spi_reset_active();
// Wait 300ms to ensure LCD is reset
  five_msec_sleep(WAIT_20); 
  spi_reset_idle();
// Wait 150ms to ensure LCD is powered
  five_msec_sleep(WAIT_10); 
// 8-bit data, 2 lines, instruction table 1
// NOTE: These are set again later, when switching back to instruction table 0.
// If you want to change these, be sure to change them below as well. 
  lcd_write(FUNCTION_SET | FUNCTION_SET_8BIT | FUNCTION_SET_2LINE | FUNCTION_SET_INST1, LCD_COMMAND);
// 1/5 Bias
  lcd_write(BIAS_SET, LCD_COMMAND);
// Boost on, C4 constrast 
  lcd_write(POWER_SET | POWER_SET_BOOST | POWER_SET_C4, LCD_COMMAND);
  five_msec_sleep(WAIT_2); 
// Voltage follower, gain 
  lcd_write(FOLLOWER_CTL | FOLLOWER_CTL_FON | FOLLOWER_CTL_GAIN(GAIN), LCD_COMMAND);
// Set contrast, none of C3, C2, C1 
  lcd_write(CONTRAST_SET | CONTRAST_SET_C2 | CONTRAST_SET_C1, LCD_COMMAND);
// Switch back to instruction table 0 
  lcd_write(FUNCTION_SET | FUNCTION_SET_8BIT | FUNCTION_SET_2LINE | FUNCTION_SET_INST0, LCD_COMMAND);
// Display on 
  lcd_write(DISPLAY_CTL | DISPLAY_CTL_ON, LCD_COMMAND);
// Clear Display 
  lcd_write(CLEAR_DISPLAY, LCD_COMMAND);
// Cursor auto increment 
  lcd_write(ENTRY_MODE | ENTRY_MODE_INCRE, LCD_COMMAND);
// Wait for display to be ready 
  usleep10(WAIT_20000);
  spi_rs_data();
  usleep10(WAIT_20000);
}

void lcd_write(char data, char rs){
  if(rs == LCD_COMMAND){spi_rs_command();}
  usleep10(WAIT_1);
  spi_chipselect_active(); // Chip Select Active
  usleep10(WAIT_1);
  SPI_B0_write(data);
  usleep10(WAIT_8);
  spi_chipselect_idle();
  if(rs == LCD_COMMAND){spi_rs_data();}
  usleep10(WAIT_2);
}

void lcd_command( char data){
  spi_rs_command();
  usleep10(WAIT_1);
  spi_chipselect_active();
  usleep10(WAIT_1);
  SPI_B0_write(data);
  usleep10(WAIT_8);
  spi_chipselect_idle();
  usleep10(WAIT_2);
}

// Write a character to the display. '\n' will move the cursor to line 2.
void lcd_putc(char c){
  if (c == '\n') {
    lcd_write(LCD_L2_C01, LCD_COMMAND);  // Move to line two
    current_line = LCD_LINE_2;
    char_count = WAIT_1;
  }else{
    if(char_count <= WAIT_16){
      lcd_write(c, LCD_DATA);          // Write character
    }
    char_count++;
  }
}

// Write a string to the display, using lcd_putc.
void lcd_puts(char *s){
  char_count = COUNT_1;
  current_line = LCD_LINE_1;
  if (s == NULL){
    return;
  }
  while (*s) {
    lcd_putc(*s++);
  }
}

// Write a string to the display, using lcd_putc.
void lcd_out(char *s, char line){
  lcd_write(line, LCD_COMMAND);  // Move to line two
  char_count = WAIT_1;
  while (*s) {
    lcd_putc(*s++);
  }
}

void Display_Process(void){
  lcd_out(display_1,LCD_LINE_1);   // 16 characters max between quotes - line 1
  lcd_out(display_2,LCD_LINE_2);   // 16 characters max between quotes - line 2
}