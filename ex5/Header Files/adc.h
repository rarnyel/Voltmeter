// ADC Functions for the MCP3001
// B.W.Metcalfe 2016

// Define the oscillator frequency, needed for delays
#define _XTAL_FREQ  4000000

// Define the ping connections
#define CS RB5
#define CLK RB6
#define DIN1 RA0	//Output for ADC1
#define DIN2 RA1	//Output for ADC2

// Read a single (8-bit) sample from the ADC
unsigned int readADC(int adcFlag);
