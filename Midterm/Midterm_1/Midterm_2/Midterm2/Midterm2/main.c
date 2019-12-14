#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "i2c_master.h"
#include "uart.h"
#include "apds.h"

FILE UART_string = FDEV_SETUP_STREAM(uart_putchar, NULL , _FDEV_SETUP_WRITE);
char result[512];
int main(void){
	uint16_t R = 0, G = 0, B= 0;
	i2c_init();
	init_uart();
	stdout = &UART_string;
	APDS_init();
	_delay_ms(2500);
	printf("AT\r\n");
	_delay_ms(2500);
	printf("AT+CWMODE=1\r\n");
	_delay_ms(2500);
	printf("AT+CWJAP=\"hello world\"\r\n");
	while (1){
	_delay_ms(2500);
	printf("AT+CIPMUX=0\r\n");
	_delay_ms(2500);
	printf("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
	_delay_ms(2500);
	RGB_reader(&R, &G, &B);
	printf("AT+CIPSEND=104\r\n");
	printf("GET https://api.thingspeak.com/update?api_key=5H30LGDINC9QIK32&field1=0\r\n", R,G,B);
	_delay_ms(2500);
	}
}
