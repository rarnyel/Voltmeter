// Setup configuration bits
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config CP = OFF

#define _XTAL_FREQ 4000000

#include <xc.h>

int a = 0;
int pause = 0;

// Assuming pins a,b,c are RB1,2,3
int convertSevenSeg(int input){
	switch (input){
		case 0:
			return 0b00000000;
		case 1:
			return 0b01110010;
		case 2:
			return 0b01001000;
		case 3:
			return 0b01100000;
		case 4:
			return 0b00110010;
		case 5:
			return 0b00100100;
		case 6:
			return 0b00000100;
		case 7:
			return 0b01110000;
		case 8:
			return 0b00000000;
		case 9:
			return 0b00110000;
		default:
			return 0b00001100;
	}
}

void interrupt isr(){
    
    if(INTCONbits.RBIF){
        pause = ~pause;
    }
    else{
        //resets counter
        a = 0;
    }
    
	// Reset the interrupt flag
	INTCONbits.INTF = 0;
    INTCONbits.RBIF = 0;
}

void main(){
	// Set all of PORTA to inputs
	TRISA = 0XFF;
	// Set appropriate pins on PORTB to outputs
	TRISB = 0b10000001;
	// Reset the external interrupt flag
	INTCONbits.INTF = 0;
    // Reset the RB interrupt-on-change flag
    INTCONbits.RBIF = 0;
	// Interrupt on the rising edge
	OPTION_REGbits.INTEDG = 1;
	// Enable the external interrupt
	INTCONbits.INTE = 1;
    // Enable the RB interrupt-on-change
    INTCONbits.RBIE = 1;
	// Global interrupt enable
	INTCONbits.GIE = 1;

	while(1){
		for(a=0;a<10;a++){
            while(pause==1){
                PORTB = convertSevenSeg(a);
            }
			PORTB = convertSevenSeg(a);
			__delay_ms(1000);
		}
	}
}
