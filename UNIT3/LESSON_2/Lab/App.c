#include "UART.h"

uint8_t string_buffer[100]="Learn-in-depth : Mahmoud Bahaa";

void main(void)
{
	Uart_send_string(string_buffer);
}