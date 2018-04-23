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
			break;
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
	Lcd_Set_Cursor(1,1);	// Maybe not needed
	Lcd_Write_String("V max =");
	Lcd_Set_Cursor(2,1);
	Lcd_Write_String("4.75 V");
	__delay_ms(1500);
}

int voltageFunc(int adcFlag){
	// Measuring voltage from ADC
	// Returns actual voltage
	// Maybe it checks which ADC is enabled and returns relevant voltage
	// 10-bit ADC so 1024 discrete voltage points between 0.25V and Vdd
	switch (adcFlag){
		case 1:
			adc1 = readADC();
			voltage1 = voltageFloor(adc1);
			break;
		case 2:
			adc2 = readADC();
			voltage2 = voltageFloor(adc2);
			break;
	}
}

int voltageFloor(int adc){
	voltage = adc / 57;
	switch(voltage){
		case 1:
			return 25;
			break;
		case 2:
			return  50;
			break;
		case 3:
			return 75;
			break;
		case 4:
			return 100;
			break;
		case 5:
			return 125;
			break;
		case 6:
			return 150;
			break;
		case 7:
			return 175;
			break;
		case 8:
			return 200;
			break;
		case 9:
			return 225;
			break;
		case 10:
			return 250;
			break;
		case 11:
			return 275;
			break;
		case 12:
			return 300;
			break;
		case 13:
			return 325;
			break;
		case 14:
			return 350;
			break;
		case 15:
			return 375;
			break;
		case 16:
			return 400;
			break;
		case 17:
			return 425;
			break;
		case 18:
			return 450;
			break;
		}
}

int maxVoltageFunc(int prevVoltage, int voltage){
	// Function to measure and store max voltage
	// Maybe takes voltage as input and checks it against max
	if(prevVoltage > maxVoltage){
		prevVoltage = maxVoltage;
	}
}

void print(int cursor, int string, char input){
	Lcd_Clear();
	Lcd_Set_Cursor(cursor,1);
	switch(string){
		case 0:		// for string
			Lcd_Write_String(input);
			break;
		case 1:
			Lcd_Write_Char(input):
			break;
	}		
}	

int time(){
	// Function to time and display the time spent below threshold
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
				Lcd_Clear();
				Lcd_Set_Cursor(1,1);
				Lcd_Write_Int(adc1);
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

				break;

			case 1:
				// Hold last measured ADC voltage
				Lcd_Clear();
				Lcd_Write_Char(voltage);
				break;
		}
	}
}
