/*
 * SPI.c
 *
 *  Created on: 21 Oct 2024
 *      Author: mahmo
 */


//==============================================================
//INCLUDES:
//==============================================================

#include "SPI.h"

//==============================================================
//GENERIC VARIABLES:
//==============================================================

SPI_Config_t* GLOBAL_SPIx_Config[2] = {NULL,NULL};

//==============================================================
//GENERIC MACROS:
//==============================================================

#define SPI1_INDEX										0
#define SPI2_INDEX										1

#define SPI_SR_TXE										(uint8_t)(0x02)
#define SPI_SR_RXNE										(uint8_t)(0x01)

//==============================================================
//APIs Supported by "MCAL SPI DRIVER":
//==============================================================

/*
 * --------------------------------------------------------------
 * FUNCTION:       MCAL_SPI_INIT
 * DESCRIPTION:    Initializes the specified SPI instance.
 * PARAMETER (IN): SPIx - Pointer to the SPI instance (SPI1 or SPI2).
 * PARAMETER (IN): SPI_CONFIG - Pointer to the SPI configuration structure.
 * RETURN VALUE:   void
 * NOTES:          Configures SPI mode, clock settings, data size,
 *                 frame format, NSS settings, baud rate, and interrupts.
 * --------------------------------------------------------------
 */

void MCAL_SPI_INIT(SPI_typedef *SPIx, SPI_Config_t* SPI_CONFIG)
{
	uint16_t CR1_temp = 0;
	uint16_t CR2_temp = 0;

	//Enable the SPI CLOCK and Initialize Global SPI config:
	if(SPIx == SPI1)
	{
		GLOBAL_SPIx_Config[SPI1_INDEX] = SPI_CONFIG;
		RCC_SPI1_CLK_EN();
	}
	else if(SPIx == SPI2)
	{
		GLOBAL_SPIx_Config[SPI2_INDEX] = SPI_CONFIG;
		RCC_SPI2_CLK_EN();
	}
	//Set the data size:
	CR1_temp |= SPI_CONFIG->DATA_SIZE;

	//Set the clock phase:
	CR1_temp |= SPI_CONFIG->CLOCK_PHASE;

	//Set the clock polarity:
	CR1_temp |= SPI_CONFIG->CLOCK_POLARITY;

	//Set the frame format:
	CR1_temp |=	SPI_CONFIG->FRAME_FORMAT;

	//NSS:
	if(SPI_CONFIG->NSS==NSS_HARDWARE_MASTER_SSO_ENABLE)
	{
		CR2_temp |= SPI_CONFIG->NSS;
	}
	else if(SPI_CONFIG->NSS==NSS_HARDWARE_MASTER_SSO_DISABLE)
	{
		CR2_temp &= SPI_CONFIG->NSS;
	}
	else
	{
		CR1_temp |= SPI_CONFIG->NSS;
	}

	//Set the baud rate:
	CR1_temp |= SPI_CONFIG->SPI_BAUD_RATE;

	//Enable interrupts:
	if(SPI_CONFIG->SPI_IRQ != SPI_IRQ_DISABLE)
	{
		CR2_temp |= SPI_CONFIG->SPI_IRQ;
		if(SPIx == SPI1)
		{
			NVIC_SPI1_IRQ_ENABLE;
		}
		else if(SPIx == SPI2)
		{
			NVIC_SPI2_IRQ_ENABLE;
		}
	}

	//Select SPI communication mode:
	CR1_temp |= SPI_CONFIG->COMMUNICATION_MODE;

	//Master or Slave selection:
	CR1_temp |= SPI_CONFIG->DEVICE_MODE;

	//Enable the SPI:
	CR1_temp |= (1<<6);

	//Set the registers:
	SPIx->CR1 = CR1_temp;
	SPIx->CR2 = CR2_temp;
}

/*
 * --------------------------------------------------------------
 * FUNCTION:       MCAL_SPI_DeINIT
 * DESCRIPTION:    De-initializes the specified SPI instance.
 * PARAMETER (IN): SPIx - Pointer to the SPI instance (SPI1 or SPI2).
 * RETURN VALUE:   void
 * NOTES:          Resets the SPI clock and disables its IRQ.
 * --------------------------------------------------------------
 */

void MCAL_SPI_DeINIT(SPI_typedef *SPIx)
{
	if(SPIx == SPI1)
	{
		NVIC_SPI1_IRQ_DISABLE;
		RCC_SPI1_CLK_RESET();
	}
	else if(SPIx == SPI2)
	{
		NVIC_SPI2_IRQ_DISABLE;
		RCC_SPI2_CLK_RESET();
	}
}

/*
 * --------------------------------------------------------------
 * FUNCTION:       MCAL_SPI_SEND_DATA
 * DESCRIPTION:    Sends data through the specified SPI instance.
 * PARAMETER (IN): SPIx - Pointer to the SPI instance (SPI1 or SPI2).
 * PARAMETER (IN): pTxBuffer - Pointer to the data buffer to be transmitted.
 * PARAMETER (IN): POLLING_EN - Enables or disables polling mode.
 * RETURN VALUE:   void
 * NOTES:          Supports polling-based transmission.
 * --------------------------------------------------------------
 */

void MCAL_SPI_SEND_DATA(SPI_typedef *SPIx,uint16_t *pTxBuffer,enum POLLING POLLING_EN)
{
	if(POLLING_EN == POLLING_ENABLE)
		while(!((SPIx)->SR & SPI_SR_TXE));

	SPIx->DR = *pTxBuffer;
}

/*
 * --------------------------------------------------------------
 * FUNCTION:        MCAL_SPI_RECEIVE_DATA
 * DESCRIPTION:     Receives data from the specified SPI instance.
 * PARAMETER (IN):  SPIx - Pointer to the SPI instance (SPI1 or SPI2).
 * PARAMETER (OUT): pTxBuffer - Pointer to the buffer to store received data.
 * PARAMETER (IN):  POLLING_EN - Enables or disables polling mode.
 * RETURN VALUE:    void
 * NOTES:           Supports polling-based reception.
 * --------------------------------------------------------------
 */

void MCAL_SPI_RECEIVE_DATA(SPI_typedef *SPIx,uint16_t *pTxBuffer,enum POLLING POLLING_EN)
{
	if(POLLING_EN == POLLING_ENABLE)
		while(!((SPIx)->SR & SPI_SR_RXNE));

	*pTxBuffer = SPIx->DR;
}

/*
 * --------------------------------------------------------------
 * FUNCTION:           MCAL_SPI_SEND_RECEIVE_DATA
 * DESCRIPTION:        Sends and receives data through the specified SPI instance.
 * PARAMETER (IN):     SPIx - Pointer to the SPI instance (SPI1 or SPI2).
 * PARAMETER (IN/OUT): pTxBuffer - Pointer to the buffer for transmission and reception.
 * PARAMETER (IN):     POLLING_EN - Enables or disables polling mode.
 * RETURN VALUE:       void
 * NOTES:              Supports full-duplex communication.
 * --------------------------------------------------------------
 */

void MCAL_SPI_SEND_RECEIVE_DATA(SPI_typedef *SPIx,uint16_t *pTxBuffer,enum POLLING POLLING_EN)
{
	if(POLLING_EN == POLLING_ENABLE)
		while(!((SPIx)->SR & SPI_SR_TXE));
	SPIx->DR = *pTxBuffer;
	if(POLLING_EN == POLLING_ENABLE)
		while(!((SPIx)->SR & SPI_SR_RXNE));
	*pTxBuffer = SPIx->DR;
}

/*
 * --------------------------------------------------------------
 * FUNCTION:       MCAL_SPI_GPIO_SET_PINS
 * DESCRIPTION:    Configures the GPIO pins for the specified SPI instance.
 * PARAMETER (IN): SPIx - Pointer to the SPI instance (SPI1 or SPI2).
 * RETURN VALUE:   void
 * NOTES:          Sets up GPIO configurations for SPI communication
 *                 in master or slave mode.
 * --------------------------------------------------------------
 */

void MCAL_SPI_GPIO_SET_PINS(SPI_typedef *SPIx)
{
	GPIO_PinConfig_t PIN_Config;
	if(SPIx==SPI1)
	{
		if(GLOBAL_SPIx_Config[SPI1_INDEX]->DEVICE_MODE==DEVICE_MODE_MASTER)
		{
			//NSS PIN SETUP: GPIO PORTA PIN4:
			if(GLOBAL_SPIx_Config[SPI1_INDEX]->NSS==NSS_HARDWARE_MASTER_SSO_DISABLE)
			{
				PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_4;
				PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
				MCAL_GPIO_Init(PORTA, &PIN_Config);
			}
			else if(GLOBAL_SPIx_Config[SPI1_INDEX]->NSS==NSS_HARDWARE_MASTER_SSO_ENABLE)
			{
				PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_4;
				PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
				PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
				MCAL_GPIO_Init(PORTA, &PIN_Config);
			}
			//SCK PIN SETUP: GPIO PORTA PIN5:
			PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_5;
			PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
			PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
			MCAL_GPIO_Init(PORTA, &PIN_Config);

			//MISO PIN SETUP: GPIO PORTA PIN6: (SUPPORTS ONLY FULL DUPLEX)
			PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_6;
			PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
			MCAL_GPIO_Init(PORTA, &PIN_Config);

			//MOSI PIN SETUP: GPIO PORTA PIN7: (SUPPORTS ONLY FULL DUPLEX)
			PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_7;
			PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
			PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
			MCAL_GPIO_Init(PORTA, &PIN_Config);
		}
		else
		{
			if(GLOBAL_SPIx_Config[SPI1_INDEX]->NSS == NSS_HARDWARE_SLAVE)
			{
				//NSS PIN SETUP: GPIO PORTA PIN4:
				PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_4;
				PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
				MCAL_GPIO_Init(PORTA, &PIN_Config);

				//SCK PIN SETUP: GPIO PORTA PIN5:
				PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_5;
				PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
				MCAL_GPIO_Init(PORTA, &PIN_Config);

				//MISO PIN SETUP: GPIO PORTA PIN6: (SUPPORTS ONLY FULL DUPLEX)
				PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_6;
				PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
				PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
				MCAL_GPIO_Init(PORTA, &PIN_Config);

				//MOSI PIN SETUP: GPIO PORTA PIN7: (SUPPORTS ONLY FULL DUPLEX)
				PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_7;
				PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
				MCAL_GPIO_Init(PORTA, &PIN_Config);

			}
		}
	}

	if(SPIx==SPI2)
	{
		if(GLOBAL_SPIx_Config[SPI2_INDEX]->DEVICE_MODE==DEVICE_MODE_MASTER)
		{
			//NSS PIN SETUP: GPIO PORTB PIN12:
			if(GLOBAL_SPIx_Config[SPI2_INDEX]->NSS==NSS_HARDWARE_MASTER_SSO_DISABLE)
			{
				PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_12;
				PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
				MCAL_GPIO_Init(PORTB, &PIN_Config);
			}
			else if(GLOBAL_SPIx_Config[SPI2_INDEX]->NSS==NSS_HARDWARE_MASTER_SSO_ENABLE)
			{
				PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_12;
				PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
				PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
				MCAL_GPIO_Init(PORTB, &PIN_Config);
			}

			//SCK PIN SETUP: GPIO PORTB PIN13:
			PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_13;
			PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
			PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
			MCAL_GPIO_Init(PORTB, &PIN_Config);

			//MISO PIN SETUP: GPIO PORTB PIN14: (SUPPORTS ONLY FULL DUPLEX)
			PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_14;
			PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
			MCAL_GPIO_Init(PORTB, &PIN_Config);

			//MOSI PIN SETUP: GPIO PORTB PIN15: (SUPPORTS ONLY FULL DUPLEX)
			PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_15;
			PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
			PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
			MCAL_GPIO_Init(PORTB, &PIN_Config);
		}
		else
		{
			if(GLOBAL_SPIx_Config[SPI1_INDEX]->NSS == NSS_HARDWARE_SLAVE)
			{
				//NSS PIN SETUP: GPIO PORTB PIN12:
				PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_12;
				PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
				MCAL_GPIO_Init(PORTB, &PIN_Config);

				//SCK PIN SETUP: GPIO PORTB PIN13:
				PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_13;
				PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
				MCAL_GPIO_Init(PORTB, &PIN_Config);

				//MISO PIN SETUP: GPIO PORTB PIN14: (SUPPORTS ONLY FULL DUPLEX)
				PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_14;
				PIN_Config.GPIO_MODE = AFIO_MODE_OUT_PUSH_PULL;
				PIN_Config.GPIO_OUTPUT_FREQ = GPIO_OUTPUT_FREQ_10MHz;
				MCAL_GPIO_Init(PORTB, &PIN_Config);

				//MOSI PIN SETUP: GPIO PORTB PIN15: (SUPPORTS ONLY FULL DUPLEX)
				PIN_Config.GPIO_PIN_NUMBER = GPIO_PIN_15;
				PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
				MCAL_GPIO_Init(PORTB, &PIN_Config);

			}
		}
	}
}

/*
 * --------------------------------------------------------------
 * FUNCTION:       SPI1_IRQHandler
 * DESCRIPTION:    SPI1 interrupt handler.
 * PARAMETER (IN): None
 * RETURN VALUE:   void
 * NOTES:          Handles SPI1 transmission, reception, and error interrupts.
 * --------------------------------------------------------------
 */

void SPI1_IRQHandler(void)
{
	struct SPI_IRQ_SRC IRQ_SRC;
	IRQ_SRC.TXE =  ((SPI1->SR & (1<<1)) >> 1 );
	IRQ_SRC.RXNE = ((SPI1->SR & (1<<0)) >> 0 );
	IRQ_SRC.ERRI = ((SPI1->SR & (1<<4)) >> 4 );
	GLOBAL_SPIx_Config[SPI1_INDEX]->P_IRQ_Callback(IRQ_SRC);
}

/*
 * --------------------------------------------------------------
 * FUNCTION:       SPI2_IRQHandler
 * DESCRIPTION:    SPI2 interrupt handler.
 * PARAMETER (IN): None
 * RETURN VALUE:   void
 * NOTES:          Handles SPI2 transmission, reception, and error interrupts.
 * --------------------------------------------------------------
 */

void SPI2_IRQHandler(void)
{
	struct SPI_IRQ_SRC IRQ_SRC;
	IRQ_SRC.TXE =  ((SPI2->SR & (1<<1)) >> 1 );
	IRQ_SRC.RXNE = ((SPI2->SR & (1<<0)) >> 0 );
	IRQ_SRC.ERRI = ((SPI2->SR & (1<<4)) >> 4 );
	GLOBAL_SPIx_Config[SPI2_INDEX]->P_IRQ_Callback(IRQ_SRC);
}
