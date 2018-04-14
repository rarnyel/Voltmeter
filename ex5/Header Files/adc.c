#include "adc.h"
#include <xc.h>
#include <stdlib.h>

// Read a single sample from the ADC
unsigned int readADC()
{
  unsigned char bits;
  unsigned char rxData = 0;
  unsigned int volt = 0;
  // Pull CS low
  CS = 0;

  // Three clock toggles while the ADC is converting (see data sheet)
  for (bits = 0; bits < 3; bits++)
  {
      __delay_us(100);
      CLK = 1;
      __delay_us(100);
      CLK = 0;
  }

  // Read in the 8 MSBs, ignore the two lower bits
  for (bits = 0; bits < 8; bits++) 
  {
    // Delay before we raise the clock
    __delay_us(100);
    CLK = 1;
    
    // Read in the next bit, shift up by one bit
    rxData = rxData << 1;
    
    // Set or clear based on pin value
    if(DIN == 1)
      rxData = rxData | 0x01;
    else
      rxData = rxData & 0xfe;
    
    __delay_us(100);
    CLK = 0;
    }
  
  // Clear the CS bit
  CS = 1;
  
  // Return an integer, shift up by two because we only read 8-bits not 10.
  volt = (rxData << 2);
  return volt;
}