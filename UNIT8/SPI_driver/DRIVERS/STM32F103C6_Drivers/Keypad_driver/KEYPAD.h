/*
 * KEYPAD.h
 *
 * Created: 17/07/2024 12:25:01 PM
 *  Author: Mahmoud
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "STM32F103C6.h"
#include "GPIO.h"

#define KEYPAD_PORT PORTB

#define R0 GPIO_PIN_0 //INPUT
#define R1 GPIO_PIN_1 //INPUT
#define R2 GPIO_PIN_3 //INPUT
#define R3 GPIO_PIN_4 //INPUT
#define C0 GPIO_PIN_5 //OUTPUT
#define C1 GPIO_PIN_6 //OUTPUT
#define C2 GPIO_PIN_7 //OUTPUT
#define C3 GPIO_PIN_8 //OUTPUT

void KEYPAD_INIT();
char KEYPAD_GET_CHAR();
#endif /* KEYPAD_H_ */
