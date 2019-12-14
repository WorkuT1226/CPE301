#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/twi.h>
#include "i2c_master.h"
#define F_SCL 100000UL
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 32 )/2)
void i2c_init(void){
	TWBR = (uint8_t)TWBR_val;
}
uint8_t i2c_start(uint8_t address){
	TWCR = 0;
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while( !(TWCR & (1<<TWINT)) );
	if((TWSR & 0xF8) != TW_START){ return 1; }
	TWDR = address;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while( !(TWCR & (1<<TWINT)) );
	uint8_t twst = TW_STATUS & 0xF8;
	if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK) ) return 1;
	
	return 0;
}

uint8_t i2c_write(uint8_t data){
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	
	if( (TWSR & 0xF8) != TW_MT_DATA_ACK ){
		 return 1; 
		 }
	else 
	return 0;
}

uint8_t i2c_read_ack(void){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	while( !(TWCR & (1<<TWINT)) );
	return TWDR;
}

uint8_t i2c_read_nack(void){
	TWCR = (1<<TWINT) | (1<<TWEN);
	while( !(TWCR & (1<<TWINT)) );
	return TWDR;
}

uint8_t i2c_transmit(uint8_t address, uint8_t* D, uint16_t l)
	if (i2c_start(address | I2C_WRITE)) return 1;
	
	for (uint16_t i = 0; i < l; i++){
		if (i2c_write(d[i])) return 1;
	}
	i2c_stop();
	return 0;
}

uint8_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length){
	if (i2c_start(address|i2c_read)){ 
	return 1;
	}
	for (uint16_t i = 0; i < (length-1); i++){
		d[i] = i2c_read_ack();
	}
		d[(l-1)] = i2c_read_nack();
		i2c_stop();
	return 0;
}

uint8_t i2c_writeReg(uint8_t dadd, uint8_t radd, uint8_t* d, uint16_t l){
	if (i2c_start(dadd | 0x00)){ 
	return 1;
	}
	i2c_write(radd);
	for (uint16_t i=0; i < l; i++){
		if (i2c_write(d[i])) 
		return 1;
	}
	i2c_stop();
	return 0;
}

uint8_t i2c_readReg(uint8_t dadd, uint8_t radd, uint8_t* d, uint16_t l){
	if (i2c_start(dadd)){
	return 1;
	}
}
	i2c_write(radd);

	if (i2c_start(dadd | 0x01)){ 
	return 1;
	}
	for (uint16_t i = 0; i <(l-1); i++){
		d[i] = i2c_read_ack();
	}
		d[(l-1)] = i2c_read_nack();
		i2c_stop();
	return 0;
}

void i2c_stop(void){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

