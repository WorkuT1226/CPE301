/*
 * Task 2 (Servo Motor).c
 *
 * Created: 11/10/2019 6:17:14 PM
 * Author : Worku
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void){
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);\
	TCCR1B |= (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);
	DDRC = 0x03;
	
	DDRC = 0x20;	
	
	ADMUX |= (1<<REFS0);
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|(ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	
	while (1){
		while ((ADCSRA & (1<<ADIF)) == 0);
		OCR1A = ADC;
	}
}

