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
	// Reset interrupt flag
	INTCONbits.INTF = 0;
	// INTERRUPT CODE
}

void welcome(){
	// Show welcome message and voltage limits
}

int voltage(){
	// Measuring voltage from ADC
	// Returns actual voltage
	// Maybe it checks which ADC is enabled and returns relevant voltage
	// 10-bit ADC so 1024 discrete voltage points between 0.25V and Vdd
	adc1 = readADC();
	voltage1 = (adc*5)/1023;
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
	TRISA = 0x00;
	TRISB = 0x00;

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

	// Set R/W pin on LCD to W and init LCD
	RW = 0;
	Lcd_Init();
	Lcd_Clear();

	// Display welcome message
	welcome();

	// Main loop
	while(1){
		switch(holdFlag){
			case 0:
				// Read and display ADC voltage
				// Print voltage1
				// Delay
			case 1:
				// Hold last measured ADC voltage
		}
	}
}
