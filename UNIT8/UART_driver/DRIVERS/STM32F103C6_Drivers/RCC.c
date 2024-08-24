/*
 * RCC.c
 *
 *  Created on: 21 Aug 2024
 *      Author: Mahmoud
 */

//--------------------------------------------------------------
//INCLUDES:
//--------------------------------------------------------------

#include "RCC.h"

//--------------------------------------------------------------

const uint8_t APBprescaler_Table[8] = {0, 0, 0, 0, 1, 2, 3, 4};
const uint8_t AHBprescaler_Table[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

uint32_t RCC_GET_SYSCLK_FREQ(void)
{
	switch((RCC->CFGR >> 2) & 0b11)
	{
	case 0:
		return HSI_RCC_CLK;
		break;

	case 1:
		return HSE_RCC_CLK;
		break;

	case 2:
		return PLL_RCC_CLK;
		break;
	}
	return HSI_RCC_CLK;
}

uint32_t RCC_GET_HCLK_FREQ(void)
{
	return RCC_GET_SYSCLK_FREQ() >> AHBprescaler_Table[((RCC->CFGR >> 4) & 0xF)];
}

uint32_t RCC_GET_PCLK1_FREQ(void)
{
	return (RCC_GET_HCLK_FREQ() >> APBprescaler_Table[((RCC->CFGR >> 8) & (0b111))]);
}

uint32_t RCC_GET_PCLK2_FREQ(void)
{
	return (RCC_GET_HCLK_FREQ() >> APBprescaler_Table[((RCC->CFGR >> 11) & (0b111))]);
}
