// Setup configuration bits
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config CP = OFF

// Set oscillator frequency
#define _XTAL_FREQUENCY 4000000

// Including libraries
#include <xc.h>
#include "adc.h"
#include "lcd.h"

	unsigned int adc1 = 0;
    int adc = 0;

	// Setting storage variable for actual voltage
	int voltage = 0;
	int voltage1 = 0;
    
    int holdFlag = 0;
    
void interrupt isr(){
	holdFlag = !holdFlag;
	// Reset interrupt flag
	INTCONbits.INTF = 0;
    }

void welcome(){
	// Show welcome message and voltage limits
	Lcd_Clear();			// Technically unnecessary
	Lcd_Set_Cursor(1,1);	// Sets cursor on first 8 bits
	Lcd_Write_String("Hello Wo");
	Lcd_Set_Cursor(2,1);
	Lcd_Write_String("rld!");
	__delay_ms(1000);
	Lcd_Clear();
	Lcd_Set_Cursor(1,1);	// Maybe not needed
	Lcd_Write_String("250 - 47");
	Lcd_Set_Cursor(2,1);
	Lcd_Write_String("50 mV");
	__delay_ms(1000);
}
    
int voltageFloor(int adc1){
	adc = adc1 / 57;
    adc = adc * 286;
    if(adc<286){
        adc = 286;
    }
    return adc;
}
    
void main(){
	// Setting up TRISA and TRISB
	TRISA = 0b00010011;
	TRISB = 0b10000001;

	// Set CS high and CLK low for ADC
	CS = 1;
	CLK = 0;
    
    // Reset the external interrupt flag
	INTCONbits.INTF = 0;
	// Interrupt on the rising edge
	OPTION_REGbits.INTEDG = 1;
	// Enable the external interrupt
	INTCONbits.INTE = 1;
	// Global interrupt enable
    INTCONbits.GIE = 1;

	// Initialise LCD and show welcome message
	Lcd_Init();
	Lcd_Clear();
    
    welcome();
    
	// Main loop
	while(1){
        switch(holdFlag){
            case 0:
              				// Read and display ADC voltage
				Lcd_Clear();
				Lcd_Set_Cursor(1,1);    
        
                adc1 = readADC();
        
                adc1 = voltageFloor(adc1);
				Lcd_Write_Int(adc1);
				Lcd_Set_Cursor(2,1);
				
				// Prints V1 or V2 based on which ADC is being read
				Lcd_Write_String("mV1");  
                break;
        case 1:
                Lcd_Set_Cursor(1,1);
            	Lcd_Write_Int(adc1);
				Lcd_Set_Cursor(2,1);
				
				// Prints V1 or V2 based on which ADC is being read
				Lcd_Write_String("mV1"); 
                break;
            }
	}
}
