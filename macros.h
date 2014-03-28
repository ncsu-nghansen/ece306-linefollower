//---------------------------------------------
//Shared Global Variables

extern char *display_1;
extern char *display_2;
volatile extern int ADC_Thumb;
volatile extern int ADC_LeftIR; 
volatile extern int ADC_RightIR;
volatile extern unsigned int TimeMsec;
volatile extern unsigned int TimeUsec;
volatile extern unsigned int Time_Sequence;
extern int AdcChannel;

volatile extern int MotorTimer;
volatile extern int LeftMotorPower;
volatile extern int RightMotorPower;
volatile extern int MotorState;

volatile extern char Last_SW1_State;
volatile extern char Last_SW2_State;

//-------------------------------------------
// Main Macros

#define ALWAYS                  (1) // Is always 1
#define LED1                 (0x01) // LED 1
#define BLINK_LED            (0x01) // Allow LED to Blink
#define CNTL_STATE_INDEX        (3) // Control States
#define LCD_LINE_1           (0x80) // Position Cursor at Character 01 of Line 1
#define LCD_LINE_2           (0xC0) // Position Cursor at Character 01 of Line 2
#define GPS_ONOFF            (0x08) //
#define LED1                 (0x01) // LED 1
#define LED2                 (0x02) // LED 2
#define LED3                 (0x04) // LED 3
#define LED4                 (0x08) // LED 4

#define SW1                  (0x01) // Switch 1
#define SW2                  (0x02) // Switch 2
#define CNTL_STATE_INDEX        (3)

//Unhelpful Main Macros
#define RESET_TIME			 (0x00)
#define NOT_PRESSED          (0x00)
#define EVERY_50				(50)
#define EVERY_2					(2)
#define ROLLOVER_TIME			(250)

//-------------
//Clocks
#define CSLOCK                  (0x01) // Any incorrect password locks registers
#define MCLK_FREQ           (8000000L)
#define SMCLK_FREQ          (8000000L)
//#define SMCLK_FREQ        (6000000L)
//#define SMCLK_FREQ        (2000000L)
#define SMCLK_DIV                 (64)

#define USE_R_FORWARD (0x00)
#define USE_SMCLK (0x01)

//------------------------------------------------------------
// General Port Config  Macros

#define STD_IO (0x00)

#define FUNC1_1 (0x00)
#define FUNC1_0 (0x01)

#define FUNC2_1 (0x01)
#define FUNC2_0 (0x00)

#define FUNC3_1 (0x01)
#define FUNC3_0 (0x01)

#define INPUT (0x00)
#define OUTPUT (0x01)

#define SET_LOW (0x00)
#define SET_HIGH (0x01)

#define INTERRUPTS (0x01)

#define LOW_HIGH (0x00)
#define HIGH_LOW (0x01)

#define NO_RESIST (0x00)
#define RESIST (0x01)


// Port 1 Macros

#define V_DETECT_R (0x01)
#define V_DETECT_L (0x02)
#define IR_LED (0x04)
#define V_THUMB (0x08)
#define SPI_CS_LCD (0x10)
#define RESET_LCD (0x20)
#define SPI_SIMO (0x40)
#define RS_LCD (0x80)

// Port 2 Macros 

#define USB_TXD (0x01)
#define USB_RXD (0x02)
#define SPI_SCK (0x04)
#define UNK_1 (0x08)
#define UNK_2 (0x10)
#define CPU_TXD (0x20)
#define CPU_RXD (0x40)
#define UNK_3 (0x80)

// Port 3 Macros 
#define ACEL_X (0x01)  //Does capitalization matter here?
#define ACEL_Y (0x02)
#define ACEL_Z (0x04)
#define TEST_PROBE (0x08)
#define R_FORWARD (0x10)
#define R_REVERSE (0x20)
#define L_FORWARD (0x40)
#define L_REVERSE (0x80)

// Port 4 Macros 
#define SW1 (0x01) //Switch 1
#define SW2 (0x02) //Switch 2

// Port J Macros
#define GPS_PWR (0x01)
#define GPS_RESET (0x02)
#define GPS_PWRCNTL (0x04)
#define GPS_PWRCHK (0x08)

//-----------------------------------------------
// LCD macros

#define NULL ((void *) 0x0)

// Control States
#define CNTL_STATE_INDEX        (3)

// With 8MHz SMCLK, this makes the SPI clock 100kHz.
#define SPI_CLK_PRESCALER      (80)

// SPI
#define SPI_CS_LCD           (0x10) // Old NTC - ADC Input
#define RESET_LCD            (0x20) // 
#define RS_LCD               (0x80) // SPI RS Command / Data selection

// LCD
#define LINE1                   (0)
#define LINE2                   (1)
// Low - Command  High - Data
#define LCD_COMMAND             (0)
#define LCD_DATA                (1)
// DOG-M162 Instructions See ST7036 reference for details.
#define CLEAR_DISPLAY        (0x01)
#define RETURN_HOME          (0x02)

#define ENTRY_MODE           (0x04)
#define ENTRY_MODE_INCRE     (0x02)
#define ENTRY_MODE_SHIFT     (0x01)

#define DISPLAY_CTL          (0x08)
#define DISPLAY_CTL_ON       (0x04)
#define DISPLAY_CTL_CURSOR   (0x02)
#define DISPLAY_CTL_BLINK    (0x01)

#define FUNCTION_SET         (0x20)
#define FUNCTION_SET_8BIT    (0x10)
#define FUNCTION_SET_2LINE   (0x08)
#define FUNCTION_SET_2HIGH   (0x04)
#define FUNCTION_SET_INST2   (0x02)
#define FUNCTION_SET_INST1   (0x01)
#define FUNCTION_SET_INST0   (0x00)

#define SET_CGRAM(addr)      (0x40 | addr)
#define SET_DDRAM(addr)      (0x80 | addr)
#define BIAS_SET             (0x14)
#define BIAS_SET_FOURTH      (0x08)
#define POWER_SET            (0x50)
#define POWER_SET_ICON       (0x08)
#define POWER_SET_BOOST      (0x04)
#define POWER_SET_C5         (0x02)
#define POWER_SET_C4         (0x01)
#define FOLLOWER_CTL         (0x60)
#define FOLLOWER_CTL_FON     (0x08)
#define FOLLOWER_CTL_GAIN(g)    (g)
#define CONTRAST_SET         (0x70)
#define CONTRAST_SET_C3      (0x08)
#define CONTRAST_SET_C2      (0x04)
#define CONTRAST_SET_C1      (0x02)
#define CONTRAST_SET_C0      (0x01)
#define GAIN                 (0x0D) // Recommended value from DOG-M Reference

// Line 2 begins at this DDRAM address
#define LINE_TWO             (0x40)

#define LCD_LINE_1           (0x80) // Position Cursor at Character 01 of Line 1
#define LCD_LINE_2           (0xC0) // Position Cursor at Character 01 of Line 2

#define LCD_L1_C01           (0x80) // Position Cursor at Character 01 of Line 1
#define LCD_L1_C02           (0x81) // Position Cursor at Character 02 of Line 1
#define LCD_L1_C03           (0x82) // Position Cursor at Character 03 of Line 1
#define LCD_L1_C04           (0x83) // Position Cursor at Character 04 of Line 1
#define LCD_L1_C05           (0x84) // Position Cursor at Character 05 of Line 1
#define LCD_L1_C06           (0x85) // Position Cursor at Character 06 of Line 1
#define LCD_L1_C07           (0x86) // Position Cursor at Character 07 of Line 1
#define LCD_L1_C08           (0x87) // Position Cursor at Character 08 of Line 1
#define LCD_L1_C09           (0x88) // Position Cursor at Character 09 of Line 1
#define LCD_L1_C10           (0x89) // Position Cursor at Character 10 of Line 1
#define LCD_L1_C11           (0x8A) // Position Cursor at Character 11 of Line 1
#define LCD_L1_C12           (0x8B) // Position Cursor at Character 12 of Line 1
#define LCD_L1_C13           (0x8C) // Position Cursor at Character 13 of Line 1
#define LCD_L1_C14           (0x8D) // Position Cursor at Character 14 of Line 1
#define LCD_L1_C15           (0x8E) // Position Cursor at Character 15 of Line 1
#define LCD_L1_C16           (0x8F) // Position Cursor at Character 16 of Line 1
#define LCD_L2_C01           (0xC0) // Position Cursor at Character 01 of Line 2
#define LCD_L2_C02           (0xC1) // Position Cursor at Character 02 of Line 2
#define LCD_L2_C03           (0xC2) // Position Cursor at Character 03 of Line 2
#define LCD_L2_C04           (0xC3) // Position Cursor at Character 04 of Line 2
#define LCD_L2_C05           (0xC4) // Position Cursor at Character 05 of Line 2
#define LCD_L2_C06           (0xC5) // Position Cursor at Character 06 of Line 2
#define LCD_L2_C07           (0xC6) // Position Cursor at Character 07 of Line 2
#define LCD_L2_C08           (0xC7) // Position Cursor at Character 08 of Line 2
#define LCD_L2_C09           (0xC8) // Position Cursor at Character 09 of Line 2
#define LCD_L2_C10           (0xC9) // Position Cursor at Character 10 of Line 2
#define LCD_L2_C11           (0xCA) // Position Cursor at Character 11 of Line 2
#define LCD_L2_C12           (0xCB) // Position Cursor at Character 12 of Line 2
#define LCD_L2_C13           (0xCC) // Position Cursor at Character 13 of Line 2
#define LCD_L2_C14           (0xCD) // Position Cursor at Character 14 of Line 2
#define LCD_L2_C15           (0xCE) // Position Cursor at Character 15 of Line 2
#define LCD_L2_C16           (0xCF) // Position Cursor at Character 16 of Line 2

//Unhelpful LCD macros
#define INDEX_17 (17)
#define WAIT_100 (100)
#define WAIT_20 (20)
#define WAIT_10 (10)
#define WAIT_2 (2)
#define WAIT_20000 (20000)
#define WAIT_8 (8)
#define WAIT_1 (1)
#define WAIT_16 (16)
#define COUNT_1 (1)


//-----------------------------------------------------------------------------
//Switch Macros
#define INDEX_0 (0)
#define INDEX_1 (1)
#define INDEX_2 (2)
#define INDEX_12 (12)
#define INDEX_13 (13)
#define INDEX_14 (14)

//-----------------------------------------------------------------------------
//Interrupt Macros
#define TA0_ROLLOVER (500)  //gives 1ms tick
#define START_DEBOUNCE (500)  //gives 500ms debounce
#define END_DEBOUNCE (0)
#define DISABLE_DEBOUNCE (-1)


//----------------------
//Motor Macros
#define RESET_0 (0)
#define TICK_LENGTH (1) //Time_Sequence is 5ms? //Why was this 15?

#define RPOWER (95)
#define LPOWER (100)
#define MAX_POWER (100)
#define OFF_POWER (0)

#define CIRCLE_CW_TIME (3150)
#define CIRCLE_CCW_TIME (3750)
#define CIRCLE_DIV (8)

#define TRI_TIME (250)
#define TURN_60 (1000)
#define TURN_90 (1500)
#define TRI_SIDES (3)

#define SPIN_TIME (2750)

#define TWO_SEC (2000)
#define ONE_SEC (1000)
#define HALF_SEC (500)

//Time Macros
#define QUARTER_SEC (250)
#define HALF_SEC (500)
#define ONE_SEC (1000)
#define TEN_SEC (10000)