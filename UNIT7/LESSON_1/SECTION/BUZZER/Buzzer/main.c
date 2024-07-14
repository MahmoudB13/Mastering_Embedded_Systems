/*
 * main.c
 *
 * Created: 7/14/2024 11:43:41 AM
 *  Author: mahmoud
 */ 

#include "UTILS.h"
#define F_CPU 8000000UL
#include <util/delay.h>

#define PIND   *((volatile unsigned char*)(0x30))
#define DDRD   *((volatile unsigned char*)(0x31))
#define PORTD  *((volatile unsigned char*)(0x32))

int main(void)
{
	SET_BIT(DDRD,4);
	CLEAR_BIT(DDRD,0);
    while(1)
    {
        //TODO:: Please write your application code 
		if(GET_BIT(PIND,0)==1)
		{
			SET_BIT(PORTD,4);
			_delay_ms(1000);
			CLEAR_BIT(PORTD,4);
		}
    }
}
