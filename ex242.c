// Setup configuration bits
#pragma config FOSC = XT // XT oscillator
#pragma config WDTE = OFF // WDT disabled
#pragma config PWRTE = ON // Power-up Timer enabled
#pragma config CP = OFF // No Code protection

// Oscillator Frequency (4 MHz)
#define _XTAL_FREQ 4000000

// Include C library functions for PIC
#include <xc.h>

void main()
{
// Set all port B bits to be outputs
TRISB = 0x0;

// This loop happens forever
while(1)
{
PORTB=0x07; // Turn on RB0,1,2
__delay_ms(250); // Wait 0.25 seconds
PORTB=0x04;
__delay_ms(250);
PORTB=0x03;
__delay_ms(250);
PORTB=0x00;
__delay_ms(250);
}
return;
}
