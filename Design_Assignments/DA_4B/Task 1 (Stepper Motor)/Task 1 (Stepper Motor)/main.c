/*
 * Task 1 (Stepper Motor).c
 *
 * Created: 11/10/2019 6:14:01 PM
 * Author : Worku 
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){
	DDRC = 0xFF;
	TCCR1A |= (1<<WGM01);
	TCCR1B |= (1<<WGM12)|(1<< CS12)|(1<<CS10);	
	
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	while (1){
		while ((ADCSRA & (1<<ADIF)) == 0);
		OCR1A = ADC;
		
		TCNT1 = 0;
		while (TCNT0 != OCR1A) {}
		PORTC = 0xF9;
		
		TCNT1 = 0;					
		while (TCNT0 != OCR1A) {}
		PORTC = 0xF3;
		
		TCNT1 = 0;					
		while (TCNT0 != OCR1A) {}	
		PORTC = 0xF6;				
		
		TCNT1 = 0;					
		while (TCNT0 != OCR1A) {}	
		PORTC = 0xFF;			
	}
}
