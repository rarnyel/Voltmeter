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
	//unsigned int flags = 0x00;	// Bit 0 is holdFlag, Bit 1 is adcFlag, bitwise XOR
	unsigned short holdFlag = 0;	// 1 if hold, switch using the interrupt
	unsigned short adcFlag = 0;	// Decides which ADC to use (0 for ADC1, 1 for ADC2)

	// Setting storage variable for raw ADC output
	unsigned int adc1 = 0;
	unsigned int adc2 = 0;

	// Setting storage variable for actual voltage
	unsigned int voltage = 0;
	unsigned int prevVoltage = 0;
	unsigned int maxVoltage = 0;
	unsigned int voltage1 = 0;
	unsigned int voltage2 = 0;
	
	// Setting variables for the LCD functions

void interrupt isr(){
	switch(INTCONbits.INTF){
		case 1:
			holdFlag = !holdFlag;
			break;
	}
	
	switch(INTCONbits.RBIF){
		case 1:
			adcFlag = !adcFlag;

			Lcd_Set_Cursor(2,1);
			
			// Prints V1 or V2 based on which ADC is being read
			switch(adcFlag){
				case 0:
					Lcd_Write_String("mV1");
					break;
				case 1:
					Lcd_Write_String("mV2");
					break;
      		}

			Lcd_Set_Cursor(1,1);

			break;
	}

	// Reset interrupt flag
	INTCONbits.INTF = 0;
	INTCONbits.RBIF = 0;
}

void welcome(){
	// Show welcome message and voltage limits
	Lcd_Set_Cursor(1,1);	// Sets cursor on first 8 bits
	Lcd_Write_String("Hello Wo");
	Lcd_Set_Cursor(2,1);
	Lcd_Write_String("rld!");
	__delay_ms(1000);
	Lcd_Write_String("50 mV");
	Lcd_Set_Cursor(1,1);	
	Lcd_Write_String("250 - 47");
	__delay_ms(500);
}

int voltageFunc(unsigned short adcFlag){
	// Measuring voltage from ADC
	// Returns actual voltage
	// Maybe it checks which ADC is enabled and returns relevant voltage
	// 10-bit ADC so 1024 discrete voltage points between 0.25V and Vdd

	adc = readADC(unsigned short adcFlag);
	voltage = voltageFloor(adc);

	voltage = adc / 57;
	voltage = adc * 286;

	if(voltage<286){
		voltage = 250;
	}
	
	return voltage;
}

void main(){
	// Setting up TRISA and TRISB
	TRISA = 0b00010011;
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
				prevVoltage = voltage;
				voltage = voltageFunc(adcFlag);
				Lcd_Write_Int(voltage);

				break;

			case 1:
				// Hold last measured ADC voltage
				Lcd_Write_Int(voltage);
				break;
		}
	}
}
