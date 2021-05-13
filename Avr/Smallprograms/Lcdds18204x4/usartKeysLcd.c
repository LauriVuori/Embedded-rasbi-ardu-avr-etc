#include <avr/io.h>
#define F_CPU 10000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd_tat.h"
#include "project.h"

//#include "project.h"

const __flash uint8_t menu[] = {"Options:\0"};
const __flash uint8_t meter[] = {"Meter:\0"};

// 1. Tutki LCD näytölle kirjoittamista Lcd funktioilla ja printf funktiolla.
// Tee ohjelma joka kysyy käyttäjältä kirjoitetaanko ylärivi,alarivi vai molemmat.
// ja kirjoita teksti luku yhdistelmä näytölle.



volatile uint8_t time = 0;
uint8_t button = 0;
uint8_t topRow = 0;
uint8_t bottomRow = 0;

struct Options {
	uint8_t	writeTopRow;
	uint8_t	writeBottomRow;
	uint8_t	writeBothRows;
	uint8_t setupOn;
	uint8_t counter;
};

void printToTerminalFlash(const __flash uint8_t * szString);
void printTextNum(struct Options * options);
void Timer_init(void);
void setupPrinting(uint8_t button, struct Options * options);

int main(void) {
	
	DDRD |= ~(1 << PD2) | ~(1 << PD3) | ~(1 << PD4);
	DDRD |= (1 << PD5);
	PORTD = 0xFF;
	Timer_init();
	struct Options options = {0};
	
	LCD_init(1, 0, 0); // lcd ON, kursori EI, kursori EI VILKU
	_delay_ms(200);
	
	_delay_ms(200);
	/*fdevopen((void *) LCD_WriteChar, 0);
	printf(”terve”);*/

	uint8_t currentRow = 0;
	uint8_t currentCol = 0;
	_delay_ms(200);
	LCD_SetCursorXY(0, 0);
 	LCD_Clear();
	_delay_ms(200);
 	

	
	while(1) {

		if (options.setupOn == 0) {
			printMenu();
			if (button != 0) {
				//PORTD ^= 0x00 |(1 << PD4);
				setupPrinting(button, &options);
				button = 0;
			}
		}
		else {
			printTextNum(&options);
			if (options.counter > 20) {
				memset(&options, 0 , sizeof(options));
			}
		}
		//button = luenappi();

		//printFlashToLcd(menu);
		_delay_ms(500);
		LCD_SetCursorXY(0, 0);
		LCD_Clear();
		//LCD_WriteUINT(15);
		//LCD_WriteChar('A');
		//drawing(button, &currentRow, &currentCol);
		//LCD_SetCursorXY(0, 0);
		//_delay_ms(500);
		//LCD_Clear();
	}
}


void printTextNum(struct Options * options) {
	if (options->writeTopRow == 1) {
		LCD_SetCursorXY(0, 0);
		printToLcdFlash(meter);
		_delay_ms(35);
		LCD_WriteUINT(options->counter);
		options->counter += 1;
		_delay_ms(35);
	}
	if (options->writeBottomRow == 1) {
		LCD_SetCursorXY(0, 1);
		printToLcdFlash(meter);
		_delay_ms(35);
		LCD_WriteUINT(options->counter);
		options->counter += 1;
		_delay_ms(35);
	}
	if (options->writeBothRows == 1) {
		LCD_SetCursorXY(0, 0);
		_delay_ms(20);
		printToLcdFlash(meter);
		LCD_WriteUINT(options->counter);
		LCD_SetCursorXY(0, 1);
		_delay_ms(20);
		printToLcdFlash(meter);
		LCD_WriteUINT(options->counter);
		options->counter += 1;
	}
}
ISR(TIMER1_OVF_vect) {
	time ++;
	TCNT1 = 4835;

	if(~PIND & (1 <<PD2)) {
		button = 1;
	}
	if(~PIND & (1 <<PD3)) {
		button = 2;
	}
	if(~PIND & (1 <<PD4)) {
		button = 3;
	}

}

void Timer_init(void) {
	// 1 250 000 / 65 535 = 19.073 times in second
	// start timer on 4835 -> 19 times
	// 52.63 ms per overflow
	TCCR1B |= (1 << CS11); // 8 10mHz/ 8 = 1 250 000
	TIMSK |= 1 << TOIE1;
	TCNT1 = 4835;
	sei();
	// TOIE1, timer1 overflow interrupt enable
}
	// uint8_t	writeTopRow;
	// uint8_t	writeBottomRowF;
	// uint8_t	writeBothRows;
void setupPrinting(uint8_t button, struct Options * options) {
	if (button == 1) {
		options->writeTopRow = 1;
		options->setupOn = 1;
		return;
	}
	if (button == 2) {
		options->writeBottomRow = 1;
		options->setupOn = 1;
		return;
	}
	if (button == 3) {
		options->writeBothRows = 1;
		options->setupOn = 1;
		return;
	}
}
