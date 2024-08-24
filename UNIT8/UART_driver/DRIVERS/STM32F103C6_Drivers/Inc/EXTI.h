/*
 * EXTI.h
 *
 *  Created on: 13 Aug 2024
 *      Author: Mahmoud
 */

#ifndef INC_EXTI_H_
#define INC_EXTI_H

//--------------------------------------------------------------
//INCLUDES:
//--------------------------------------------------------------

#include "STM32F103C6.h"
#include "GPIO.h"

//--------------------------------------------------------------


typedef struct
{
	uint16_t EXTI_INPUT_LINE;
	// Interrupt line number 0 -> 15 according to @REF EXTI_Input_Line_Number

	GPIO_typedef* GPIO_PORT;
	// Interrupt PORT A,B,C,D

	uint16_t GPIO_PIN_NUMBER;
	//Interrupt PIN number 0 -> 15

	uint8_t	IVT_IRQ_Number;
	//Interrupt number from IVT.

} EXTI_GPIO_Mapping_t;

typedef struct
{
	EXTI_GPIO_Mapping_t EXTI_PIN;
	//EXTI_PIN Specify the Interrupt line number & Interrupt PORT & Interrupt PIN number (EXTI GPIO Mapping).
	//You must set it according to @REF EXTI_PIN_Define

	uint8_t	EXTI_Trigger_Case;
	//EXTI_Trigger_Case Specify the Interrupt Trigger Case if it is Rising or Falling or Both.
	//you must set it according to @REF EXTI_Trigger_Case

	uint8_t	EXTI_IRQ_EN;
	//EXTI_IRQ_EN enable & disable IRQ Mask in EXTI & NVIC
	//you must set it according to @REF EXTI_IRQ_EN

	void (*PF_IRQ_CallBack)(void);
	//PF_IRQ_CallBack this is a pointer to a function we need it executed when the interrupt occurred.

} EXTI_Config_t;

//==============================================================
//@REF EXTI_Define

//@REF EXTI_Input_Line_Number
#define EXTI0				0
#define EXTI1				1
#define EXTI2				2
#define EXTI3				3
#define EXTI4				4
#define EXTI5				5
#define EXTI6				6
#define EXTI7				7
#define EXTI8				8
#define EXTI9				9
#define EXTI10				10
#define EXTI11				11
#define EXTI12				12
#define EXTI13				13
#define EXTI14				14
#define EXTI15				15

//--------------------------------------------------------------

//@REF EXTI_PIN_Define
/* EXTI0 */
#define EXTI0PA0			(EXTI_GPIO_Mapping_t){EXTI0, PORTA, GPIO_PIN_0, EXTI0_IRQ}
#define EXTI0PB0			(EXTI_GPIO_Mapping_t){EXTI0, PORTB, GPIO_PIN_0, EXTI0_IRQ}
#define EXTI0PC0			(EXTI_GPIO_Mapping_t){EXTI0, PORTC, GPIO_PIN_0, EXTI0_IRQ}
#define EXTI0PD0			(EXTI_GPIO_Mapping_t){EXTI0, PORTD, GPIO_PIN_0, EXTI0_IRQ}

/* EXTI1 */
#define EXTI1PA1			(EXTI_GPIO_Mapping_t){EXTI1, PORTA, GPIO_PIN_1, EXTI1_IRQ}
#define EXTI1PB1			(EXTI_GPIO_Mapping_t){EXTI1, PORTB, GPIO_PIN_1, EXTI1_IRQ}
#define EXTI1PC1			(EXTI_GPIO_Mapping_t){EXTI1, PORTC, GPIO_PIN_1, EXTI1_IRQ}
#define EXTI1PD1			(EXTI_GPIO_Mapping_t){EXTI1, PORTD, GPIO_PIN_1, EXTI1_IRQ}

/* EXTI2 */
#define EXTI2PA2			(EXTI_GPIO_Mapping_t){EXTI2, PORTA, GPIO_PIN_2, EXTI2_IRQ}
#define EXTI2PB2			(EXTI_GPIO_Mapping_t){EXTI2, PORTB, GPIO_PIN_2, EXTI2_IRQ}
#define EXTI2PC2			(EXTI_GPIO_Mapping_t){EXTI2, PORTC, GPIO_PIN_2, EXTI2_IRQ}
#define EXTI2PD2			(EXTI_GPIO_Mapping_t){EXTI2, PORTD, GPIO_PIN_2, EXTI2_IRQ}

/* EXTI3 */
#define EXTI3PA3			(EXTI_GPIO_Mapping_t){EXTI3, PORTA, GPIO_PIN_3, EXTI3_IRQ}
#define EXTI3PB3			(EXTI_GPIO_Mapping_t){EXTI3, PORTB, GPIO_PIN_3, EXTI3_IRQ}
#define EXTI3PC3			(EXTI_GPIO_Mapping_t){EXTI3, PORTC, GPIO_PIN_3, EXTI3_IRQ}
#define EXTI3PD3			(EXTI_GPIO_Mapping_t){EXTI3, PORTD, GPIO_PIN_3, EXTI3_IRQ}

/* EXTI4 */
#define EXTI4PA4			(EXTI_GPIO_Mapping_t){EXTI4, PORTA, GPIO_PIN_4, EXTI4_IRQ}
#define EXTI4PB4			(EXTI_GPIO_Mapping_t){EXTI4, PORTB, GPIO_PIN_4, EXTI4_IRQ}
#define EXTI4PC4			(EXTI_GPIO_Mapping_t){EXTI4, PORTC, GPIO_PIN_4, EXTI4_IRQ}
#define EXTI4PD4			(EXTI_GPIO_Mapping_t){EXTI4, PORTD, GPIO_PIN_4, EXTI4_IRQ}

/* EXTI5 */
#define EXTI5PA5			(EXTI_GPIO_Mapping_t){EXTI5, PORTA, GPIO_PIN_5, EXTI5_IRQ}
#define EXTI5PB5			(EXTI_GPIO_Mapping_t){EXTI5, PORTB, GPIO_PIN_5, EXTI5_IRQ}
#define EXTI5PC5			(EXTI_GPIO_Mapping_t){EXTI5, PORTC, GPIO_PIN_5, EXTI5_IRQ}
#define EXTI5PD5			(EXTI_GPIO_Mapping_t){EXTI5, PORTD, GPIO_PIN_5, EXTI5_IRQ}

/* EXTI6 */
#define EXTI6PA6			(EXTI_GPIO_Mapping_t){EXTI6, PORTA, GPIO_PIN_6, EXTI6_IRQ}
#define EXTI6PB6			(EXTI_GPIO_Mapping_t){EXTI6, PORTB, GPIO_PIN_6, EXTI6_IRQ}
#define EXTI6PC6			(EXTI_GPIO_Mapping_t){EXTI6, PORTC, GPIO_PIN_6, EXTI6_IRQ}
#define EXTI6PD6			(EXTI_GPIO_Mapping_t){EXTI6, PORTD, GPIO_PIN_6, EXTI6_IRQ}

/* EXTI7 */
#define EXTI7PA7			(EXTI_GPIO_Mapping_t){EXTI7, PORTA, GPIO_PIN_7, EXTI7_IRQ}
#define EXTI7PB7			(EXTI_GPIO_Mapping_t){EXTI7, PORTB, GPIO_PIN_7, EXTI7_IRQ}
#define EXTI7PC7			(EXTI_GPIO_Mapping_t){EXTI7, PORTC, GPIO_PIN_7, EXTI7_IRQ}
#define EXTI7PD7			(EXTI_GPIO_Mapping_t){EXTI7, PORTD, GPIO_PIN_7, EXTI7_IRQ}

/* EXTI8 */
#define EXTI8PA8			(EXTI_GPIO_Mapping_t){EXTI8, PORTA, GPIO_PIN_8, EXTI8_IRQ}
#define EXTI8PB8			(EXTI_GPIO_Mapping_t){EXTI8, PORTB, GPIO_PIN_8, EXTI8_IRQ}
#define EXTI8PC8			(EXTI_GPIO_Mapping_t){EXTI8, PORTC, GPIO_PIN_8, EXTI8_IRQ}
#define EXTI8PD8			(EXTI_GPIO_Mapping_t){EXTI8, PORTD, GPIO_PIN_8, EXTI8_IRQ}

/* EXTI9 */
#define EXTI9PA9			(EXTI_GPIO_Mapping_t){EXTI9, PORTA, GPIO_PIN_9, EXTI9_IRQ}
#define EXTI9PB9			(EXTI_GPIO_Mapping_t){EXTI9, PORTB, GPIO_PIN_9, EXTI9_IRQ}
#define EXTI9PC9			(EXTI_GPIO_Mapping_t){EXTI9, PORTC, GPIO_PIN_9, EXTI9_IRQ}
#define EXTI9PD9			(EXTI_GPIO_Mapping_t){EXTI9, PORTD, GPIO_PIN_9, EXTI9_IRQ}

/* EXTI10 */
#define EXTI10PA10			(EXTI_GPIO_Mapping_t){EXTI10, PORTA, GPIO_PIN_10, EXTI10_IRQ}
#define EXTI10PB10			(EXTI_GPIO_Mapping_t){EXTI10, PORTB, GPIO_PIN_10, EXTI10_IRQ}
#define EXTI10PC10			(EXTI_GPIO_Mapping_t){EXTI10, PORTC, GPIO_PIN_10, EXTI10_IRQ}
#define EXTI10PD10			(EXTI_GPIO_Mapping_t){EXTI10, PORTD, GPIO_PIN_10, EXTI10_IRQ}

/* EXTI11 */
#define EXTI11PA11			(EXTI_GPIO_Mapping_t){EXTI11, PORTA, GPIO_PIN_11, EXTI11_IRQ}
#define EXTI11PB11			(EXTI_GPIO_Mapping_t){EXTI11, PORTB, GPIO_PIN_11, EXTI11_IRQ}
#define EXTI11PC11			(EXTI_GPIO_Mapping_t){EXTI11, PORTC, GPIO_PIN_11, EXTI11_IRQ}
#define EXTI11PD11			(EXTI_GPIO_Mapping_t){EXTI11, PORTD, GPIO_PIN_11, EXTI11_IRQ}

/* EXTI12 */
#define EXTI12PA12			(EXTI_GPIO_Mapping_t){EXTI12, PORTA, GPIO_PIN_12, EXTI12_IRQ}
#define EXTI12PB12			(EXTI_GPIO_Mapping_t){EXTI12, PORTB, GPIO_PIN_12, EXTI12_IRQ}
#define EXTI12PC12			(EXTI_GPIO_Mapping_t){EXTI12, PORTC, GPIO_PIN_12, EXTI12_IRQ}
#define EXTI12PD12			(EXTI_GPIO_Mapping_t){EXTI12, PORTD, GPIO_PIN_12, EXTI12_IRQ}

/* EXTI13 */
#define EXTI13PA13			(EXTI_GPIO_Mapping_t){EXTI13, PORTA, GPIO_PIN_13, EXTI13_IRQ}
#define EXTI13PB13			(EXTI_GPIO_Mapping_t){EXTI13, PORTB, GPIO_PIN_13, EXTI13_IRQ}
#define EXTI13PC13			(EXTI_GPIO_Mapping_t){EXTI13, PORTC, GPIO_PIN_13, EXTI13_IRQ}
#define EXTI13PD13			(EXTI_GPIO_Mapping_t){EXTI13, PORTD, GPIO_PIN_13, EXTI13_IRQ}

/* EXTI14 */
#define EXTI14PA14			(EXTI_GPIO_Mapping_t){EXTI14, PORTA, GPIO_PIN_14, EXTI14_IRQ}
#define EXTI14PB14			(EXTI_GPIO_Mapping_t){EXTI14, PORTB, GPIO_PIN_14, EXTI14_IRQ}
#define EXTI14PC14			(EXTI_GPIO_Mapping_t){EXTI14, PORTC, GPIO_PIN_14, EXTI14_IRQ}
#define EXTI14PD14			(EXTI_GPIO_Mapping_t){EXTI14, PORTD, GPIO_PIN_14, EXTI14_IRQ}

/* EXTI15 */
#define EXTI15PA15			(EXTI_GPIO_Mapping_t){EXTI15, PORTA, GPIO_PIN_15, EXTI15_IRQ}
#define EXTI15PB15			(EXTI_GPIO_Mapping_t){EXTI15, PORTB, GPIO_PIN_15, EXTI15_IRQ}
#define EXTI15PC15			(EXTI_GPIO_Mapping_t){EXTI15, PORTC, GPIO_PIN_15, EXTI15_IRQ}
#define EXTI15PD15			(EXTI_GPIO_Mapping_t){EXTI15, PORTD, GPIO_PIN_15, EXTI15_IRQ}

//--------------------------------------------------------------

//@REF EXTI_Trigger_Case
#define EXTI_Trigger_RISING						0
#define EXTI_Trigger_FALLING					1
#define EXTI_Trigger_RISING_AND_FALLING			2

//--------------------------------------------------------------

//@REF EXTI_IRQ_EN
#define EXTI_IRQ_ENABLE							1
#define EXTI_IRQ_DISABLE						0

//==============================================================


//==============================================================
//APIs Supported by "MCAL EXTI DRIVER":
//==============================================================

void MCAL_EXTI_GPIO_Init(EXTI_Config_t *EXTI_CFG);
void MCAL_EXTI_GPIO_DeInit(void);
void MCAL_EXTI_GPIO_Update(EXTI_Config_t *EXTI_CFG);

#endif
