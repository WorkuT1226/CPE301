#define BAUD 9600
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/setbaud.h>
void USART_tx_string(char*x);
void USART_tx_char (char i);
void USART_init(void);				
float usart_temp = 2.18;		
char myArray[100];	
char L[] = " ";						

int main(void){
	USART_init();				
	TCCR1B |= (1<<CS12) | (1<<CS10);	
	TIMSK1 = (1<<TOIE1);				
	TCNT1 = 49911;
	sei();								
}
void USART_init (void){
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);
	UBRR0L = UBRRL_VALUE;
	UBRR0H = UBRRH_VALUE;
}

ISR (TIMER1_OVF_vect){
	USART_tx_string(L);	
	USART_tx_char('3');			
	USART_tx_string(L);	
	USART_tx_string("Hello World");				
	USART_tx_string(L);				
	snprintf(myArray, sizeof(myArray), "%f\r\n", usart_temp);	
	USART_tx_string(myArray);			
	USART_tx_string(L);			
	TCNT1 = 49911;						
}

void USART_tx_char (char i){
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = i;					
}

void USART_tx_string (char*x){
	while ((*x != '\0')){
		while (!(UCSR0A & (1<<UDRE0)));	
		UDR0 = *x;					
		x++;						
	}
}
