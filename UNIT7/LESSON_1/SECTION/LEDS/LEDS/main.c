/*
 * main.c
 *
 * Created: 7/13/2024 1:51:14 PM
 *  Author: mahmoud
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "UTILS.h"


#define BASE 0x20
#define DDRA *((volatile unsigned char*)(BASE+0x1A))
#define PORTA *((volatile unsigned char*)(BASE+0x1B))

int main(void)
{
	DDRA=0xFF;
	
    while(1)
    {
        //TODO:: Please write your application code 
		for(int i=0;i<8;i++)
		{
			SET_BIT(PORTA,i);
			_delay_ms(500);
		}
		for(int i=7;i>=0;i--)
		{
			CLEAR_BIT(PORTA,i);
			_delay_ms(500);
		}
		
    }
}