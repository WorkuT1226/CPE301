/*
 * Midterm 1.c
 * Author : Worku Tafara
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#define BAUDRATE 9600
#define BAUD_PRESCALER (F_CPU /BAUDRATE/16 - 1)

void USART_init(unsigned int z);
void ADC_init(void);
void read_ADC (void);
void USART_tx_string(char *x);
unsigned int ADC_temp;
char myArray[1024];
char mystringA[] = "AT\r\n";
char mystringB[] = "AT+CWMODE=1\r\n";
char mystringC[] = "AT+CWLAP";
char mystringD[] = "AT+CWJAP=\"eduroam\",\"#568120\"";
char mystringE[] = "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80";
char mystringF[] = "AT+CIPSEND=100\r\n\\";
char mystringG[] = "AT+CIPCLOSE";

int main(void){
	ADC_init();							
	USART_init(BAUD_PRESCALER);			
	TCNT1 = 49911;					
	sei();								
	while (1) {};			
}

ISR (TIMER1_OVF_vect){
	USART_tx_string(mystringA);
	_delay_ms(625);
	USART_tx_string(mystringB);
	_delay_ms(625);
	USART_tx_string(mystringC);
	_delay_ms(625);
	USART_tx_string(mystringD);
	_delay_ms(625);
	USART_tx_string(mystringE);
	_delay_ms(625);
	USART_tx_string(mystringF);
	_delay_ms(625);
	USART_tx_string(mystringG);
	_delay_ms(625);
	
	read_ADC();
	snprintf(myArray,sizeof(myArray),"GET https://api.thingspeak.com/update?api_key=HX5DID33R61DQXTV&field1=%0d\r\n", ADC_temp);			
	USART_tx_string(myArray);
	TCNT1 = 49911;
}

void USART_init (unsigned int z){
	UBRR0H = (unsigned char)(z>>8);
	UBRR0L = (unsigned char)z;
	UCSR0C = (1 << TXEN0);
	UCSR0B = (3 << UCSZ00);
}

void ADC_init (void){
	ADMUX = (0<<REFS1)|					
	(1<<REFS0)|							
	(0<<ADLAR)|							
	(0<<MUX2)|							
	(0<<MUX1)|							
	(0<<MUX0);
	ADCSRA = (1<<ADEN)|				
	(0<<ADSC)|						
	(0<<ADATE)|							
	(0<<ADIF)|							
	(0<<ADIE)|							
	(1<<ADPS2)|
	(0<<ADPS1)|
	(1<<ADPS0);
	TCCR1B |= (1<<CS12) | (1<<CS10);
	TIMSK1 = (1<<TOIE1);				
	TCNT1 = 49911;						
}

void read_ADC (void)	{
	unsigned char index=4;
	ADC_temp = 0;
	while (index--){
		ADCSRA |= (1<<ADSC);
		while(ADCSRA & (1<<ADSC));
		ADC_temp += ADC;
	}
	ADC_temp = (ADC_temp / 2);
}

void USART_tx_string (char *x){
	while ((*x != '\0')){
		while (!(UCSR0A & (1 << UDRE0)));
		UDR0 = *x;
		x++;
	}
}