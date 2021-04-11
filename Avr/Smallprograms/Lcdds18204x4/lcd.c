#include <avr/io.h>
#include <util/delay.h>

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

void printMenu(void) {
	LCD_WriteString("Asetukset");
	LCD_SetCursorXY(0,1);
	_delay_ms(20);
	LCD_WriteString("Tulosta");
	LCD_SetCursorXY(0,0);
	_delay_ms(20);
	_delay_ms(2000);
	LCD_Clear();
	_delay_ms(20);
	LCD_WriteString("1)Ylarivi");
	LCD_SetCursorXY(0,1);
	_delay_ms(20);
	LCD_WriteString("2)alarivi");
	_delay_ms(2000);
	LCD_Clear();
	LCD_SetCursorXY(0,0);
	_delay_ms(20);
	LCD_WriteString("3)Molemmat");
	_delay_ms(2000);
	LCD_Clear();
	_delay_ms(20);
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

	PORTD = ~0x10; // 0110 1111
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

void printFlashToLcd(const __flash uint8_t * text) {
	LCD_WriteString(text);
}