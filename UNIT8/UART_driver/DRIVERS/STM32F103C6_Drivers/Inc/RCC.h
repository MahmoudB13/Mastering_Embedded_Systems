/*
 * RCC.h
 *
 *  Created on: 21 Aug 2024
 *      Author: Mahmoud
 */

#ifndef INC_RCC_H_
#define INC_RCC_H_

//--------------------------------------------------------------
//INCLUDES:
//--------------------------------------------------------------

#include "STM32F103C6.h"
#include "GPIO.h"

//--------------------------------------------------------------
//GENERIC MACROS:
//--------------------------------------------------------------
#define HSI_RCC_CLK				(uint32_t)8000000
#define HSE_RCC_CLK				(uint32_t)16000000
#define PLL_RCC_CLK				(uint32_t)32000000


//--------------------------------------------------------------
uint32_t RCC_GET_SYSCLK_FREQ(void);
uint32_t RCC_GET_HCLK_FREQ(void);
uint32_t RCC_GET_PCLK1_FREQ(void);
uint32_t RCC_GET_PCLK2_FREQ(void);

#endif /* INC_RCC_H_ */
