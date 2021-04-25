#include <avr/io.h>
#define F_CPU 10000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd_tat.h"
#define SECOND F_CPU/255

volatile uint16_t time = 0;

uint16_t timestart = 0;
uint16_t timeend = 0;
uint16_t difference = 0;


//volatile  uint8_t count = 0;
uint8_t loop = 0;
// uint16_t adc_data = 0;


void Timer_initattiny(void) {
	// TCCR1B |= (1 << ICES1) | (1 << CS12);
	TCCR0B |= (1 << CS00);
	TIMSK |= (1 << TOIE0);
	TCCR1B |= (1 << ICES1) | (1 << CS10);
	TIFR = (1<<ICF1);
}

void Timer_initatmega(void) {

    TCCR0 |= 1 << CS00;
	TIMSK |= (1 << TOIE0);
	TCCR1B |= (1 << ICES1) | (1 << CS10);
	TIFR = (1<<ICF1);
}



ISR(TIMER0_OVF_vect) {
	time++;
}

void printhz(uint16_t timedifference, uint8_t cpuDivisor);
int main(void){
	Timer_initattiny();
	uint16_t t;
	uint16_t t2;
	

	LCD_init(1, 0, 0);
	//DDRA &= ~(1<<3);
	uint8_t count = 0;


	// fdevopen((void *) LCD_WriteChar, 0);
	_delay_ms(100);
	//DDRA &= ~(1<<3); // ADC.3 input
	LCD_Clear();
	sei(); // globaali keskeytys sallittu
	while(1) {
		TIFR = (1<<ICF1);
		while ((TIFR&(1<<ICF1)) == 0); 
		time = 0;
		t2 = ICR1;
		t = time;
		//t = time;
		//time = 0;
		
		TIFR = (1<<ICF1);		

		while ((TIFR&(1<<ICF1)) == 0);
		t = time - t;
		t2 = ICR1 - t2;
		LCD_Clear();
		if (t < 170) {
			printhz(t2,1);
		}
		else {
			printhz(t,0);
		}
		_delay_ms(50);
	}
}
void printhz(uint16_t timedifference, uint8_t cpuDivisor) {
	cli();
	uint16_t hz1 = 0;
	if (cpuDivisor == 1) {
		hz1 = (F_CPU/timedifference);
	}
	else {
		hz1 = (SECOND/timedifference);
	}
	LCD_WriteUINT(hz1);
	LCD_WriteString(" hz");
	sei();
}