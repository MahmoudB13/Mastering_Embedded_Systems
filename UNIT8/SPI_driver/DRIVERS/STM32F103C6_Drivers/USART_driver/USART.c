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

USART_Config_t* GLOBAL_UART_Config = NULL;
USART_Config_t* GLOBAL_UARTx_Config[3] = {NULL,NULL,NULL};

//==============================================================
//GENERIC VARIABLES:
//==============================================================

#define USART1_INDEX								0
#define USART2_INDEX								1
#define USART3_INDEX								2

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
		GLOBAL_UARTx_Config[USART1_INDEX] = UART_Config;
		RCC_USART1_CLK_EN();
	}
	else if(USARTx==USART2)
	{
		GLOBAL_UARTx_Config[USART2_INDEX] = UART_Config;
		RCC_USART2_CLK_EN();
	}
	else if(USARTx==USART3)
	{
		GLOBAL_UARTx_Config[USART3_INDEX] = UART_Config;
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

/*
 * --------------------------------------------------------------
 * FUNCTION:       MCAL_UART_DeInit
 * DESCRIPTION:    De-initializes the specified USART instance.
 * PARAMETER (IN): USARTx - Pointer to the USART instance (USART1, USART2, or USART3).
 * RETURN VALUE:   void
 * NOTES:          Resets the USART clock and disables its IRQ.
 * --------------------------------------------------------------
 */

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

/*
 * --------------------------------------------------------------
 * FUNCTION:       MCAL_UART_TRANSMIT
 * DESCRIPTION:    Sends data via the specified USART instance.
 * PARAMETER (IN): USARTx - Pointer to the USART instance.
 * PARAMETER (IN): TX_Buffer - Pointer to the data buffer to be transmitted.
 * PARAMETER (IN): POLLING_EN - Enum value indicating whether polling is enabled or disabled.
 * RETURN VALUE:   void
 * NOTES:          Supports both 8-bit and 9-bit data transmission.
 * --------------------------------------------------------------
 */

void MCAL_UART_TRANSMIT(USART_typedef *USARTx,uint16_t *TX_Buffer,enum POLLING POLLING_EN)
{
	if(POLLING_EN == POLLING_ENABLE)
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

/*
 * --------------------------------------------------------------
 * FUNCTION:        MCAL_UART_RECEIVE
 * DESCRIPTION:     Receives data from the specified USART instance.
 * PARAMETER (IN):  USARTx - Pointer to the USART instance.
 * PARAMETER (OUT): RX_Buffer - Pointer to store the received data.
 * PARAMETER (IN):  POLLING_EN - Enum value indicating whether polling is enabled or disabled.
 * RETURN VALUE:    void
 * NOTES:           Supports both 8-bit and 9-bit data reception with optional parity handling.
 * --------------------------------------------------------------
 */

void MCAL_UART_RECEIVE(USART_typedef *USARTx,uint16_t *RX_Buffer,enum POLLING POLLING_EN)
{
	if(POLLING_EN == POLLING_ENABLE)
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

/*
 * --------------------------------------------------------------
 * FUNCTION:       MCAL_UART_WAIT_TC
 * DESCRIPTION:    Waits until the transmission is complete.
 * PARAMETER (IN): USARTx - Pointer to the USART instance.
 * RETURN VALUE:   void
 * NOTES:          Blocks execution until the transmission complete (TC) flag is set.
 * --------------------------------------------------------------
 */

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
		// Configure TX pin (PA9) as Alternate Function Push-Pull Output
		PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_9;
		PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
		PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
		MCAL_GPIO_Init(PORTA,&PIN_Config);

		// Configure RX pin (PA10) as Floating Input
		PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_10;
		PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
		MCAL_GPIO_Init(PORTA,&PIN_Config);

		// Configure CTS (PA11) if flow control is enabled
		if(GLOBAL_UARTx_Config[USART1_INDEX]->FLOW_CONTROL==FLOW_CONTROL_CTS || GLOBAL_UARTx_Config[USART1_INDEX]->FLOW_CONTROL==FLOW_CONTROL_CTS_RTS)
		{
			PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_11;
			PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
			MCAL_GPIO_Init(PORTA,&PIN_Config);
		}

		// Configure RTS (PA12) if flow control is enabled
		if(GLOBAL_UARTx_Config[USART1_INDEX]->FLOW_CONTROL==FLOW_CONTROL_RTS || GLOBAL_UARTx_Config[USART1_INDEX]->FLOW_CONTROL==FLOW_CONTROL_CTS_RTS)
		{
			PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_12;
			PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
			PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
			MCAL_GPIO_Init(PORTA,&PIN_Config);
		}
	}
	else if(USARTx==USART2)
	{
		// Configure TX pin (PA2) as Alternate Function Push-Pull Output
		PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_2;
		PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
		PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
		MCAL_GPIO_Init(PORTA,&PIN_Config);

		// Configure RX pin (PA3) as Floating Input
		PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_3;
		PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
		MCAL_GPIO_Init(PORTA,&PIN_Config);

		// Configure CTS (PA0) if flow control is enabled
		if(GLOBAL_UARTx_Config[USART2_INDEX]->FLOW_CONTROL==FLOW_CONTROL_CTS || GLOBAL_UARTx_Config[USART2_INDEX]->FLOW_CONTROL==FLOW_CONTROL_CTS_RTS)
		{
			PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_0;
			PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
			MCAL_GPIO_Init(PORTA,&PIN_Config);
		}

		// Configure RTS (PA1) if flow control is enabled
		if(GLOBAL_UARTx_Config[USART2_INDEX]->FLOW_CONTROL==FLOW_CONTROL_RTS || GLOBAL_UARTx_Config[USART2_INDEX]->FLOW_CONTROL==FLOW_CONTROL_CTS_RTS)
		{
			PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_1;
			PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
			PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
			MCAL_GPIO_Init(PORTA,&PIN_Config);
		}
	}
	else if(USARTx==USART3)
	{
		// Configure TX pin (PB10) as Alternate Function Push-Pull Output
		PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_10;
		PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
		PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
		MCAL_GPIO_Init(PORTB,&PIN_Config);

		// Configure RX pin (PB11) as Floating Input
		PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_11;
		PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
		MCAL_GPIO_Init(PORTB,&PIN_Config);

		// Configure CTS (PB13) if flow control is enabled
		if(GLOBAL_UARTx_Config[USART3_INDEX]->FLOW_CONTROL==FLOW_CONTROL_CTS || GLOBAL_UARTx_Config[USART3_INDEX]->FLOW_CONTROL==FLOW_CONTROL_CTS_RTS)
		{
			PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_13;
			PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
			MCAL_GPIO_Init(PORTB,&PIN_Config);
		}

		// Configure RTS (PB14) if flow control is enabled
		if(GLOBAL_UARTx_Config[USART3_INDEX]->FLOW_CONTROL==FLOW_CONTROL_RTS || GLOBAL_UARTx_Config[USART3_INDEX]->FLOW_CONTROL==FLOW_CONTROL_CTS_RTS)
		{
			PIN_Config.GPIO_PIN_NUMBER	= GPIO_PIN_14;
			PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
			PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
			MCAL_GPIO_Init(PORTB,&PIN_Config);
		}
	}
}

/*
 * --------------------------------------------------------------
 * FUNCTION:       USART1_IRQHandler
 * DESCRIPTION:    Interrupt handler for USART1.
 * RETURN VALUE:   void
 * NOTES:          Calls the user-defined IRQ callback function.
 * --------------------------------------------------------------
 */

void USART1_IRQHandler(void)
{
	GLOBAL_UARTx_Config[USART1_INDEX]->PF_IRQ_CallBack();
}

/*
 * --------------------------------------------------------------
 * FUNCTION:       USART2_IRQHandler
 * DESCRIPTION:    Interrupt handler for USART2.
 * RETURN VALUE:   void
 * NOTES:          Calls the user-defined IRQ callback function.
 * --------------------------------------------------------------
 */

void USART2_IRQHandler(void)
{
	GLOBAL_UARTx_Config[USART2_INDEX]->PF_IRQ_CallBack();
}

/*
 * --------------------------------------------------------------
 * FUNCTION:       USART3_IRQHandler
 * DESCRIPTION:    Interrupt handler for USART3.
 * RETURN VALUE:   void
 * NOTES:          Calls the user-defined IRQ callback function.
 * --------------------------------------------------------------
 */

void USART3_IRQHandler(void)
{
	GLOBAL_UARTx_Config[USART3_INDEX]->PF_IRQ_CallBack();
}
