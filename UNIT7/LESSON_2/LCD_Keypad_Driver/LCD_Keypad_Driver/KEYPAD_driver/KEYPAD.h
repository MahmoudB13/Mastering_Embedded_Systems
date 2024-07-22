/*
 * KEYPAD.h
 *
 * Created: 17/07/2024 12:25:01 PM
 *  Author: Mahmoud
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include <xc.h>
#include "../UTILS.h"

#define KEYPAD_PORT PORTD
#define DATA_DIR_KEYPAD DDRD
#define KEYPAD_PIN PIND	

#define R0 0 //INPUT
#define R1 1 //INPUT
#define R2 2 //INPUT
#define R3 3 //INPUT
#define C0 4 //OUTPUT
#define C1 5 //OUTPUT
#define C2 6 //OUTPUT
#define C3 7 //OUTPUT

void KEYPAD_INIT();
char KEYPAD_GET_CHAR();
#endif /* KEYPAD_H_ */