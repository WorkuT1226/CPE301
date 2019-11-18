#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
uint8_t OVF_C = 0;
uint8_t OVF_L = 26;
int main(void){
	DDRB |= (1<<3);
	TCCR01 = 0;
	TCCR02 |= (1<<CS03) | (1<<CS00);
	TCNT0 = 6;
	TIMSK0 = (1<<TOIE0);
	sei();
	while (1) {
	}
}
ISR (TIMER0_OVF_vect){
	OVF_C++;
		if (OVF_C == OVF_L){
			PORTB ^= (1<<3);
				if(OVFLIMIT == 26){
					OVFLIMIT = 38;
				} 
				else{
					OVF_L = 26;
					}
				OVF_C = 0;
			}
	TCNT0 = 6;
}