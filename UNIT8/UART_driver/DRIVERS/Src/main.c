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
#include "EXTI.h"
#include "USART.h"

uint16_t data;

void UART_IRQ_CALLBACK(void)
{
	MCAL_UART_RECEIVE(USART1, &data);
	MCAL_UART_TRANSMIT(USART1, &data);
}

int main(void)
{
	//RCC ENABLE:
	RCC_PORTA_CLK_EN();
	RCC_PORTB_CLK_EN();
	RCC_AFIO_CLK_EN();

	USART_Config_t UART_Config;
	UART_Config.UART_IRQ = UART_IRQ_RXNE;
	UART_Config.PF_IRQ_CallBack = UART_IRQ_CALLBACK;
	UART_Config.BAUD_RATE = BAUD_RATE_115200;
	UART_Config.DATA_BITS = DATA_BITS_Eight;
	UART_Config.PARITY_BITS = PARITY_BITS_Disabled;
	UART_Config.FLOW_CONTROL = FLOW_CONTROL_DISABLE;
	UART_Config.STOP_BITS = STOP_BITS_ONE;
	UART_Config.USART_MODE = USART_MODE_TX_RX;
	UART_Config.POLLING = POLING_DISABLE;

	MCAL_UART_Init(USART1,&UART_Config);
	MCAL_UART_GPIO_SET_PINS(USART1);



	/* Loop forever */
	while(1)
	{

	}
}
