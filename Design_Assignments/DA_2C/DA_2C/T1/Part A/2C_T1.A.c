#define F_CPU 16000000UL
#include <avr/io.h>
int main(void){
	int c = 0;
	TCCR01 = 0;
	TCCR02 |= (1<<CS03) | (1<<CS00);
	DDRB |= (1<<3);
    while (1){
		c=0;
		TCNT0 = 00000000;
		while (c<38){
			if(TCNT0 == 11111111){
				c++;
				TCNT0 = 00000000;
			}
		}
		PORTB = (1<<3);
		c = 0;
		TCNT0 = 00000000;
		while (c<26){
			if(TCNT0 == 11111111){
				c++;
				TCNT0 = 00000000;
			}
		}
		PORTB = (1<<3);
    }
}