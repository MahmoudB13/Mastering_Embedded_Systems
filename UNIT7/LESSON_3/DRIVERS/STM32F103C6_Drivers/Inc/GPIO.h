/*
 * GPIO.h
 *
 *  Created on: Jul 17, 2024
 *      Author: Mahmoud
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

//--------------------------------------------------------------
//INCLUDES:
//--------------------------------------------------------------

#include "STM32F103C6.h"

//--------------------------------------------------------------
//CONFIG STRUCTURE:
//--------------------------------------------------------------

typedef struct
{
	uint16_t GPIO_PIN_NUMBER;
	//TO SPECIFY THE PIN TO BE CONFIGURED.
	//THIS PARAMETER MUST BE SET BASED ON @REF GPIO_PINS_define.


	uint8_t GPIO_MODE;
	//TO SPECIFY THE OPERATING MODE FOR THE SELECTED PIN.
	//THIS PARAMETER MUST BE SET BASED ON //@REF GPIO_MODE_define.


	uint8_t GPIO_OUTPUT_FREQ;
	//TO SPECIFY THE FREQUENCY FOR THE SELECTED OUTPUT PIN.
	//THIS PARAMETER MUST BE SET BASED ON //@REF GPIO_FREQ_define.

}GPIO_PinConfig_t;

//==============================================================

//--------------------------------------------------------------
//Macros Configuration References
//--------------------------------------------------------------

//@REF GPIO_PINS_define
#define GPIO_PIN_0					((uint16_t)0x0001)		/* PIN 00 selected */
#define GPIO_PIN_1					((uint16_t)0x0002)		/* PIN 01 selected */
#define GPIO_PIN_2					((uint16_t)0x0004)		/* PIN 02 selected */
#define GPIO_PIN_3					((uint16_t)0x0008)		/* PIN 03 selected */
#define GPIO_PIN_4					((uint16_t)0x0010)		/* PIN 04 selected */
#define GPIO_PIN_5					((uint16_t)0x0020)		/* PIN 05 selected */
#define GPIO_PIN_6					((uint16_t)0x0040)		/* PIN 06 selected */
#define GPIO_PIN_7					((uint16_t)0x0080)		/* PIN 07 selected */
#define GPIO_PIN_8					((uint16_t)0x0100)		/* PIN 08 selected */
#define GPIO_PIN_9					((uint16_t)0x0200)		/* PIN 09 selected */
#define GPIO_PIN_10					((uint16_t)0x0400)		/* PIN 10 selected */
#define GPIO_PIN_11					((uint16_t)0x0800)		/* PIN 11 selected */
#define GPIO_PIN_12					((uint16_t)0x1000)		/* PIN 12 selected */
#define GPIO_PIN_13					((uint16_t)0x2000)		/* PIN 13 selected */
#define GPIO_PIN_14					((uint16_t)0x4000)		/* PIN 14 selected */
#define GPIO_PIN_15					((uint16_t)0x8000)		/* PIN 15 selected */
#define GPIO_PIN_ALL				((uint16_t)0xFFFF)		/* All pins selected */

/*#define GPIO_PIN_MASK				0x0000FFFFu*/
//--------------------------------------------------------------

//@REF GPIO_OUTPUT_FREQ define:
#define GPIO_OUTPUT_FREQ_10MHz								0x00000001u
#define GPIO_OUTPUT_FREQ_2MHz								0x00000002u
#define GPIO_OUTPUT_FREQ_50MHz								0x00000003u

//--------------------------------------------------------------

//@REF GPIO_MODE_define:
//INPUT CONFIG:
#define GPIO_MODE_ANALOG 							0x00000000u
#define GPIO_MODE_FLOATING_INPUT 					0x00000001u
#define GPIO_MODE_INPUT_PullUp 						0x00000002u
#define GPIO_MODE_INPUT_PullDown 					0x00000003u

/*For alternate function inputs, the port must be configured in Input mode
(floating, pull-up or pull-down) and the input pin must be driven externally. */

//OUTPUT CONFIG:
#define GPIO_MODE_OUT_PUSH_PULL 					0x00000004u
#define GPIO_MODE_OUT_OPEN_DRAIN 					0x00000005u
#define AFIO_MODE_OUT_PUSH_PULL 					0x00000006u
#define AFIO_MODE_OUT_OPEN_DRAIN 					0x00000007u

//--------------------------------------------------------------

//@REF GPIO_PIN_state:
#define GPIO_PIN_SET								1
#define GPIO_PIN_RESET								0

//@REF GPIO_LOCK_state:
#define GPIO_LOCK_OK								0
#define GPIO_LOCK_ERROR								1

//==============================================================
//APIs Supported by "MCAL GPIO DRIVER":
//==============================================================

//Initialize & Reset APIs
void MCAL_GPIO_Init (GPIO_typedef *GPIOx, GPIO_PinConfig_t *PIN_Config);
void MCAL_GPIO_DeInit (GPIO_typedef *GPIOx);

//Read APIs
uint8_t MCAL_GPIO_ReadPin (GPIO_typedef *GPIOx, uint16_t GPIO_PIN_NUMBER);
uint16_t MCAL_GPIO_ReadPort (GPIO_typedef *GPIOx);

//Write APIs
void MCAL_GPIO_WritePin (GPIO_typedef *GPIOx, uint16_t GPIO_PIN_NUMBER, uint8_t Value);
void MCAL_GPIO_WritePort (GPIO_typedef *GPIOx, uint16_t Value);

//Toggle APIs
void MCAL_GPIO_TogglePin (GPIO_typedef *GPIOx, uint16_t GPIO_PIN_NUMBER);

//Lock APIs
uint8_t MCAL_GPIO_LockPin (GPIO_typedef *GPIOx, uint16_t GPIO_PIN_NUMBER);

#endif /* INC_GPIO_H_ */
