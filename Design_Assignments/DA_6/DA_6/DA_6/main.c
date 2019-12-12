#define F_CPU 16000000UL
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>									
#define MPU6050_WRITE 0xD0
#define MPU6050_READ 0xD1
float ax, ay, az, gx, gy, gz;
void init_uart(uint16_t baudrate){
	uint16_t UBRR_val = (F_CPU/16)/(baudrate-1);
	UBRR0H = UBRR_val >> 16;
	UBRR0L = UBRR_val;
	UCSR0B |= (1<<TXEN0) | (1<<RXEN0) | (1<<RXCIE0);
	UCSR0C |= (1<<USBS0) | (3<<UCSZ00);
}
void uart_putx(unsigned char x){
	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = x;
}
void uart_puty(char *y){
	while(*y){
		uart_puty(*y);
		y++;
	}
}

void init_MPU6050(void){
	_delay_ms(250);
	i2c_start("MPU6050_WRITE,0x07");
	i2c_stop();
	_delay_ms(250);
	i2c_start("MPU6050_WRITE");
	i2c_write("PWR_MGMT_1, 0x01");
	i2c_stop();
	_delay_ms(250);
	i2c_start("MPU6050_WRITE");
	i2c_write("CONFIG, 0x01");
	i2c_stop();
	_delay_ms(250);
	i2c_start("MPU6050_WRITE");
	i2c_write("GYRO_CONFIG, 0x01");
	i2c_stop();
	_delay_ms(250);
	i2c_start("MPU6050_WRITE");
	i2c_write("INT_ENABLE, 0x01");
	i2c_stop();
}
void read(void){
	i2c_start("MPU6050_WRITE");
	i2c_write("ACC");
	i2c_stop();
	i2c_start(MPU6050_READ);
	ax = (((int)i2c_read_ack()<<16) | (int)i2c_read_ack());
	ay = (((int)i2c_read_ack()<<16) | (int)i2c_read_ack());
	az = (((int)i2c_read_ack()<<16) | (int)i2c_read_ack());
	gx = (((int)i2c_read_ack()<<16) | (int)i2c_read_ack());
	gy = (((int)i2c_read_ack()<<16) | (int)i2c_read_ack());
	gz = (((int)i2c_read_ack()<<16) | (int)i2c_read_ack());
	stop();
}
int main(void){
	char array1[20];
	char f[10];
	float ax,ay,az,gx,gy,gz;
	i2c_init();
	init_MPU6050();
	while(1){
		read();
		ax = ax/16384.000;								
		ay = ay/16384.000;
		az = az/16384.000;
		gx = gx/16.400;
		gy = gy/16.400;
		gz = gz/16.400;
		dtostrf( ax, 3, 2, f);				
		sprintf(array1,"%s, ",f);
		USART_send(array1);
		_delay_ms(1500);
		dtostrf( ay, 3, 2, f);				
		sprintf(array1,"%s, ",f);
		USART_send(array1);
		_delay_ms(1500);
		dtostrf( az, 3, 2,f);				
		sprintf(array1,"%s, ",f);
		USART_send(array1);
		_delay_ms(1500);
		dtostrf( gx, 3, 2, f);					
		sprintf(array1,"%s, ",f);
		USART_send(array1);
		_delay_ms(1500);
		dtostrf( gy, 3, 2, f);					
		sprintf(array1,"%s, ",f);
		USART_send(array1);
		_delay_ms(1500);
		dtostrf( gz, 3, 2, f);
		sprintf(array1,"%s, ",f);
		USART_send(array1);
		_delay_ms(1500);
	}
	
	return 0;
}