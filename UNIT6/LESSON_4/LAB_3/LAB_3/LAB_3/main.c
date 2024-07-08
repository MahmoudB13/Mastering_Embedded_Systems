/*
 * File:   main.c
 * Author: mahmoud
 *
 * Created on July 6, 2024, 2:08 AM
 */

#include <xc.h>
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect)
{
	PORTD |= 1<<5;
    _delay_ms(1000);
}
ISR(INT1_vect)
{
	PORTD |= 1<<6;
    _delay_ms(1000);
}
ISR(INT2_vect)
{
	PORTD |= 1<<7;
    _delay_ms(1000);
}

int main(void) {
    DDRD = 0xF0;
    DDRB = 0;
    MCUCR |= 0b1101;
    MCUCSR &= ~(1<<6);
    GICR |= (0b111<<5);
    sei();
    while(1)
    {
        PORTD &= ~((1<<5) | (1<<6) | (1<<7)) ;
		_delay_ms(1000);
    }
    return 0;
}
