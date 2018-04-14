// LCD Functions
// B.W.Metcalfe 2016
// Based on code by electroSome.com and Paul Leonard

// Turn off some warnings
// 752 -> explicit cast still flags as warning, compiler bug so I've disabled it
// 520 -> turn of warning about un-used functions
#pragma warning disable 752
#pragma warning disable 520

// Define the oscillator frequency, needed for delays
#define _XTAL_FREQ  4000000

// Define the pin connections
#define RS RB4
#define RW RB5
#define EN RB6
#define D4 RB0
#define D5 RB1
#define D6 RB2
#define D7 RB3

// Set the bits on the LCD port
void Lcd_Port(char a);

// Send a command to the LCD
void Lcd_Cmd(char a);

// Clear the LCD
void Lcd_Clear();

// Set the cursor to a particular place and line
void Lcd_Set_Cursor(char a, char b);

// Bring up the LCD
void Lcd_Init();

// Write a single character
void Lcd_Write_Char(char a);

// Write an entire string
void Lcd_Write_String(char *a);

// Write an int
void Lcd_Write_Int(unsigned int a);

void Lcd_Shift_Right();

void Lcd_Shift_Left();