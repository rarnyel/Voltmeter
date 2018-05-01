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

// General variable setup
	unsigned char holdFlag = 0;	// 1 if hold, switch using the interrupt

	// Setting storage variable for raw ADC output
    unsigned int adcVal = 0;

	// Setting storage variable for actual voltage
	unsigned int voltage = 0;

void interrupt isr(){
	
	// Global interrupt disable
	INTCONbits.GIE = 0;

    // Toggles hold flag
    holdFlag = !holdFlag;

	// Reset interrupt flag
	INTCONbits.INTF = 0;
	
	// Re-enable global interrupts
	INTCONbits.GIE = 1;
}

void welcome(){
	// Show welcome message and voltage limits
	Lcd_Set_Cursor(1,1);	// Sets cursor on first 8 bits
	Lcd_Write_String("Hello Wo");   // Prints welcome message
    Lcd_Set_Cursor(2,1);    // Sets cursor on second 8 bits
    Lcd_Write_String("rld!");
    __delay_ms(1000);       // Delays 1s to show message
    Lcd_Clear();            // Clears the LCD
	Lcd_Write_String("250 - 47");   // Prints range
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String("50 mV");
	__delay_ms(1000);        // Delays 1s to show message
	Lcd_Clear();
}

int voltageFunc(){
	// Measures an ADC output and converts to voltage

	adcVal = readADC();     // Saved ADC output to adcVal

    // Converts to an actual voltage
	voltage = adcVal / 30;
	voltage = (voltage * 147) + 2;

    // Adds cutoff voltage equal to that of the ADC
	if(voltage<286){
		voltage = 250;
        
        // Sets up the buzzer variable
        unsigned char buzz = 0;
		
		// Buzzes 80 times at 1kHz
        while(buzz < 80){
            PORTBbits.RB7 = 1;
            __delay_ms(1);
            PORTBbits.RB7 = 0;
            __delay_ms(1);
            buzz++;
        }
	}
	
	// Ouputs the voltage from the function
	return voltage;
}

void main(){
	// Setting up TRISA and TRISB
	TRISA = 0b00010011;
	TRISB = 0b00000001;

	// Reset the external interrupt flag
	INTCONbits.INTF = 0;
	// Interrupt on the rising edge
	OPTION_REGbits.INTEDG = 1;
	// Enable the external interrupt
	INTCONbits.INTE = 1;
	// Global interrupt enable
	INTCONbits.GIE = 1;

	// Set CS high and CLK low for ADC
	CS = 1;
	CLK = 0;

	// Initialise LCD and show welcome message
	Lcd_Init();
	Lcd_Clear();
	welcome();
	
// Main loop
	while(1){
		switch(holdFlag){
			case 0:
				// Read and display ADC voltage
				// Saves voltage into variable "voltage"
				voltage = voltageFunc();
				
				// Prints voltage onto the LCD
				Lcd_Write_Int(voltage);

				// Prints mV
                Lcd_Set_Cursor(2,1);
                Lcd_Write_String("mV");
                Lcd_Set_Cursor(1,1);
                
                Lcd_Clear();

				break;

			case 1:
				// Hold last measured ADC voltage
				// Prints last voltage
				Lcd_Write_Int(voltage);
                Lcd_Set_Cursor(2,1);
				// Prints "mV Held"
                Lcd_Write_String("mV Held");
                Lcd_Set_Cursor(1,1);
                Lcd_Clear();
                
                break;
		}
	}
}
