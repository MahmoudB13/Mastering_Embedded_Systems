/*
 * main.c
 *
 * Created: 7/15/2024 11:35:17 AM
 *  Author: Mahmoud
 */ 


#include "LCD_driver/LCD.h"
#include "KEYPAD_driver/KEYPAD.h"

int main(void)
{
	LCD_INIT();
	KEYPAD_INIT();
	_delay_ms(50);
    while(1)
    {
		char buffer = KEYPAD_GET_CHAR();
		if(buffer=='c')
		{
			LCD_WRITE_COMMAND(LCD_CLEAR_SCREEN);
		}
		else
		{
			LCD_WRITE_CHAR(buffer);	
		}
    }
}