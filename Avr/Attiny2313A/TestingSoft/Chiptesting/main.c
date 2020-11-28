
#include <avr/io.h>
#define F_CPU 10000000UL
#include <util/delay.h>
#include "test.c"

// variables: 
// typedef signed char int8_t
// typedef unsigned char uint8_t
// typedef signed int int16_t
// typedef unsigned int uint16_t
// typedef signed long int int32_t
// typedef unsigned long int uint32_t
// typedef signed long long int int64_t
// typedef unsigned long long int uint64_t


int main (void)
{
	DDRB=0xFF; //suuntarekisteri ja suunta ulos
	PORTB=0xff; //B-port 1111 1111 leds off
	DDRD=~((1<<PD2)|(1<<PD3)); //suuntarekisteri , bitti siirto
	PORTD=0xff; //D-porttiin


	while(1){
		while(~PIND & (1<<PD2)) {
			PORTB =~2;
		}
		while(~PIND & (1<<PD3)){
            PORTB =~1;
		}
		PORTB=0xff;
	}
}

