/*
 * main.c
 *
 * Created: 7/14/2024 9:04:41 AM
 *  Author: mahmoud
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "UTILS.h"

#define DDRC *((volatile unsigned char*)(0x34))
#define PORTC *((volatile unsigned char*)(0x35))

int main(void)
{
	DDRC = 0xFF;
    while(1)
    {
        //TODO:: Please write your application code 
		for(int i=0;i<10;i++)
		{
			for(int j =0;j<10;j++)
			{
				int delay =20;
				while(delay--)
				{
					PORTC=(j<<4)|(1<<2);
					_delay_ms(10);
					PORTC=(i<<4)|(1<<3);
					_delay_ms(10);
				}
			}
		}
    }
}