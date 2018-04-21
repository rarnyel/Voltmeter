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
	int adcFlag = 0;	// Decides which ADC to use (0 for ADC1, 1 for ADC2)

	// Setting storage variable for raw ADC output
	unsigned int adc1 = 0;
	unsigned int adc2 = 0;

	// Setting storage variable for actual voltage
	float voltage = 0;
	float prevVoltage = 0;
	float maxVoltage = 0;
	float voltage1 = 0;
	float voltage2  0;

void interrupt isr(){
	switch(INTCONbits.INTF){
		case 1:
			holdFlag = !holdFlag;
	//	case 0:
			// Code for other buttons
	}
	
	switch(INTCONbits.RBIF){
		case 1:
			adcFlag = !adcFlag;
	//	case 0:
			// Code for other buttons 
			// Maybe turn it into a tristate for differential voltage
	}

	// Reset interrupt flag
	INTCONbits.INTF = 0;
	INTCONbits.RBIF = 0;
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
	Lcd_Set_Cursor(2,1);	// Maybe not needed
	Lcd_Write_String("V max =");
	Lcd_Set_Cursor(2,1);
	Lcd_Write_String("4.75 V");
	__delay_ms(1500);
}

int voltage(int adcFlag){
	// Measuring voltage from ADC
	// Returns actual voltage
	// Maybe it checks which ADC is enabled and returns relevant voltage
	// 10-bit ADC so 1024 discrete voltage points between 0.25V and Vdd
	switch (adc){
		case 1:
			adc1 = readADC();
			voltage1 = (adc1*4.75)/1023;
		case 2:
			adc2 = readADC();
			voltage2 = (adc2*4.75)/1023;
	}
}

int maxVoltage(int prevVoltage, int voltage){
	// Function to measure and store max voltage
	// Maybe takes voltage as input and checks it against max
	if(prevVoltage > maxVoltage){
		prevVoltage = maxVoltage;
	}
}

int time(){
	// Function to time and display the time spent below threshold
}

void main(){
	// Setting up TRISA and TRISB
	TRISA = 0b00000001;
	TRISB = 0b11100001;

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

	// Set CS high and CLK low for ADC
	CS = 1;
	CLK = 0;	// 	(Maybe unnecessary)

	// Set R/W pin on LCD to W and init LCD
	RW = 0;		//	(Now unnecessary)
	Lcd_Init();
	Lcd_Clear();

	// Display welcome message
	welcome();

	// Main loop
	while(1){
		switch(holdFlag){
			case 0:
				// Read and display ADC voltage
				prevVoltage = Voltage;
				voltage = voltage(adcFlag);
				Lcd_Clear();
				Lcd_Set_Cursor(1,1);
				Lcd_Write_Char(voltage);
				Lcd_Set_Cursor(2,1);
				
				// Prints V1 or V2 based on which ADC is being read
				switch(adcFlag){
					case 0:
						Lcd_Write_String("V1");
					case 1;
						Lcd_Write_String("V2");
				}

			case 1:
				// Hold last measured ADC voltage
				Lcd_Clear();
				Lcd_Write_Char(voltage);
		}
	}
}
