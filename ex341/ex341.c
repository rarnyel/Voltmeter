// Setup configuration bits
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config CP = OFF

#define _XTAL_FREQ 4000000

#include <xc.h>

// Assuming pins a,b,c are RB0,1,2
int convertSevenSeg(int input){
	switch (input){
		case 0:
			return 0b01000000;
		case 1:
			return 0b01111001;
		case 2:
			return 0b00100100;
		case 3:
			return 0b00110000;
		case 4:
			return 0b00011001;
		case 5:
			return 0b00010010;
		case 6:
			return 0b00000010;
		case 7:
			return 0b01111000;
		case 8:
			return 0b00000000;
		case 9:
			return 0b00011000;
		default:
			return 0b00000110;
	}
}

void main(){
	while(1){
		PORTB = convertSevenSeg(3);
	}
}

