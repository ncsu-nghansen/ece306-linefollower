// Function prototypes for precompiled
__interrupt void Timer2_B0_ISR(void);
 __interrupt void TIMER2_B1_ISR(void);
void Init_Timer_B2(void);
void measure_delay(void);
void usleep10(unsigned int usec);

// Function prototypes main
void main(void);
void ADC_Process(void);
void Control_Process(void);

// Function prototypes init
void Init_Conditions(void);

// Function prototypes switch
void Switches_Process(void);
char isPressed(int);

// Function prototypes timers
void Init_Timers(void);
void waitMsec(int);


// Function prototypes clocks
void Init_Clocks(void);


// Function prototypes systems
void enable_interrupts(void);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(void); 
void Init_Port4(void);
void Init_PortJ(void);

// Function prototypes LED
void Init_LEDs(void);

// Function prototypes LCD

void Init_LCD(void); 
void lcd_clear(void); 
void lcd_putc(char c); 
void lcd_puts(char *s); 
void lcd_out(char *s, char line); 
void lcd_write(char data, char command); 
void lcd_command( char data); 
void Display_Process(void);

//Function Prototypes Interrupt (not the interrupts themselves)
void Init_Interrupts(void);

// Motor Control Prototypes
void Motors_Process(void);
void leftForward(void);
void leftReverse(void);
void rightForward(void);
void rightReverse(void);
void leftStop(void);
void rightStop(void);
void allStop(void);
void timedForward(int time);
void timedReverse(int time);
void timedLeft(int time);
void timedRight(int time);
void circleCW(void);
void circleCCW(void);
void figureEight(void);
void triangle(void);