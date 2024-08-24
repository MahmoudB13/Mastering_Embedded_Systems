/*
 * USART.c
 *
 *  Created on: 19 Aug 2024
 *      Author: Mahmoud
 */

//==============================================================
//INCLUDES:
//==============================================================

#include "USART.h"

//==============================================================
//GENERIC VARIABLES:
//==============================================================

USART_Config_t *GLOBAL_UART_Config = NULL;

//==============================================================
//APIs Supported by "MCAL USART DRIVER":
//==============================================================


/*
 * --------------------------------------------------------------
 * FUNCTION: 		MCAL_UART_Init
 * DISCRIPTION: 	Initializes USARTx.
 * PARAMETER (IN): 	USARTx: where x can be (1->3 depending on device used) to select the USART Instant.
 * PARAMETER (IN): 	UART_Config: a pointer to USART_Config_t structure.
 * RETURN VALUE: 	void
 * NOTES: 			ONLY SUPPORTS ASYNC 8 MHz COMMUNICATION.
 * --------------------------------------------------------------
 */

void MCAL_UART_Init(USART_typedef *USARTx,USART_Config_t *UART_Config)
{
	GLOBAL_UART_Config = UART_Config;
	//Enable the USART CLOCK:
	if(USARTx==USART1)
	{
		RCC_USART1_CLK_EN();
	}
	else if(USARTx==USART2)
	{
		RCC_USART2_CLK_EN();
	}
	else if(USARTx==USART3)
	{
		RCC_USART3_CLK_EN();
	}

	//Enable the USART by writing the UE bit in USART_CR1 register to 1:
	USARTx->CR1 |= (1 << 13);

	//Program the M bit in USART_CR1 to define the word length:
	USARTx->CR1 |= UART_Config->DATA_BITS;

	//Program the number of stop bits in USART_CR2:
	USARTx->CR2 |= UART_Config->STOP_BITS;

	//Program the PCE & PS bits in USART_CR1 to enable parity:
	USARTx->CR1 |= UART_Config->PARITY_BITS;

	//Select the desired baud rate using the USART_BRR register:
	uint32_t CLK;
	if(USARTx==USART1)
	{
		CLK = RCC_GET_PCLK2_FREQ();
	}
	else
	{
		CLK = RCC_GET_PCLK1_FREQ();
	}

	USARTx->BRR = UART_BRR_Register(CLK, UART_Config->BAUD_RATE);


	//Select the TE & RE bits in USART_CR1 to select transmission mode:
	USARTx->CR1 |= UART_Config->USART_MODE;

	//Program the RTSE & CTSE bits in USART_CR3 to enable flow control:
	USARTx->CR3 |= UART_Config->FLOW_CONTROL;

	if(UART_Config->UART_IRQ!=UART_IRQ_DISABLE)
	{
		USARTx->CR1 |= UART_Config->UART_IRQ;
		if(USARTx==USART1)
		{
			NVIC_USART1_IRQ_ENABLE;
		}
		else if(USARTx==USART2)
		{
			NVIC_USART2_IRQ_ENABLE;
		}
		else if(USARTx==USART3)
		{
			NVIC_USART3_IRQ_ENABLE;
		}
	}
}


void MCAL_UART_DeInit(USART_typedef *USARTx)
{
	if(USARTx==USART1)
	{
		RCC_USART1_CLK_RESET();
		NVIC_USART1_IRQ_DISABLE;
	}
	else if(USARTx==USART2)
	{
		RCC_USART2_CLK_RESET();
		NVIC_USART2_IRQ_DISABLE;
	}
	else if(USARTx==USART3)
	{
		RCC_USART3_CLK_RESET();
		NVIC_USART3_IRQ_DISABLE;
	}
}


void MCAL_UART_TRANSMIT(USART_typedef *USARTx,uint16_t *TX_Buffer)
{
	if(GLOBAL_UART_Config->POLLING==POLING_ENABLE)
	{
		while(!(USARTx->SR & 1<<7));
	}

	if(GLOBAL_UART_Config->DATA_BITS==DATA_BITS_Eight)
	{
		USARTx->DR = (*TX_Buffer & (uint8_t)0xFF);
	}
	else
	{
		USARTx->DR = (*TX_Buffer & (uint16_t)0x1FF);
	}
}

void MCAL_UART_RECEIVE(USART_typedef *USARTx,uint16_t *RX_Buffer)
{
	if(GLOBAL_UART_Config->POLLING==POLING_ENABLE)
	{
		while(!(USARTx->SR & 1<<5));
	}
	if(GLOBAL_UART_Config->DATA_BITS==DATA_BITS_Eight)
	{
		if(GLOBAL_UART_Config->PARITY_BITS==PARITY_BITS_Disabled)
		{
			*RX_Buffer = (USARTx->DR & (uint8_t)0xFF);
		}
		else
		{
			*RX_Buffer = (USARTx->DR & (uint8_t)0x7F);
		}
	}
	else
	{
		if(GLOBAL_UART_Config->PARITY_BITS==PARITY_BITS_Disabled)
		{
			*RX_Buffer = USARTx->DR;
		}
		else
		{
			*RX_Buffer = (USARTx->DR & (uint8_t)0xFF);
		}
	}
}



void MCAL_UART_WAIT_TC(USART_typedef *USARTx)
{
	while(!(USARTx->SR & 1<<6));
}


/*
 * --------------------------------------------------------------
 * FUNCTION: 		MCAL_UART_GPIO_SET_PINS
 * DISCRIPTION: 	Initializes USARTx PINS.
 * PARAMETER (IN): 	USARTx: where x can be (1->3 depending on device used) to select the USART Instant.
 * RETURN VALUE: 	void
 * NOTES:
 * --------------------------------------------------------------
 */
void MCAL_UART_GPIO_SET_PINS(USART_typedef *USARTx)
{
	GPIO_PinConfig_t PIN_Config;
	if(USARTx==USART1)
	{
		//TX
		PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_9;
		PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
		PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
		MCAL_GPIO_Init(PORTA,&PIN_Config);

		//RX
		PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_10;
		PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
		MCAL_GPIO_Init(PORTA,&PIN_Config);

		if(GLOBAL_UART_Config->FLOW_CONTROL==FLOW_CONTROL_CTS || GLOBAL_UART_Config->FLOW_CONTROL==FLOW_CONTROL_CTS_RTS)
		{
			PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_11;
			PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
			MCAL_GPIO_Init(PORTA,&PIN_Config);
		}
		else if(GLOBAL_UART_Config->FLOW_CONTROL==FLOW_CONTROL_RTS || GLOBAL_UART_Config->FLOW_CONTROL==FLOW_CONTROL_CTS_RTS)
		{
			PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_12;
			PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
			PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
			MCAL_GPIO_Init(PORTA,&PIN_Config);
		}
	}
	else if(USARTx==USART2)
	{
		//TX
		PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_2;
		PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
		PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
		MCAL_GPIO_Init(PORTA,&PIN_Config);

		//RX
		PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_3;
		PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
		MCAL_GPIO_Init(PORTA,&PIN_Config);
		if(GLOBAL_UART_Config->FLOW_CONTROL==FLOW_CONTROL_CTS || GLOBAL_UART_Config->FLOW_CONTROL==FLOW_CONTROL_CTS_RTS)
		{
			PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_0;
			PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
			MCAL_GPIO_Init(PORTA,&PIN_Config);
		}
		else if(GLOBAL_UART_Config->FLOW_CONTROL==FLOW_CONTROL_RTS || GLOBAL_UART_Config->FLOW_CONTROL==FLOW_CONTROL_CTS_RTS)
		{
			PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_1;
			PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
			PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
			MCAL_GPIO_Init(PORTA,&PIN_Config);
		}
	}
	else if(USARTx==USART3)
	{
		//TX
		PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_10;
		PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
		PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
		MCAL_GPIO_Init(PORTB,&PIN_Config);

		//RX
		PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_11;
		PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
		MCAL_GPIO_Init(PORTB,&PIN_Config);
		if(GLOBAL_UART_Config->FLOW_CONTROL==FLOW_CONTROL_CTS || GLOBAL_UART_Config->FLOW_CONTROL==FLOW_CONTROL_CTS_RTS)
		{
			PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_13;
			PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
			MCAL_GPIO_Init(PORTB,&PIN_Config);
		}
		else if(GLOBAL_UART_Config->FLOW_CONTROL==FLOW_CONTROL_RTS || GLOBAL_UART_Config->FLOW_CONTROL==FLOW_CONTROL_CTS_RTS)
		{
			PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_14;
			PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
			PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
			MCAL_GPIO_Init(PORTB,&PIN_Config);
		}
	}
}


void USART1_IRQHandler(void)
{
	GLOBAL_UART_Config->PF_IRQ_CallBack();
}
void USART2_IRQHandler(void)
{
	GLOBAL_UART_Config->PF_IRQ_CallBack();
}
void USART3_IRQHandler(void)
{
	GLOBAL_UART_Config->PF_IRQ_CallBack();
}
