#include <avr/io.h>
#define F_CPU 20000000UL
#include <util/delay.h>
#include "lcd_tat.h"

#define ROWMAX 2
#define COLMAX 16
void wait(uint16_t time);
void drawing(uint8_t button, uint8_t * currentRow, uint8_t * currentCol);
unsigned char luenappi();
unsigned char test();
void printBinary(uint8_t number, uint8_t * currentRow, uint8_t * currentCol);
int main(void) {
	DDRD = 0xf0;
	PORTD = 0x0f;



	LCD_init(1, 0, 0); // lcd ON, kursori EI, kursori EI VILKU
	uint8_t button = 5;
	uint8_t currentRow = 0;
	uint8_t currentCol = 0;
	wait(1000);
	LCD_Clear();
	LCD_SetCursorXY(currentRow, currentCol);
	while(1) {
		wait (10);
		button = luenappi();
		wait(20);
		drawing(button, &currentRow, &currentCol);
		// if (currentCol > 15) {
		// 	currentCol = 0;
		// }
		// if (button != 0) {
		// 	if ((button < 10) && (currentCol < 16)) {
		// 		LCD_WriteUINT(button);
		// 		LCD_SetCursorXY(currentRow, currentCol);
		// 		currentCol++;
		// 	}
		// }
		// LCD_WriteUINT(PIND);
		wait (100);
	}
}
void printBinary(uint8_t number, uint8_t * currentRow, uint8_t * currentCol) {
	int i, k;
	for (i = 16; i >= 0; i--) {
		k = number >> i;
		if (k & 1) {
			drawing(k, currentRow, currentCol);
		}
		else {
			drawing(k, currentRow, currentCol);
		}
	}
}


void drawing(uint8_t button, uint8_t * currentRow, uint8_t * currentCol) {

	if (*currentRow > 15 ) {
		*currentRow = 0;
	}
	if (button == 16) {
		*currentRow = 0;
		*currentCol = 0;
		LCD_Clear();
		LCD_SetCursorXY(*currentRow, *currentCol);
	}
	if (button == 15) {
		if(*currentCol > 0) {
			*currentCol -= 1;
		}
		else {
			*currentCol += 1;
		}
		LCD_SetCursorXY(*currentRow, *currentCol);
	}
	else if ((button != 0) && (button != 16) && (button != 15)) {
		if (button < 10) {
			LCD_WriteUINT(button);
			*currentRow += 1;
			LCD_SetCursorXY(*currentRow, *currentCol);
		}
		else if (button >= 10) {
			LCD_WriteUINT(button);
			*currentRow += 2;
			LCD_SetCursorXY(*currentRow, *currentCol);
		}

	}
}

unsigned char luenappi() {
	unsigned char a=0x00;

	PORTD = ~0x10; // 1110 1111
	wait(10);
	if (~PIND & 0x01) a = 1;
	if (~PIND & 0x02) a = 2;
	if (~PIND & 0x04) a = 3;
	if (~PIND & 0x08) a = 4;

	PORTD = 0xff;

	PORTD = ~0x20; // 1101 1111
	wait(10);
	if (~PIND & 0x01) a = 5;
	if (~PIND & 0x02) a = 6;
	if (~PIND & 0x04) a = 7;
	if (~PIND & 0x08) a = 8;

	PORTD = 0xff;

	PORTD = ~0x40 ; // 1011 1111
	wait(10);
	if (~PIND & 0x01) a = 9;
	if (~PIND & 0x02) a = 10;
	if (~PIND & 0x04) a = 11;
	if (~PIND & 0x08) a = 12;
	PORTD = 0xff;

	PORTD = ~0x80 ;// 0111 1111
	if (~PIND & 0x01) {while(~PIND & 0x01){a = 13;}}
	if (~PIND & 0x02){ while(~PIND & 0x02){a = 14;}}
	if (~PIND & 0x04) {
		while (~PIND & 0x04) {
			a = 15;
		}
	}
	if (~PIND & 0x08){
		while (~PIND & 0x08){
			a = 16;
		}
	} 
	return (a);
}
// *** Primitive wait() ***
void wait(uint16_t time) {
	volatile uint16_t i;

	for(i=0;i<2000;i++)
	_delay_loop_2(time);
}