/*
 * DA_4A.c
* Author : Worku Tafara
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
int myMotor = 0;	

int main(void){
	DDRD = 0x30;					
	DDRC = 0x02;					
	PORTC |= (1<<1);			
	TCCR0A |= (1<<COM0A1)|(1<<WGM01)|(1<<WGM00);	
	TCCR0B |= (1<<CS02)|(1<<CS00);				
	PCICR |= (1<<PCIE1);			
	PCMSK1 |= (1<<PCINT9);			
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	while (1) {	
	}		
}

ISR (PCINT1_vect) {
	if (!(PINC & (1<<PINC1))) {
		if (myMotor == 1) {
			OCR0A = 0;
			PORTB &= ~(1<<PORTB2);
		}
		if (myMotor == 1) {
			while ((ADCSRA & (1<<ADIF)) == 0);
			
			OCR0A = ADC;
			PORTB |= (1<<PORTB3);
		}
		_delay_ms(1000);
		myMotor ^= 1;
	}
}
