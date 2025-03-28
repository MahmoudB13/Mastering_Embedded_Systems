/*
 * SPI.h
 *
 *  Created on: 21 Oct 2024
 *      Author: Mahmoud
 */

#ifndef SPI_DRIVER_SPI_H_
#define SPI_DRIVER_SPI_H_

//--------------------------------------------------------------
//INCLUDES:
//--------------------------------------------------------------

#include "STM32F103C6.h"
#include "GPIO.h"

//--------------------------------------------------------------
//INTERRUPT SOURCES:
//--------------------------------------------------------------

struct SPI_IRQ_SRC
{
	uint8_t TXE:1;				//TX BUFFER EMPTY INTERRUPT.
	uint8_t RXNE:1;				//RX BUFFER NOT EMPTY INTERRUPT.
	uint8_t ERRI:1;				//ERROR INTERRUPT.
	uint8_t Reserved:5;
};

//--------------------------------------------------------------
//CONFIG STRUCTURE:
//--------------------------------------------------------------

typedef struct
{
	uint16_t DEVICE_MODE;
	//TO SPECIFY THE MODE OF THE SPI WHETHER MASTER OR SLAVE.
	//THIS PARAMETER MUST BE SET BASED ON //@REF DEVICE_MODE_define.

	uint16_t COMMUNICATION_MODE;
	//TO SPECIFY THE MODE OF COMMUNCICATION: FULL DUPLEX, HALF DUPLEX OR SIMPLEX.
	//THIS PARAMETER MUST BE SET BASED ON //@REF COMMUNICATION_MODE_define.

	uint16_t FRAME_FORMAT;
	//TO SPECIFY THE FIRST BIT TO BE TRANSFERRED WHETHER LSB OR MSB.
	//THIS PARAMETER MUST BE SET BASED ON //@REF FRAME_FORMAT_define.

	uint16_t DATA_SIZE;
	//TO SPECIFY THE NUMBER OF BITS TO BE TRANSMITTED.
	//THIS PARAMETER MUST BE SET BASED ON //@REF DATA_SIZE_define.

	uint16_t CLOCK_POLARITY;
	//TO SPECIFY THE POLARITY OF THE CLOCK.
	//THIS PARAMETER MUST BE SET BASED ON //@REF CLOCK_POLARITY_define.

	uint16_t CLOCK_PHASE;
	//TO SPECIFY THE PHASE OF THE CLOCK.
	//THIS PARAMETER MUST BE SET BASED ON //@REF CLOCK_PHASE_define.

	uint16_t NSS;
	//TO SPECIFY WHETHER THE NSS IS CONTROLLED BY SOFTWARE OR HARDWARE.
	//THIS PARAMETER MUST BE SET BASED ON //@REF NSS_define.

	uint16_t SPI_BAUD_RATE;
	//TO SPECIFY THE BAUDRATE OF THE TRANSMISSION.
	//THIS PARAMETER MUST BE SET BASED ON //@REF SPI_BAUD_RATE_define.

	uint16_t SPI_IRQ;
	//TO ENABLE AND DISABLE THE INTERRUPTS OT THE SPI.
	//THIS PARAMETER MUST BE SET BASED ON //@REF SPI_IRQ_define.


	void(*P_IRQ_Callback)(struct SPI_IRQ_SRC IRQ_SRC);
	//PF_IRQ_CallBack this is a pointer to a function we need it executed when the interrupt occurred.

}SPI_Config_t;
//==============================================================

//--------------------------------------------------------------
//Macros Configuration References
//--------------------------------------------------------------

//@REF DEVICE_MODE_define:
#define DEVICE_MODE_SLAVE									(uint16_t)(0)
#define DEVICE_MODE_MASTER									(uint16_t)(1<<2)


//--------------------------------------------------------------

//@REF COMMUNICATION_MODE_define:
#define COMMUNICATION_MODE_2_LINES							(uint16_t)(0)
#define COMMUNICATION_MODE_2_LINES_RX_ONLY					(uint16_t)(1<<10)
#define COMMUNICATION_MODE_1_LINE_RX_ONLY					(uint16_t)(1<<15)
#define COMMUNICATION_MODE_1_LINE_TX_ONLY					(uint16_t)(1<<14 | 1<<15)

//--------------------------------------------------------------

//@REF FRAME_FORMAT_define:
#define FRAME_FORMAT_MSB									(uint16_t)(0)
#define FRAME_FORMAT_LSB									(uint16_t)(1<<7)

//--------------------------------------------------------------

//@REF DATA_SIZE_define:
#define DATA_SIZE_8_BIT										(uint16_t)(0)
#define DATA_SIZE_16_BIT									(uint16_t)(1<<11)

//--------------------------------------------------------------

//@REF CLOCK_POLARITY_define:
#define CLOCK_POLARITY_IDLE_0								(uint16_t)(0)
#define CLOCK_POLARITY_IDLE_1								(uint16_t)(1<<1)

//--------------------------------------------------------------

//@REF CLOCK_PHASE_define:
#define CLOCK_PHASE_FISRT									(uint16_t)(0)
#define CLOCK_PHASE_SECOND									(uint16_t)(1<<0)

//--------------------------------------------------------------

//@REF NSS_define:
#define NSS_HARDWARE_SLAVE									(uint16_t)(0)
#define NSS_HARDWARE_MASTER_SSO_ENABLE						(uint16_t)(1<<2)
#define NSS_HARDWARE_MASTER_SSO_DISABLE						~((uint16_t)(1<<2))
#define NSS_SOFTWARE_RESET									(uint16_t)(1<<9)
#define NSS_SOFTWARE_SET									(uint16_t)(1<<9 | 1<<8)

//--------------------------------------------------------------

//@REF SPI_BAUD_RATE_define:
#define SPI_BAUD_RATE_2										(uint16_t)(0b000<<3)
#define SPI_BAUD_RATE_4										(uint16_t)(0b001<<3)
#define SPI_BAUD_RATE_8										(uint16_t)(0b010<<3)
#define SPI_BAUD_RATE_16									(uint16_t)(0b011<<3)
#define SPI_BAUD_RATE_32									(uint16_t)(0b100<<3)
#define SPI_BAUD_RATE_64									(uint16_t)(0b101<<3)
#define SPI_BAUD_RATE_128									(uint16_t)(0b110<<3)
#define SPI_BAUD_RATE_256									(uint16_t)(0b111<<3)

//--------------------------------------------------------------

//@REF SPI_IRQ_define:
#define SPI_IRQ_DISABLE										(uint16_t)(0)
#define SPI_IRQ_TXEIE_ENABLE								(uint16_t)(1<<7)
#define SPI_IRQ_RXNEIE_ENABLE								(uint16_t)(1<<6)
#define SPI_IRQ_ERRIE_ENABLE								(uint16_t)(1<<5)

//--------------------------------------------------------------

//==============================================================
//APIs Supported by "SPI DRIVER":
//==============================================================

void MCAL_SPI_INIT(SPI_typedef *SPIx, SPI_Config_t* SPI_CONFIG);
void MCAL_SPI_DeINIT(SPI_typedef *SPIx);

void MCAL_SPI_GPIO_SET_PINS(SPI_typedef *SPIx);

void MCAL_SPI_SEND_DATA(SPI_typedef *SPIx,uint16_t *pTxBuffer,enum POLLING POLLING_EN);
void MCAL_SPI_RECEIVE_DATA(SPI_typedef *SPIx,uint16_t *pRxBuffer,enum POLLING POLLING_EN);

void MCAL_SPI_SEND_RECEIVE_DATA(SPI_typedef *SPIx,uint16_t *pTxBuffer,enum POLLING POLLING_EN);
#endif /* SPI_DRIVER_SPI_H_ */
