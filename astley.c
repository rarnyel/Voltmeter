// CONFIG
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config CP = OFF

#include <xc.h>
// Include the LCD library
#include "lcd.h"

#define _XTAL_FREQUENCY 4000000

void main(){
	TRISA = 0x00;
    TRISB = 0x00;
    
    RW = 0;
    
    Lcd_Init();
    
    while(1){
        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("WE'RE");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("NO");
        __delay_ms(1000);

        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("STRANGER");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("S TO");
        __delay_ms(1000);

        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("LOVE");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String(" ");
        __delay_ms(2000);        

        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("YOU");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("KNOW");
        __delay_ms(1000);

        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("THE");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("RULES");
        __delay_ms(1000);

        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("AND");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("SO");
        __delay_ms(1000);

        Lcd_Clear();
        Lcd_Set_Cursor(1,1);
        Lcd_Write_String("DO");
        Lcd_Set_Cursor(2,1);
        Lcd_Write_String("I");
        __delay_ms(1000);
    }
}
