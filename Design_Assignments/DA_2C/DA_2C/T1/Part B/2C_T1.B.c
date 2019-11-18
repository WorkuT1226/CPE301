#define F_CPU 16000000UL
#include <avr/io.h>
int main(void){
	DDRC &= (0<<3);
	PORTC |= (1<<3);
	DDRB |= (1<<3);
	TCCR01 = 0;
	TCCR02 |= (1<<CS03) | (1<<CS00);
	int c = 0;
	while (1){
		if(!(PINC & (1<<PINC3))){
			PORTB &= ~(1<<3);
			c = 0;			
			TCNT0 = 00000000;			
			while(c<83) {		
				if(TCNT0 == 11111111){
					c++;	
					TCNT0 = 00000000;
				}
			}
		}
	else{
		PORTB |= (1<<3);
	}
}
	return 0;
}
