/*
 * KEYPAD.c
 *
 * Created: 17/07/2024 12:24:48 PM
 *  Author: Mahmoud
 */ 

#include "KEYPAD.h"

void KEYPAD_INIT()
{
	DATA_DIR_KEYPAD = 0xF0;
	KEYPAD_PORT = 0xFF;
}

char KEYPAD_GET_CHAR()
{
	char matrix[4][4]={{'7','4','1','c'},{'8','5','2','0'},{'9','6','3','='},{'/','*','-','+'}};
	char input = '\0';
	int i,j;
	while(1)
	{
		for(i=0;i<4;i++)
		{
			CLEAR_BIT(KEYPAD_PORT,(i+4));
			for(j=0;j<4;j++)
			{
				if(GET_BIT(PIND,j)==0)
				{
					while(GET_BIT(PIND,j)==0);
					input = matrix[i][j];
					SET_BIT(KEYPAD_PORT,(i+4));
					return input;
				}
			}
			SET_BIT(KEYPAD_PORT,(i+4));
		}
	}
}