/*
 * USART.h
 *
 *  Created on: 19 Aug 2024
 *      Author: Mahmoud
 */

#ifndef USART_DRIVER_USART_H_
#define USART_DRIVER_USART_H_

//--------------------------------------------------------------
//INCLUDES:
//--------------------------------------------------------------

#include "STM32F103C6.h"
#include "GPIO.h"
#include "RCC.h"

//--------------------------------------------------------------
//CONFIG STRUCTURE:
//--------------------------------------------------------------

typedef struct
{
	uint8_t DATA_BITS;
	//TO SPECIFY THE NUMBER OF BITS TO BE TRANSMITTED.
	//THIS PARAMETER MUST BE SET BASED ON //@REF DATA_BITS_define.

	uint8_t PARITY_BITS;
	//TO SPECIFY THE PARITY BITS.
	//THIS PARAMETER MUST BE SET BASED ON //@REF PARITY_BITS_define.

	uint8_t STOP_BITS;
	//TO SPECIFY THE STOP BITS.
	//THIS PARAMETER MUST BE SET BASED ON //@REF STOP_BITS_define.

	uint32_t BAUD_RATE;
	//TO SPECIFY THE BAUD RATE OF THE TRANSMISSION.
	//THIS PARAMETER MUST BE SET BASED ON //@REF BAUD_RATE_define.

	uint8_t USART_MODE;
	//TO SPECIFY THE MODE OF THE USART.
	//THIS PARAMETER MUST BE SET BASED ON //@REF USART_MODE_define.

	uint8_t FLOW_CONTROL;
	//TO ENABLE AND DISABLE THE FLOW CONTROL OF THE USART.
	//THIS PARAMETER MUST BE SET BASED ON //@REF FLOW_CONTROL_define.

	uint8_t UART_IRQ;
	//TO ENABLE AND DISABLE THE INTERRUPTS OF THE USART.
	//THIS PARAMETER MUST BE SET BASED ON //@REF UART_IRQ_define.

	void (*PF_IRQ_CallBack)(void);
	//PF_IRQ_CallBack this is a pointer to a function we need it executed when the interrupt occurred.

}USART_Config_t;
//==============================================================

//--------------------------------------------------------------
//Macros Configuration References
//--------------------------------------------------------------

//@REF DATA_BITS_define:
#define DATA_BITS_Eight					(uint32_t)(0)
#define DATA_BITS_Nine					(uint32_t)(1 << 12)

//--------------------------------------------------------------

//@REF PARITY_BITS_define:
#define PARITY_BITS_Disabled			(uint32_t)(0)
#define PARITY_BITS_Even				(uint32_t)(1 << 10)
#define PARITY_BITS_Odd					(uint32_t)((1 << 10) | (1 << 9))

//--------------------------------------------------------------

//@REF STOP_BITS_define:
#define STOP_BITS_ONE					(uint32_t)(0b00 << 12)
#define STOP_BITS_HALF					(uint32_t)(0b01 << 12)
#define STOP_BITS_TWO					(uint32_t)(0b10 << 12)
#define STOP_BITS_ONE_HALF				(uint32_t)(0b11 << 12)

//--------------------------------------------------------------

//@REF BAUD_RATE_define:

#define BAUD_RATE_2400					2400
#define BAUD_RATE_9600					9600
#define BAUD_RATE_19200					19200
#define BAUD_RATE_57600					57600
#define BAUD_RATE_115200				115200
#define BAUD_RATE_230400				230400
#define BAUD_RATE_460800				460800
#define BAUD_RATE_921600				921600
#define BAUD_RATE_2250000				2250000
#define BAUD_RATE_4500000				4500000

//--------------------------------------------------------------

//@REF USART_MODE_define:
#define USART_MODE_TX					(uint32_t)(1 << 3)
#define USART_MODE_RX					(uint32_t)(1 << 2)
#define USART_MODE_TX_RX				(uint32_t)((1 << 3) | (1 << 2))

//--------------------------------------------------------------

//@REF FLOW_CONTROL_define:
#define FLOW_CONTROL_DISABLE			(uint32_t)(0)
#define FLOW_CONTROL_RTS				(uint32_t)(1 << 8)
#define FLOW_CONTROL_CTS				(uint32_t)(1 << 9)
#define FLOW_CONTROL_CTS_RTS			(uint32_t)((1 << 9) | (1 << 8))

//--------------------------------------------------------------

//@REF UART_IRQ_define:
#define UART_IRQ_DISABLE				(uint32_t)(0)
#define UART_IRQ_RXNE					(uint32_t)(1<<5)
#define UART_IRQ_TC						(uint32_t)(1<<6)
#define UART_IRQ_TXE					(uint32_t)(1<<7)
#define UART_IRQ_PE						(uint32_t)(1<<8)

//--------------------------------------------------------------


#define USARTDIV(_PCLK_, _BAUDRATE_)						(uint32_t)(_PCLK_/(16 * _BAUDRATE_))
#define USARTDIV_MUL100(_PCLK_, _BAUDRATE_)					(uint32_t)((25 * _PCLK_) / (4 * _BAUDRATE_))
#define Mantissa_MUL100(_PCLK_, _BAUDRATE_)					(uint32_t)(USARTDIV(_PCLK_, _BAUDRATE_) * 100)
#define DIV_Mantissa(_PCLK_, _BAUDRATE_)					(uint32_t)(USARTDIV(_PCLK_, _BAUDRATE_))
#define DIV_Fraction(_PCLK_, _BAUDRATE_)					(uint32_t)(((USARTDIV_MUL100(_PCLK_, _BAUDRATE_) - Mantissa_MUL100(_PCLK_, _BAUDRATE_)) * 16) / 100)
#define UART_BRR_Register(_PCLK_, _BAUDRATE_)				(uint32_t)((DIV_Mantissa(_PCLK_, _BAUDRATE_) << 4) | (DIV_Fraction(_PCLK_, _BAUDRATE_) & 0xF))


//==============================================================
//APIs Supported by "UART DRIVER":
//==============================================================

//Initialize/DeInitialize UART:
void		MCAL_UART_Init			(USART_typedef *USARTx,USART_Config_t *UART_Config);
void		MCAL_UART_DeInit			(USART_typedef *USARTx);

void		MCAL_UART_GPIO_SET_PINS	(USART_typedef *USARTx);

//TRANSMIT AND RECEIVE:
void 		MCAL_UART_TRANSMIT		(USART_typedef *USARTx,uint16_t *TX_Buffer,enum POLLING POLLING_EN);
void	 	MCAL_UART_RECEIVE		(USART_typedef *USARTx,uint16_t *RX_Buffer,enum POLLING POLLING_EN);

void 		MCAL_UART_WAIT_TC		(USART_typedef *USARTx);


#endif /* USART_DRIVER_USART_H_ */
