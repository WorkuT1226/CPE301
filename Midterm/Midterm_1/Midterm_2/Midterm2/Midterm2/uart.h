#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"

void init_UART(void){
	uint16_t baud_rate = BRGVAL;
	UBRR0H = baud_rate >> 16;
	UBRR0L = baud_rate & 0xFFFF;
	UCSR0B = ( 1 <<RXEN0)|( 1 <<TXEN0);
	UCSR0C = (3 <<UCSZ00);
}
int uart_putchar(char x, FILE *stream){
	while ( !( UCSR0A & ( 1 <<UDRE0)) );
	UDR0 = x;
	return 0;