// Setup configuration bits
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config CP = OFF

// Set oscillator frequency
#define _XTAL_FREQUENCY 4000000

// Including libraries
#include <xc.h>
#include "lcd.h"

int holdFlag = 0;	// 1 if hold, switch using the interrupt
	
void main(){
	// Setting up TRISA and TRISB
	TRISA = 0b00000001;
	TRISB = 0b11100001;

	RW = 0;		
	Lcd_Init();
	Lcd_Clear();

	// Main loop
	while(1){
        holdFlag = 0;
        switch(holdFlag){
            case 0:
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("No Int");
                __delay_ms(10);
            case 1:
                Lcd_Clear();
                Lcd_Set_Cursor(1,1);
                Lcd_Write_String("Int");
                __delay_ms(10);
        }
	}
}
