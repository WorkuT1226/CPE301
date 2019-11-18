//; AssemblerApplication1.asm
//; Created: 10/5/2019 6:21:20 PM
//; Author : Worku Tafara

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define F_CPU 16000000UL

int main(void){
	DDRB |= (1<<3);
	PORTB |= (1<<3);
	DDRC &= (0<<3);
	PORTC |= (1<<3);
	EIMSK = (1<<INT0);
	EICRA = (1<<ISC01);
	sei ();
	
while (1) {}
}

ISR (INT0_vect)	{
	 PORTB ^= (1<<3);
	_delay_ms(1333);
}