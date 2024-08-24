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

#define FLASH_MEMORY_BASE     						0x08000000UL
#define SYSTEM_MEMORY_BASE    						0x1FFFF000UL
#define SRAM_BASE            						0x20000000UL
#define PERIPHERALS_BASE      						0x40000000UL
#define CORTEX_M3_INTERNAL_PERIPHERALS_BASE 		0xE0000000UL

//--------------------------------------------------------------
//BASE ADDRESS OF NVIC CONTROLLER:
//--------------------------------------------------------------

#define NVIC_BASE 									0xE000E100UL


//--------------------------------------------------------------
//BASE ADDRESSES OF AHB PERIPHERALS:
//--------------------------------------------------------------

//RCC:
#define RCC_BASE 									0x40021000UL

//--------------------------------------------------------------
//BASE ADDRESSES OF APB2 PERIPHERALS:
//--------------------------------------------------------------

//GPIO:
//PORTA AND PORTB ARE FULLY INCLUDED IN LQFP48 PACKAGE:
#define PORTA_BASE 									0x40010800UL
#define PORTB_BASE 									0x40010C00UL

//PORTC AND PORTD ARE PARTIALLY INCLUDED IN LQFP48 PACKAGE:
#define PORTC_BASE 									0x40011000UL
#define PORTD_BASE 									0x40011400UL

//PORTE IS NOT INCLUDED IN LQFP48 PACKAGE:
#define PORTE_BASE 									0x40011800UL

//EXTI:
#define EXTI_BASE 									0x40010400UL

//AFIO:
#define AFIO_BASE 									0x40010000UL

//USART:
#define USART1_BASE 								0x40013800UL

//--------------------------------------------------------------
//BASE ADDRESSES OF APB1 PERIPHERALS:
//--------------------------------------------------------------

//USART:
#define USART2_BASE 								0x40004400UL
#define USART3_BASE 								0x40004800UL

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
	volatile uint32_t EXTICR[4];
	uint32_t reserved;
	volatile uint32_t MAPR2;
}AFIO_typedef;

//--------------------------------------------------------------

//USART REGISTERS:
typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_typedef;

//--------------------------------------------------------------

//NVIC REGISTERS:
#define NVIC_ISER0									*((volatile uint32_t*)(NVIC_BASE+0x00))
#define NVIC_ISER1									*((volatile uint32_t*)(NVIC_BASE+0x04))
#define NVIC_ISER2									*((volatile uint32_t*)(NVIC_BASE+0x08))
#define NVIC_ICER0									*((volatile uint32_t*)(NVIC_BASE+0x80))
#define NVIC_ICER1									*((volatile uint32_t*)(NVIC_BASE+0x84))
#define NVIC_ICER2									*((volatile uint32_t*)(NVIC_BASE+0x88))

//==============================================================

//--------------------------------------------------------------
//PERIPHERAL INSTANCES:
//--------------------------------------------------------------

//RCC:
#define RCC 										((RCC_typedef*) RCC_BASE)

//GPIO:
#define PORTA 										((GPIO_typedef*) PORTA_BASE)
#define PORTB 										((GPIO_typedef*) PORTB_BASE)
#define PORTC 										((GPIO_typedef*) PORTC_BASE)
#define PORTD 										((GPIO_typedef*) PORTD_BASE)
#define PORTE 										((GPIO_typedef*) PORTE_BASE)

//EXTI:
#define EXTI 										((EXTI_typedef*) EXTI_BASE)

//AFIO:
#define AFIO 										((AFIO_typedef*) AFIO_BASE)

//USART:
#define USART1 										((USART_typedef*) USART1_BASE)
#define USART2 										((USART_typedef*) USART2_BASE)
#define USART3 										((USART_typedef*) USART3_BASE)

//==============================================================

//--------------------------------------------------------------
//Generic Macros:
//--------------------------------------------------------------

#define SET_BIT(Reg,Bit_No)							(Reg |= (1 << Bit_No))
#define CLEAR_BIT(Reg,Bit_No)						(Reg &= ~ (1 << Bit_No))
#define TOGGLE_BIT(Reg,Bit_No)						(Reg ^= (1 << Bit_No))
#define READ_BIT(Reg,Bit_No)						((Reg >> Bit_No) & 1)

//==============================================================

//--------------------------------------------------------------
//CLOCK ENABLE MACROS:
//--------------------------------------------------------------

//AFIO:
#define RCC_AFIO_CLK_EN()							SET_BIT(RCC->APB2ENR,0)

//GPIO:
#define RCC_PORTA_CLK_EN()							SET_BIT(RCC->APB2ENR,2)
#define RCC_PORTB_CLK_EN()							SET_BIT(RCC->APB2ENR,3)
#define RCC_PORTC_CLK_EN()							SET_BIT(RCC->APB2ENR,4)
#define RCC_PORTD_CLK_EN()							SET_BIT(RCC->APB2ENR,5)
#define RCC_PORTE_CLK_EN()							SET_BIT(RCC->APB2ENR,6)

//USART:
#define RCC_USART1_CLK_EN()							SET_BIT(RCC->APB2ENR,14)
#define RCC_USART2_CLK_EN()							SET_BIT(RCC->APB1ENR,17)
#define RCC_USART3_CLK_EN()							SET_BIT(RCC->APB1ENR,18)

//--------------------------------------------------------------
//CLOCK RESET MACROS:
//--------------------------------------------------------------

//USART:
#define RCC_USART1_CLK_RESET()						SET_BIT(RCC->APB2RSTR,14)
#define RCC_USART2_CLK_RESET()						SET_BIT(RCC->APB1RSTR,17)
#define RCC_USART3_CLK_RESET()						SET_BIT(RCC->APB1RSTR,18)

//==============================================================

//--------------------------------------------------------------
//IVT numbers:
//--------------------------------------------------------------

//EXTI0->4
#define EXTI0_IRQ									6
#define EXTI1_IRQ									7
#define EXTI2_IRQ									8
#define EXTI3_IRQ									9
#define EXTI4_IRQ									10

//EXTI9_5 -> 23
#define EXTI5_IRQ									23
#define EXTI6_IRQ									23
#define EXTI7_IRQ									23
#define EXTI8_IRQ									23
#define EXTI9_IRQ									23

//EXTI15_10 -> 40
#define EXTI10_IRQ									40
#define EXTI11_IRQ									40
#define EXTI12_IRQ									40
#define EXTI13_IRQ									40
#define EXTI14_IRQ									40
#define EXTI15_IRQ									40

//--------------------------------------------------------------

//USART1->3:
#define USART1_IRQ									37
#define USART2_IRQ									38
#define USART3_IRQ									39


//==============================================================

//--------------------------------------------------------------
//NVIC enable Macros:
//--------------------------------------------------------------

//EXTI:
#define NVIC_EXTI0_IRQ_ENABLE						SET_BIT(NVIC_ISER0,EXTI0_IRQ)
#define NVIC_EXTI1_IRQ_ENABLE						SET_BIT(NVIC_ISER0,EXTI1_IRQ)
#define NVIC_EXTI2_IRQ_ENABLE						SET_BIT(NVIC_ISER0,EXTI2_IRQ)
#define NVIC_EXTI3_IRQ_ENABLE						SET_BIT(NVIC_ISER0,EXTI3_IRQ)
#define NVIC_EXTI4_IRQ_ENABLE						SET_BIT(NVIC_ISER0,EXTI4_IRQ)
#define NVIC_EXTI9_5_IRQ_ENABLE						SET_BIT(NVIC_ISER0,EXTI5_IRQ)
#define NVIC_EXTI15_10_IRQ_ENABLE					SET_BIT(NVIC_ISER1,(EXTI10_IRQ-32))

//--------------------------------------------------------------

//USART:
#define NVIC_USART1_IRQ_ENABLE						SET_BIT(NVIC_ISER1,(USART1_IRQ-32))
#define NVIC_USART2_IRQ_ENABLE						SET_BIT(NVIC_ISER1,(USART2_IRQ-32))
#define NVIC_USART3_IRQ_ENABLE						SET_BIT(NVIC_ISER1,(USART3_IRQ-32))


//--------------------------------------------------------------
//NVIC disable Macros:
//--------------------------------------------------------------

//EXTI:
#define NVIC_EXTI0_IRQ_DISABLE						SET_BIT(NVIC_ICER0,EXTI0_IRQ)
#define NVIC_EXTI1_IRQ_DISABLE						SET_BIT(NVIC_ICER0,EXTI1_IRQ)
#define NVIC_EXTI2_IRQ_DISABLE						SET_BIT(NVIC_ICER0,EXTI2_IRQ)
#define NVIC_EXTI3_IRQ_DISABLE						SET_BIT(NVIC_ICER0,EXTI3_IRQ)
#define NVIC_EXTI4_IRQ_DISABLE						SET_BIT(NVIC_ICER0,EXTI4_IRQ)
#define NVIC_EXTI9_5_IRQ_DISABLE					SET_BIT(NVIC_ICER0,EXTI5_IRQ)
#define NVIC_EXTI15_10_IRQ_DISABLE					SET_BIT(NVIC_ICER1,(EXTI10_IRQ-32))

//--------------------------------------------------------------

//USART:
#define NVIC_USART1_IRQ_DISABLE						SET_BIT(NVIC_ICER1,(USART1_IRQ-32))
#define NVIC_USART2_IRQ_DISABLE						SET_BIT(NVIC_ICER1,(USART2_IRQ-32))
#define NVIC_USART3_IRQ_DISABLE						SET_BIT(NVIC_ICER1,(USART3_IRQ-32))

//==============================================================

#endif /* INC_STM32F103C6_H_ */
