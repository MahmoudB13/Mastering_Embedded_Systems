/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include "GPIO.h"
#include "STM32F103C6.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "Seven_segment.h"

void RCC_Init()
{
	//PORTA RCC CLOCK ENABLE:
	RCC_PORTA_CLK_EN();
	//PORTB RCC CLOCK ENABLE:
	RCC_PORTB_CLK_EN();
}


int main(void)
{
	RCC_Init();
	KEYPAD_INIT();
	LCD_INIT();
	SEVEN_SEGMENT_Init();
	/* Loop forever */
	while(1)
	{
		SEVEN_SEGMENT_DISPLAY(FOUR);
	}
}
