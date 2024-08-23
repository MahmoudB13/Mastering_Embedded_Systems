/*
 * GPIO.c
 *
 *  Created on: Jul 17, 2024
 *      Author: Mahmoud
 */

//--------------------------------------------------------------
//INCLUDES:
//--------------------------------------------------------------

#include "GPIO.h"


//==============================================================
//APIs Supported by "MCAL GPIO DRIVER":
//==============================================================


/*
 * --------------------------------------------------------------
 * FUNCTION: 		Get_PIN_Position
 * DISCRIPTION: 	get the position of the PIN in CRL & CRH because each pin is take 4 bit.
 * PARAMETER (IN): 	GPIO_PIN_NUMBER: Set PIN number according to @REF GPIO_PINs_define.
 * RETURN VALUE: 	it return the position of the PIN
 * NOTES: 			----
 * --------------------------------------------------------------
 */
uint8_t Get_PIN_Position(uint16_t GPIO_PIN_NUMBER)
{
	switch(GPIO_PIN_NUMBER)
	{
	case GPIO_PIN_0:
	case GPIO_PIN_8:
		return 0;
		break;

	case GPIO_PIN_1:
	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_2:
	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_3:
	case GPIO_PIN_11:
		return 12;
		break;

	case GPIO_PIN_4:
	case GPIO_PIN_12:
		return 16;
		break;

	case GPIO_PIN_5:
	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_6:
	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_7:
	case GPIO_PIN_15:
		return 28;
		break;
	}

	return 0;
}


/*
 * --------------------------------------------------------------
 * FUNCTION: 		MCAL_GPIO_Init
 * DISCRIPTION: 	Initializes GPIOx PIN according to specifications in PIN_Config.
 * PARAMETER (IN): 	GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * PARAMETER (IN): 	PIN_Config: a pointer to GPIO_PIN_Configuration_t structure that contains.
 * RETURN VALUE: 	void
 * NOTES: 			STM32F103C6 MCU has GPIO A,B,C,D,E Modules but LQFP48 Package has only GPIO A,B Part of C,D
 * 					exported as external PINs from the MCU.
 * --------------------------------------------------------------
 */
void MCAL_GPIO_Init (GPIO_typedef *GPIOx, GPIO_PinConfig_t *PIN_Config)
{
	//CRL register is used to configure PINS 0->7
	//CRH register is used to configure PINS 8->15
	volatile uint32_t* config_reg = NULL;
	if((PIN_Config->GPIO_PIN_NUMBER)<GPIO_PIN_8)
	{
		config_reg = &GPIOx->CRL;
	}
	else
	{
		config_reg = &GPIOx->CRH;
	}

	//CLEAR CNFx AND MODEx FOR THE SPECIFIED PIN:
	(*config_reg) &= ~(0x0F<<Get_PIN_Position(PIN_Config->GPIO_PIN_NUMBER));

	//IF THE PIN IS SET TO OUTPUT:
	if(PIN_Config->GPIO_MODE==GPIO_MODE_OUT_OPEN_DRAIN || PIN_Config->GPIO_MODE==GPIO_MODE_OUT_PUSH_PULL ||
			PIN_Config->GPIO_MODE==AFIO_MODE_OUT_OPEN_DRAIN || PIN_Config->GPIO_MODE==AFIO_MODE_OUT_PUSH_PULL)
	{
			//SET THE FREQUENCY OF THE OUTPUT PIN:
			*config_reg |= ((PIN_Config->GPIO_OUTPUT_FREQ)&0x3)<<Get_PIN_Position(PIN_Config->GPIO_PIN_NUMBER);
			//SET THE OUTPUT MODE OF THE PIN:
			*config_reg |= ((((PIN_Config->GPIO_MODE)-4)<<2)&0xC)<<Get_PIN_Position(PIN_Config->GPIO_PIN_NUMBER);
	}
	//IF THE PIN IS SET TO INPUT:
	else
	{
			if(PIN_Config->GPIO_MODE==GPIO_MODE_ANALOG||PIN_Config->GPIO_MODE==GPIO_MODE_FLOATING_INPUT||PIN_Config->GPIO_MODE==GPIO_MODE_INPUT_PullUp)
			{
				//SET THE INPUT MODE:
				*config_reg |= (((PIN_Config->GPIO_MODE)<<2)&0xC)<<Get_PIN_Position(PIN_Config->GPIO_PIN_NUMBER);
				//SET THE ODR TO ENABLE PULL-UP:
				GPIOx->ODR  |= PIN_Config->GPIO_PIN_NUMBER;
			}
			if(PIN_Config->GPIO_MODE==GPIO_MODE_INPUT_PullDown)
			{
				//SET THE INPUT MODE TO PULL-DOWN:
				*config_reg |= ((((PIN_Config->GPIO_MODE)-1)<<2)&0xC)<<Get_PIN_Position(PIN_Config->GPIO_PIN_NUMBER);
				//CLEAR THE ODR TO ENABLE PULL-DOWN:
				GPIOx->ODR  &= ~(PIN_Config->GPIO_PIN_NUMBER);
			}
	}
}


/*
 * --------------------------------------------------------------
 * FUNCTION: 		MCAL_GPIO_DeInit
 * DISCRIPTION: 	Reset All the GPIO Registers.
 * PARAMETER (IN): 	GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * RETURN VALUE: 	void
 * NOTES: 			----
 * --------------------------------------------------------------
 */
void MCAL_GPIO_DeInit (GPIO_typedef *GPIOx)
{
	/*	IF THERE IS NO RESET CONTROLLER:
	 * 	GPIOx->CRL  = 0x44444444;
	 *  GPIOx->CRH  = 0x44444444;
	 *	GPIOx->IDR    READ ONLY
	 *	GPIOx->ODR  = 0x00000000;
	 *	GPIOx->BSRR = 0x00000000;
	 *	GPIOx->BRR  = 0x00000000;
	 *	GPIOx->LCKR = 0x00000000;
	 */

	//USING THE RESET CONTROLLER:
	if(GPIOx == PORTA)
	{
		RCC->APB2RSTR |=  (1 << 2);
		RCC->APB2RSTR &= ~(1 << 2);
	}
	else if(GPIOx == PORTB)
	{
		RCC->APB2RSTR |=  (1 << 3);
		RCC->APB2RSTR &= ~(1 << 3);
	}
	else if(GPIOx == PORTC)
	{
		RCC->APB2RSTR |=  (1 << 4);
		RCC->APB2RSTR &= ~(1 << 4);
	}
	else if(GPIOx == PORTD)
	{
		RCC->APB2RSTR |=  (1 << 5);
		RCC->APB2RSTR &= ~(1 << 5);
	}
	else if(GPIOx == PORTE)
	{
		RCC->APB2RSTR |=  (1 << 6);
		RCC->APB2RSTR &= ~(1 << 6);
	}
}


/*
 * --------------------------------------------------------------
 * FUNCTION: 		MCAL_GPIO_ReadPin
 * DISCRIPTION: 	Read Specific PIN.
 * PARAMETER (IN): 	GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * PARAMETER (in): 	GPIO_PIN_NUMBER: Set PIN number according to @REF GPIO_PINs_define.
 * RETURN VALUE: 	the I/P PIN Value (Two Values based on @REF GPIO_PIN_state >> SET or RESET).
 * NOTES:			----
 * --------------------------------------------------------------
 */
uint8_t MCAL_GPIO_ReadPin (GPIO_typedef *GPIOx, uint16_t GPIO_PIN_NUMBER)
{
	uint8_t bitstatus;
	if(((GPIOx->IDR)&GPIO_PIN_NUMBER)!=GPIO_PIN_RESET)
	{
		bitstatus = GPIO_PIN_SET;
	}
	else
	{
		bitstatus = GPIO_PIN_RESET;
	}
	return bitstatus;
}


/*
 * --------------------------------------------------------------
 * FUNCTION: 		MCAL_GPIO_ReadPort
 * DISCRIPTION: 	Read Specific Port.
 * PARAMETER (IN): 	GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * RETURN VALUE: 	the I/P PORT Value.
 * NOTES: 			----
 * --------------------------------------------------------------
 */
uint16_t MCAL_GPIO_ReadPort (GPIO_typedef *GPIOx)
{
	uint16_t portstatus = GPIOx->IDR;
	return portstatus;
}


/*
 * --------------------------------------------------------------
 * FUNCTION: 		MCAL_GPIO_WritePin
 * DISCRIPTION: 	Write a value on Specific PIN.
 * PARAMETER (IN): 	GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * PARAMETER (IN): 	GPIO_PIN_NUMBER: Set PIN number according to @REF GPIO_PINs_define.
 * PARAMETER (IN): 	Value: The value that will be written to PIN (Two Values based on @REF GPIO_PIN_state >> SET or RESET).
 * RETURN VALUE: 	void
 * NOTES: 			----
 * --------------------------------------------------------------
 */
void MCAL_GPIO_WritePin (GPIO_typedef *GPIOx, uint16_t GPIO_PIN_NUMBER, uint8_t Value)
{
	if(Value!=GPIO_PIN_RESET)
	{
		GPIOx->BSRR = GPIO_PIN_NUMBER;
	}
	else
	{
		GPIOx->BRR  = GPIO_PIN_NUMBER;
	}
}


/*
 * --------------------------------------------------------------
 * FUNCTION:		 MCAL_GPIO_WritePort
 * DISCRIPTION:		 Write a value on Specific PORT.
 * PARAMETER (IN):	 GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * PARAMETER (IN):	 Value: The value that will be written to PORT.
 * RETURN VALUE:	 void
 * NOTES: 			 ----
 * --------------------------------------------------------------
 */
void MCAL_GPIO_WritePort (GPIO_typedef *GPIOx, uint16_t Value)
{
	GPIOx->ODR = Value;
}


/*
 * --------------------------------------------------------------
 * FUNCTION: 		MCAL_GPIO_TogglePin
 * DISCRIPTION: 	Toggle Specific PIN.
 * PARAMETER (IN): 	GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * PARAMETER (IN): 	GPIO_PIN_NUMBER: Set PIN number according to @REF GPIO_PINs_define.
 * RETURN VALUE: 	void
 * NOTES: 			----
 * --------------------------------------------------------------
 */
void MCAL_GPIO_TogglePin (GPIO_typedef *GPIOx, uint16_t GPIO_PIN_NUMBER)
{
	GPIOx->ODR ^= GPIO_PIN_NUMBER;
}


/*
 * --------------------------------------------------------------
 * FUNCTION: 		MCAL_GPIO_LockPin
 * DISCRIPTION: 	The locking mechanism allows the IO configuration to be frozen.
 * PARAMETER (IN): 	GPIOx: where x can be (A..E depending on device used) to select the GPIO Instant.
 * PARAMETER (IN): 	GPIO_PIN_NUMBER: Set PIN number according to @REF GPIO_LOCK_state.
 * RETURN VALUE: 	it returns lock state according to @REF GPIO_LOCK_state (OK if pin config is locked else ERROR).
 * NOTES:
 * --------------------------------------------------------------
 */
uint8_t MCAL_GPIO_LockPin (GPIO_typedef *GPIOx, uint16_t GPIO_PIN_NUMBER)
{
	GPIOx->LCKR |=  GPIO_PIN_NUMBER;
	GPIOx->LCKR |=  (1<<16);
	GPIOx->LCKR &= ~(1<<16);
	GPIOx->LCKR |=  (1<<16);
	uint32_t temp = GPIOx->LCKR;
	if(temp&(1<<16))
	{
		return GPIO_LOCK_OK;
	}
	else
	{
		return GPIO_LOCK_ERROR;
	}
}
