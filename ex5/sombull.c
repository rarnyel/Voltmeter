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
	// Setting up flags
	int holdFlag = 0;	// 1 if hold, switch using the interrupt
	// To add flags for switching ADC later on	

	// Setting storage variable for raw ADC output
	unsigned int adc1 = 0;
	//unsigned int adc2 = 0;

	// Setting storage variable for actual voltage
	float voltage1 = 0;
	//float voltage2 = 0;


void interrupt isr(){
//    switch(INTCONbits.INTF){
//        case 1:
//            holdFlag = !holdFlag;
//        case 0:
//            holdFlag = holdFlag;
//    }

 //   holdFlag = !holdFlag;
	// Reset interrupt flag
	INTCONbits.INTF = 0;
	// INTERRUPT CODE
}


void welcome(){
	// Show welcome message and voltage limits
	Lcd_Clear();			// Technically unnecessary
	Lcd_Set_Cursor(1,1);	// Sets cursor on first 8 bits
	Lcd_Write_String("Hello Wo");
	Lcd_Set_Cursor(2,1);
	Lcd_Write_String("rld!");
	__delay_ms(3000);
	Lcd_Clear();
	Lcd_Set_Cursor(1,1);	// Maybe not needed
	Lcd_Write_String("V min =");
	Lcd_Set_Cursor(2,1);
	Lcd_Write_String("0.25 V");
	__delay_ms(1500);
	Lcd_Clear();
	Lcd_Set_Cursor(1,1);	// Maybe not needed
	Lcd_Write_String("V max =");
	Lcd_Set_Cursor(2,1);
	Lcd_Write_String("4.75 V");
	__delay_ms(1500);
}

int voltage(){
	// Measuring voltage from ADC
	// Returns actual voltage
	// Maybe it checks which ADC is enabled and returns relevant voltage
	// 10-bit ADC so 1024 discrete voltage points between 0.25V and Vdd
	adc1 = readADC();
	voltage1 = (adc1*4.75)/1023;
}

int hold(){
	// Function to check whether held
	// Maybe completely unnecessary
}

int maxVoltage(voltage){
	// Function to measure and store max voltage
	// Maybe takes voltage as input and checks it against max
}

int time(){
	// Function to time and display the time spent below threshold
}

void main(){
	// Setting up TRISA and TRISB
	TRISA = 0b00000001;
	TRISB = 0b11100001;

/*
	// Reset the external interrupt flag
	INTCONbits.INTF = 0;
	// Reset the RB interrupt-on-change flag
	INTCONbits.RBIF = 0;
	// Interrupt on the rising edge
	OPTION_REGbits.INTEDG = 1;
	// Enable the external interrupt
	INTCONbits.INTE = 0;    //  Should be 1
	// Enable the RB interrupt-on-change
	INTCONbits.RBIE = 0;    //  For some reason it just instantly interrupts
	// Global interrupt enable
	INTCONbits.GIE = 0;     // Should be 1
*/

	// Set CS high and CLK low for ADC
//	CS = 1;
//	CLK = 0;	// 	(Maybe unnecessary)

	// Set R/W pin on LCD to W and init LCD
//	RW = 0;		//	(Now unnecessary)
	Lcd_Init();
	Lcd_Clear();

	// Display welcome message
//	welcome();

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
