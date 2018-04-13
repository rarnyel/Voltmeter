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
// Set all port B bits to be outputs and port A input
TRISA = 0xFF;
TRISB = 0x00;

// Port output for number 5 (assuming abcd=RB0,1,2,3)
int five = 0x12;

// This loop happens forever
while(1)
{
		if(PORTAbits.RA0 == 0){
				PORTB=five; 		// Turn on RB0,1,2
				__delay_ms(2000); 	// Wait 2 seconds
				PORTB=0xFF;
				__delay_ms(2000);
		}
		else{
				PORTB=0x00;
		}
}
return;
}
