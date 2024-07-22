/*
 * STM32F103C6.h
 *
 *  Created on: Jul 17, 2024
 *      Author: Mahmoud
 */

#ifndef INC_STM32F103C6_H_
#define INC_STM32F103C6_H_

//--------------------------------------------------------------
//INCLUDES:
//--------------------------------------------------------------

#include <stdlib.h>
#include <stdint.h>

//==============================================================

//--------------------------------------------------------------
//BASE ADDRESSES OF MEMORIES:
//--------------------------------------------------------------

#define FLASH_MEMORY_BASE     					0x08000000UL
#define SYSTEM_MEMORY_BASE    					0x1FFFF000UL
#define SRAM_BASE            					0x20000000UL
#define PERIPHERALS_BASE      					0x40000000UL
#define CORTEX_M3_INTERNAL_PERIPHERALS_BASE 	0xE0000000UL

//--------------------------------------------------------------
//BASE ADDRESSES OF AHB PERIPHERALS:
//--------------------------------------------------------------

//RCC:
#define RCC_BASE 								0x40021000UL

//--------------------------------------------------------------
//BASE ADDRESSES OF APB2 PERIPHERALS:
//--------------------------------------------------------------

//GPIO:
//PORTA AND PORTB ARE FULLY INCLUDED IN LQFP48 PACKAGE:
#define PORTA_BASE 								0x40010800UL
#define PORTB_BASE 								0x40010C00UL

//PORTC AND PORTD ARE PARTIALLY INCLUDED IN LQFP48 PACKAGE:
#define PORTC_BASE 								0x40011000UL
#define PORTD_BASE 								0x40011400UL

//PORTE IS NOT INCLUDED IN LQFP48 PACKAGE:
#define PORTE_BASE 								0x40011800UL

//EXTI:
#define EXTI_BASE 								0x40010400UL

//AFIO:
#define AFIO_BASE 								0x40010000UL

//--------------------------------------------------------------
//BASE ADDRESSES OF APB1 PERIPHERALS:
//--------------------------------------------------------------

//==============================================================

//--------------------------------------------------------------
//PERIPHERAL REGISTERS:
//--------------------------------------------------------------

//RCC REGISTERS:
typedef struct
{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
}RCC_typedef;

//--------------------------------------------------------------

//GPIO REGISTERS:
typedef struct
{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_typedef;

//--------------------------------------------------------------

//EXTI REGISTERS:
typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_typedef;

//--------------------------------------------------------------

//AFIO REGISTERS:
typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	uint32_t reserved;
	volatile uint32_t MAPR2;
}AFIO_typedef;

//==============================================================

//--------------------------------------------------------------
//PERIPHERAL INSTANCES:
//--------------------------------------------------------------

//RCC:
#define RCC 						((RCC_typedef*) RCC_BASE)

//GPIO:
#define PORTA 						((GPIO_typedef*) PORTA_BASE)
#define PORTB 						((GPIO_typedef*) PORTB_BASE)
#define PORTC 						((GPIO_typedef*) PORTC_BASE)
#define PORTD 						((GPIO_typedef*) PORTD_BASE)
#define PORTE 						((GPIO_typedef*) PORTE_BASE)

//EXTI:
#define EXTI 						((EXTI_typedef*) EXTI_BASE)

//AFIO:
#define AFIO 						((AFIO_typedef*) AFIO_BASE)

//==============================================================

//--------------------------------------------------------------
//CLOCK ENABLE MACROS:
//--------------------------------------------------------------

//AFIO:
#define RCC_AFIO_CLK_EN()			(RCC->APB2ENR) |= (1<<0)

//GPIO:
#define RCC_PORTA_CLK_EN()			(RCC->APB2ENR) |= (1<<2)
#define RCC_PORTB_CLK_EN()			(RCC->APB2ENR) |= (1<<3)
#define RCC_PORTC_CLK_EN()			(RCC->APB2ENR) |= (1<<4)
#define RCC_PORTD_CLK_EN()			(RCC->APB2ENR) |= (1<<5)
#define RCC_PORTE_CLK_EN()			(RCC->APB2ENR) |= (1<<6)

#endif /* INC_STM32F103C6_H_ */
