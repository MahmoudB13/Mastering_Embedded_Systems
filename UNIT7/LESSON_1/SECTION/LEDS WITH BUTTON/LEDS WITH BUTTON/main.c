/*
 * main.c
 *
 * Created: 7/13/2024 1:51:14 PM
 *  Author: mahmoud
 */ 

#define F_CPU 8000000UL
#include <util/delay.h>
#include "UTILS.h"

#define DDRA *((volatile unsigned char*)(0x3A))
#define PORTA *((volatile unsigned char*)(0x3B))

#define PINC *((volatile unsigned char*)(0x33))
#define DDRC *((volatile unsigned char*)(0x34))
#define PORTC *((volatile unsigned char*)(0x35))

int main(void)
{
	DDRA=0xFF;
	DDRC=0x00;
	PORTC=0x01;
	
    while(1)
    {
        //TODO:: Please write your application code 
		int count = 0;
		while(count<8)
		if(GET_BIT(PINC,0)==0)
		{
			SET_BIT(PORTA,count);
			while(GET_BIT(PINC,0)==0);
			count++;
		}
		
    }
}