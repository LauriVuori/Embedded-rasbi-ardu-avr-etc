
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


int main (void){
	// DDRB=0xFF; //suuntarekisteri ja suunta ulos
	// PORTB=0xff; //B-port 1111 1111 leds off
	// DDRD=~((1<<PD2)|(1<<PD3)); //suuntarekisteri , bitti siirto
	// PORTD=0xff; //D-porttiin


	// while(1){
	// 	while(~PIND & (1<<PD2)) {
	// 		PORTB =~15;
	// 	}
	// 	while(~PIND & (1<<PD3)){
    //         PORTB =2;
	// 	}
	// 	PORTB=0xff;
	// }
	    
		
	init_pwm();
	DDRD=~((1<<PD2)|(1<<PD3));
	PORTD=0xff;
	int dimmer = 0;
    while(1){
		if(~PIND & (1<<PD2)) {  

			dimmer = 250;
			// _delay_ms(10);

			// _delay_ms(100);

		}
		
		// if(~PIND & (1<<PD3)){ // 
		// 	dimmer = 0;
		// 	// _delay_ms(100);

		// }
		// for (int i = 0; i < 250; i++){
		// 	OCR0A  = i;
		// 	_delay_ms(10);
		// }
		// for (int i = 10; i < 250; i++){
		// 	DDRB |= (1<<PB3);
		// 	OCR0A  = i;
		// 	_delay_ms(10);
		// }
		// DDRB |= (0<<PB3);
		// for (int i = 250; i > 10; i--){
		// 	DDRB |= (1<<PB4);
		// 	OCR0A  = i;
		// 	_delay_ms(10);
		// }
		// DDRB |= (0<<PB4);
	OCR0A  = dimmer;
	}
}

// for (int i = 0; i < 250; i++){
// 	OCR0A  = i;
// 	_delay_ms(10);
// }