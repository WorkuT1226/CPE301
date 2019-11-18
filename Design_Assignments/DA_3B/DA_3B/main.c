#define F_CPU 16000000UL
#define BAUD_RATE 9600
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void usart_2(unsigned int x);

int main(void){
	ADMUX = (0<<REFS1)|
	(1<<REFS0)|
	(0<<ADLAR)|
	(1<<MUX2)|
	(0<<MUX1)|
	(1<<MUX0);
	
	ADCSRA =(1<<ADEN)| 
	(0<<ADSC)|
	(1<<ADATE)|
	(0<<ADIF)|
	(0<<ADIE)|
	(1<<ADPS2)|
	(0<<ADPS1)|
	(1<<ADPS0);
	TCCR1B = 5;
	TIMSK1 = (1<<TOIE1);
	TCNT1 = 49911;
	sei();
	while(1){}
}

ISR(TIMER1_OVF_vect){
	ADCSRA|=(1<<ADSC);
	while((ADCSRA&(1<<ADIF)) == 0);
	
	ADCSRA |= (1<<ADIF);
	
	int time = ADCL;
	time = time|(ADCH<<8);
	time = (time/1024) * 4096/10;
	usart_2((time/100)+'0');
	time = time%100;
	usart_2((time/10) + '0');
	time = time%10;
	TCNT1 = 49911; 
}
void usart_1(){
	UCSR0B = (1<<TXEN0);
	UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
	UBRR0L = F_CPU/16/BAUD_RATE - 1;
}

void usart_2(unsigned int x){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = x;						
}

void usart_display(char *myString){
	int index = 0;
	while(myString[index] != 0)
	usart_2(myString[index]);
}