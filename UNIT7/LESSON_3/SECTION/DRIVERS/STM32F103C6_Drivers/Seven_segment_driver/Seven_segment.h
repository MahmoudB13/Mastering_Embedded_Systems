/*
 * Seven_segment.h
 *
 *  Created on: 24 Jul 2024
 *      Author: Mahmoud
 */

#ifndef SEVEN_SEGMENT_DRIVER_SEVEN_SEGMENT_H_
#define SEVEN_SEGMENT_DRIVER_SEVEN_SEGMENT_H_

#include "UTILS.h"

#define SEVEN_SEGMENT_PORT PORTB

#define ZERO	 	0x01
#define ONE 		0x79
#define TWO		 	0x24
#define THREE	 	0x30
#define FOUR	 	0x58
#define FIVE	 	0x12
#define SIX		 	0x02
#define SEVEN	 	0x19
#define EIGHT	 	0x00
#define NINE	 	0x10


void SEVEN_SEGMENT_Init();
void SEVEN_SEGMENT_DISPLAY(uint8_t VAL);

#endif /* SEVEN_SEGMENT_DRIVER_SEVEN_SEGMENT_H_ */
