/********************************************************************
// ** DS1820 Funktiot by Jukka Pitk�nen
// ** GetTemp-korjaus, Olli-Pekka Korpela
// ** Further modified by Lauri Vuori (More functionality)
********************************************************************/

// ds18b20Temp(&PORTD, &DDRD, &PIND, ( 1 << PD5 ));
#include <avr/io.h>
#include <util/delay.h>
#include "ds1820.h"
//todo + - 
int16_t GetTemp(uint8_t *port, uint8_t *datadirection, uint8_t *portin, uint8_t pinbit) {
    int16_t data1 = 0;  
	int16_t data2 = 0;  
    OwReset(port, datadirection, portin, pinbit);

	
    OwWriteByte(0xCC, port, datadirection, portin, pinbit);  


	OwWriteByte(0x44, port, datadirection, portin, pinbit);

	_delay_loop_2(DELAY45);

    OwReset(port, datadirection, portin, pinbit);

	OwWriteByte(0xCC, port, datadirection, portin, pinbit); 


	OwWriteByte(0xBE, port, datadirection, portin, pinbit); 

	data1 = OwReadByte(port, datadirection, portin, pinbit);


	//printBinary(lsb);
	//LCD_SetCursorXY(0,1);
	//LCD_WriteUINT(lsb);
	data2 = OwReadByte(port, datadirection, portin, pinbit);


	//printBinary(msb);
	//LCD_SetCursorXY(0,1);
	//printBinary(msb);
	//LCD_WriteUINT(msb);
    OwReset(port, datadirection, portin, pinbit);
	//OwReset();

	//lsb |= (msb << 8);
	data2 <<= 8;
	//printBinary(lsb);
	data1 |= data2;
/*
	LCD_SetCursorXY(0,1);
	printBinary(msb);
	LCD_WriteUINT(msb);*/
	return data1;

}
uint8_t OwReset(uint8_t *port, uint8_t *datadirection, uint8_t *portin, uint8_t pinbit) {
	uint8_t temp=0;

	*datadirection |= pinbit; 
	*port &= ~(pinbit);  
	_delay_loop_2(DELAY500); 

	*datadirection &= ~pinbit;
	*port |= pinbit;  
	_delay_loop_2(DELAY60); 

	temp = *portin & pinbit; 
	_delay_loop_2(DELAY400); 

	return temp;
}

uint8_t OwReadByte(uint8_t *port, uint8_t *datadirection, uint8_t *portin, uint8_t pinbit) {
	uint8_t data = 0;  
	uint8_t w = 0;     

	for(w = 0; w <= 7; w++) {
		data >>= 1;    
		*datadirection |= pinbit;  
		*port &= ~(pinbit); 
		_delay_loop_2(DELAY50); 

		*datadirection &= ~pinbit;
		*port |= pinbit;   
		_delay_loop_2(DELAY45); 

		if(*portin & pinbit) {  
			data |= 0x80;
		}

		else {
			data &= 0x7F;
		}
		
		_delay_loop_2(DELAY60);
	}
	return data;  
}


void OwWriteByte(uint8_t data, uint8_t *port, uint8_t *datadirection, uint8_t *portin, uint8_t pinbit) {
	uint8_t e = 0;

	for(e = 0; e < 8; e++) {
		if(data & 0x01) {
			*datadirection |= pinbit;
			*port &= ~(pinbit);  
			_delay_loop_2(1);
			*datadirection &= ~(pinbit);
			*port |= pinbit;
			_delay_loop_2(DELAY60);
		}

		else {
			*datadirection |= pinbit;

			*port &= ~(pinbit);    
			_delay_loop_2(DELAY60);
			*datadirection &= ~(pinbit);
			*port |= (pinbit);
			_delay_loop_2(1);
		}
		data >>= 1;  
	}
}