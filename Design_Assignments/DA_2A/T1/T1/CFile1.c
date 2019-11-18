#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL
int main(void){
	DDRB |= (1<<3);
	while (1)
	_delay_ms(250);
	PORTB &= ~(1<<3);
	_delay_ms(375);
	PORTB |= (1<<3);
	}
}
