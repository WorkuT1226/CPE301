 #include <avr/io.h>
 #include <util/delay.h>
 #define F_CPU 16000000UL

 int main(void){
	 DDRC &= (0<<3);
	 PORTC |= (1<<3);
	 DDRB |= (1<<3);
	 
	 while(1){

		 if(!(PINC & (1<<PINC3))){
			 PORTB &= ~(1<<3);
			 _delay_ms(1333);
		 }

		 else{
			 PORTB |= (1<<3);

		 }
	 }

	 return 0;
 }