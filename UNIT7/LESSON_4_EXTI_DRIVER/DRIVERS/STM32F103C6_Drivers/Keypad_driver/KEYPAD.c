/*
 * KEYPAD.c
 *
 * Created: 17/07/2024 12:24:48 PM
 *  Author: Mahmoud
 */ 

#include "KEYPAD.h"

void KEYPAD_INIT()
{
	//SET BIT 0 TO OUTPUT
	GPIO_PinConfig_t PIN_Conf;
	PIN_Conf.GPIO_PIN_NUMBER = GPIO_PIN_0;
	PIN_Conf.GPIO_MODE = GPIO_MODE_OUT_PUSH_PULL;
		PIN_Conf.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
		MCAL_GPIO_Init(KEYPAD_PORT, &PIN_Conf);
	//SET BIT 1 TO OUTPUT
	PIN_Conf.GPIO_PIN_NUMBER = GPIO_PIN_1;
	PIN_Conf.GPIO_MODE = GPIO_MODE_OUT_PUSH_PULL;
		PIN_Conf.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
		MCAL_GPIO_Init(KEYPAD_PORT, &PIN_Conf);
	//SET BIT 3 TO OUTPUT
	PIN_Conf.GPIO_PIN_NUMBER = GPIO_PIN_3;
	PIN_Conf.GPIO_MODE = GPIO_MODE_OUT_PUSH_PULL;
		PIN_Conf.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
		MCAL_GPIO_Init(KEYPAD_PORT, &PIN_Conf);
	//SET BIT 4 TO OUTPUT
	PIN_Conf.GPIO_PIN_NUMBER = GPIO_PIN_4;
	PIN_Conf.GPIO_MODE = GPIO_MODE_OUT_PUSH_PULL;
		PIN_Conf.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
		MCAL_GPIO_Init(KEYPAD_PORT, &PIN_Conf);
	//SET BIT 5 TO OUTPUT
	PIN_Conf.GPIO_PIN_NUMBER = GPIO_PIN_5;
	PIN_Conf.GPIO_MODE = GPIO_MODE_OUT_PUSH_PULL;
	PIN_Conf.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PIN_Conf);
	//SET BIT 6 TO OUTPUT
	PIN_Conf.GPIO_PIN_NUMBER = GPIO_PIN_6;
	PIN_Conf.GPIO_MODE = GPIO_MODE_OUT_PUSH_PULL;
	PIN_Conf.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PIN_Conf);
	//SET BIT 7 TO OUTPUT
	PIN_Conf.GPIO_PIN_NUMBER = GPIO_PIN_7;
	PIN_Conf.GPIO_MODE = GPIO_MODE_OUT_PUSH_PULL;
	PIN_Conf.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PIN_Conf);
	//SET BIT 8 TO OUTPUT
	PIN_Conf.GPIO_PIN_NUMBER = GPIO_PIN_8;
	PIN_Conf.GPIO_MODE = GPIO_MODE_OUT_PUSH_PULL;
	PIN_Conf.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PIN_Conf);

	MCAL_GPIO_WritePort(KEYPAD_PORT, 0xFFFF);
}

/* c output
 * r input
 */

char KEYPAD_GET_CHAR()
{
	char matrix[4][4]={{'7','4','1','c'},{'8','5','2','0'},{'9','6','3','='},{'/','*','-','+'}};
	char input = '\0';
	int i,j;

	int input_pins[4] = {GPIO_PIN_0,GPIO_PIN_1,GPIO_PIN_3,GPIO_PIN_4};
	int output_pins[4] = {GPIO_PIN_5,GPIO_PIN_6,GPIO_PIN_7,GPIO_PIN_8};
	while(1)
	{
		for(i=0;i<4;i++)
		{
			MCAL_GPIO_WritePin(KEYPAD_PORT,output_pins[0],1);
			MCAL_GPIO_WritePin(KEYPAD_PORT,output_pins[1],1);
			MCAL_GPIO_WritePin(KEYPAD_PORT,output_pins[2],1);
			MCAL_GPIO_WritePin(KEYPAD_PORT,output_pins[3],1);
			MCAL_GPIO_WritePin(KEYPAD_PORT,output_pins[i],0);
			for(j=0;j<4;j++)
			{
				if(MCAL_GPIO_ReadPin(KEYPAD_PORT,input_pins[j])==0)
				{
					while(MCAL_GPIO_ReadPin(KEYPAD_PORT,input_pins[j])==0);
					input = matrix[i][j];
					return input;
				}
			}
		}
	}
}
