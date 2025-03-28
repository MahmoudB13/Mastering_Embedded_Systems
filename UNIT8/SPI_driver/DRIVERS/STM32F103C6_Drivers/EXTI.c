/*
 * EXTI.c
 *
 *  Created on: 13 Aug 2024
 *      Author: Mahmoud
 */

//--------------------------------------------------------------
//INCLUDES:
//--------------------------------------------------------------

#include "EXTI.h"

//--------------------------------------------------------------
//GENERIC VARIABLES:
//--------------------------------------------------------------

	void (*GP_IRQ_CALLBACK[16])(void);

//--------------------------------------------------------------
//GENERIC FUNCTIONS:
//--------------------------------------------------------------

uint8_t AFIO_GPIO_EXTI_Mapping(GPIO_typedef* x)
	{
		if(x==PORTA) return 0;
		if(x==PORTB) return 1;
		if(x==PORTC) return 2;
		if(x==PORTD) return 3;
		return 0;
	}

void ENABLE_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
		case EXTI0:
			NVIC_EXTI0_IRQ_ENABLE;
			break;
		case EXTI1:
			NVIC_EXTI1_IRQ_ENABLE;
			break;
		case EXTI2:
			NVIC_EXTI2_IRQ_ENABLE;
			break;
		case EXTI3:
			NVIC_EXTI3_IRQ_ENABLE;
			break;
		case EXTI4:
			NVIC_EXTI4_IRQ_ENABLE;
			break;
		case EXTI5:
		case EXTI6:
		case EXTI7:
		case EXTI8:
		case EXTI9:
			NVIC_EXTI9_5_IRQ_ENABLE;
			break;
		case EXTI10:
		case EXTI11:
		case EXTI12:
		case EXTI13:
		case EXTI14:
		case EXTI15:
			NVIC_EXTI15_10_IRQ_ENABLE;
			break;
	}
}


void DISABLE_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
		case EXTI0:
			NVIC_EXTI0_IRQ_DISABLE;
			break;
		case EXTI1:
			NVIC_EXTI1_IRQ_DISABLE;
			break;
		case EXTI2:
			NVIC_EXTI2_IRQ_DISABLE;
			break;
		case EXTI3:
			NVIC_EXTI3_IRQ_DISABLE;
			break;
		case EXTI4:
			NVIC_EXTI4_IRQ_DISABLE;
			break;
		case EXTI5:
		case EXTI6:
		case EXTI7:
		case EXTI8:
		case EXTI9:
			NVIC_EXTI9_5_IRQ_DISABLE;
			break;
		case EXTI10:
		case EXTI11:
		case EXTI12:
		case EXTI13:
		case EXTI14:
		case EXTI15:
			NVIC_EXTI15_10_IRQ_DISABLE;
			break;
	}
}


void UPDATE_EXTI(EXTI_Config_t *EXTI_CFG)
{
	//CONFIGURE GPIO TO BE AF FLOATING INPUT:
	GPIO_PinConfig_t PIN_Config;
	PIN_Config.GPIO_PIN_NUMBER = EXTI_CFG->EXTI_PIN.GPIO_PIN_NUMBER;
	PIN_Config.GPIO_MODE = GPIO_MODE_FLOATING_INPUT;
	MCAL_GPIO_Init(EXTI_CFG->EXTI_PIN.GPIO_PORT, &PIN_Config);

	//CONFIGURE THE AFIO PIN TP BE EXTI:
	uint8_t AFIO_EXTICR_index = EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE/4;
	uint8_t AFIO_EXTICR_position = (EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE%4)*4;
	AFIO->EXTICR[AFIO_EXTICR_index] &= ~(0xF)<<AFIO_EXTICR_position;

	AFIO->EXTICR[AFIO_EXTICR_index] |= (AFIO_GPIO_EXTI_Mapping(EXTI_CFG->EXTI_PIN.GPIO_PORT)&0xF) << AFIO_EXTICR_position ;

	//SELECTING THE EDGE THAT ENABLES THE INTERRUPT:
	//CLEAR RTSR AND FTSR IN CASE OF UPDATE:
	CLEAR_BIT(EXTI->RTSR,EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE);
	CLEAR_BIT(EXTI->FTSR,EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE);

	//RISING EDGE:
	if(EXTI_CFG->EXTI_Trigger_Case==EXTI_Trigger_RISING)
	{
		SET_BIT(EXTI->RTSR,EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE);
		CLEAR_BIT(EXTI->FTSR,EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE);
	}
	//FALLING EDGE:
	if(EXTI_CFG->EXTI_Trigger_Case==EXTI_Trigger_FALLING)
	{
		SET_BIT(EXTI->FTSR,EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE);
	}
	//BOTH RISING AND FALLING:
	if(EXTI_CFG->EXTI_Trigger_Case==EXTI_Trigger_RISING_AND_FALLING)
	{
		SET_BIT(EXTI->RTSR,EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE);
		SET_BIT(EXTI->FTSR,EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE);
	}

	//UPDATE IRQ HANDLING CALLBACK:

	GP_IRQ_CALLBACK[EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE]=EXTI_CFG->PF_IRQ_CallBack;

	//MASKING THE INTERRUPT LINE:
	if(EXTI_CFG->EXTI_IRQ_EN==EXTI_IRQ_ENABLE)
	{
		SET_BIT(EXTI->IMR,EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE);
		ENABLE_NVIC(EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE);
	}
	if(EXTI_CFG->EXTI_IRQ_EN==EXTI_IRQ_DISABLE)
	{
		CLEAR_BIT(EXTI->IMR,EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE);
		DISABLE_NVIC(EXTI_CFG->EXTI_PIN.EXTI_INPUT_LINE);
	}
}


//==============================================================
//APIs Supported by "EXTI GPIO DRIVER":
//==============================================================

/*
 * --------------------------------------------------------------
 * FUNCTION: 		MCAL_EXTI_GPIO_Init
 * DISCRIPTION:
 * PARAMETER (IN):
 * RETURN VALUE: 	void
 * NOTES: 			----
 * --------------------------------------------------------------
 */

void MCAL_EXTI_GPIO_Init(EXTI_Config_t *EXTI_CFG)
{
	UPDATE_EXTI(EXTI_CFG);
}

/*
 * --------------------------------------------------------------
 * FUNCTION: 		MCAL_EXTI_GPIO_DeInit
 * DISCRIPTION: 	reset EXTI registers and NVIC corresponding IRQ Mask.
 * PARAMETER (IN):	void
 * RETURN VALUE: 	void
 * NOTES: 			----
 * --------------------------------------------------------------
 */

void MCAL_EXTI_GPIO_DeInit(void)
{
	//RESET ALL EXTI REGISTERS:
	EXTI->IMR 	=	0x00000000;
	EXTI->EMR 	= 	0x00000000;
	EXTI->RTSR 	=	0x00000000;
	EXTI->FTSR 	= 	0x00000000;
	EXTI->SWIER =	0x00000000;
	EXTI->PR 	= 	0xFFFFFFFF;
	//DISABLE EXTI IRQ FROM NVIC:
	NVIC_EXTI0_IRQ_DISABLE;
	NVIC_EXTI1_IRQ_DISABLE;
	NVIC_EXTI2_IRQ_DISABLE;
	NVIC_EXTI3_IRQ_DISABLE;
	NVIC_EXTI4_IRQ_DISABLE;
	NVIC_EXTI9_5_IRQ_DISABLE;
	NVIC_EXTI15_10_IRQ_DISABLE;
}

/*
 * --------------------------------------------------------------
 * FUNCTION: 		MCAL_EXTI_GPIO_Update
 * DISCRIPTION:
 * PARAMETER (IN):
 * RETURN VALUE: 	void
 * NOTES: 			----
 * --------------------------------------------------------------
 */

void MCAL_EXTI_GPIO_Update(EXTI_Config_t *EXTI_CFG)
{
	UPDATE_EXTI(EXTI_CFG);
}

//==============================================================
//ISR Functions:
//==============================================================

//EXTI0:
void EXTI0_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR,EXTI0);

	//Call IRQ CallBack
	GP_IRQ_CALLBACK[EXTI0]();

}

//EXTI1:
void EXTI1_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR,EXTI1);

	//Call IRQ CALLBACK
	GP_IRQ_CALLBACK[EXTI1]();
}

//EXTI2:
void EXTI2_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR,EXTI2);

	//Call IRQ CALLBACK
	GP_IRQ_CALLBACK[EXTI2]();
}

//EXTI3:
void EXTI3_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR,EXTI3);

	//Call IRQ CALLBACK
	GP_IRQ_CALLBACK[EXTI3]();
}

//EXTI4:
void EXTI4_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit.
	SET_BIT(EXTI->PR,EXTI4);

	//Call IRQ CALLBACK
	GP_IRQ_CALLBACK[EXTI4]();
}

//EXTI5->9:
void EXTI9_5_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit.
	if(EXTI->PR & GPIO_PIN_5)
	{
		SET_BIT(EXTI->PR,EXTI5);

		//Call IRQ CALLBACK
		GP_IRQ_CALLBACK[EXTI5]();
	}

	if(EXTI->PR & GPIO_PIN_6)
	{
		SET_BIT(EXTI->PR,EXTI6);

		//Call IRQ CALLBACK
		GP_IRQ_CALLBACK[EXTI6]();
	}

	if(EXTI->PR & GPIO_PIN_7)
	{
		SET_BIT(EXTI->PR,EXTI7);

		//Call IRQ CALLBACK
		GP_IRQ_CALLBACK[EXTI7]();
	}

	if(EXTI->PR & GPIO_PIN_8)
	{
		SET_BIT(EXTI->PR,EXTI8);

		//Call IRQ CALLBACK
		GP_IRQ_CALLBACK[EXTI8]();
	}

	if(EXTI->PR & GPIO_PIN_9)
	{
		SET_BIT(EXTI->PR,EXTI9);

		//Call IRQ CALLBACK
		GP_IRQ_CALLBACK[EXTI9]();
	}
}

//EXTI10->15:
void EXTI15_10_IRQHandler(void)
{
	//clear the Pending Register by writing a ‘1’ into the bit.
	if(EXTI->PR & GPIO_PIN_10)
	{
		SET_BIT(EXTI->PR,EXTI10);

		//Call IRQ CALLBACK
		GP_IRQ_CALLBACK[EXTI10]();
	}

	if(EXTI->PR & GPIO_PIN_11)
	{
		SET_BIT(EXTI->PR,EXTI11);

		//Call IRQ CALLBACK
		GP_IRQ_CALLBACK[EXTI11]();
	}

	if(EXTI->PR & GPIO_PIN_12)
	{
		SET_BIT(EXTI->PR,EXTI12);

		//Call IRQ CALLBACK
		GP_IRQ_CALLBACK[EXTI12]();
	}

	if(EXTI->PR & GPIO_PIN_13)
	{
		SET_BIT(EXTI->PR,EXTI13);

		//Call IRQ CALLBACK
		GP_IRQ_CALLBACK[EXTI13]();
	}

	if(EXTI->PR & GPIO_PIN_14)
	{
		SET_BIT(EXTI->PR,EXTI14);

		//Call IRQ CALLBACK
		GP_IRQ_CALLBACK[EXTI14]();
	}

	if(EXTI->PR & GPIO_PIN_15)
	{
		SET_BIT(EXTI->PR,EXTI15);

		//Call IRQ CALLBACK
		GP_IRQ_CALLBACK[EXTI15]();
	}
}
