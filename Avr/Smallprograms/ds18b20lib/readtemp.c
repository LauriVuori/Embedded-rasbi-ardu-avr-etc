/*
 * ds1.0.c
 *
 * Created: 14.4.2021 15.49.07
 * Author : lauri_svpuigm
 */ 

#define F_CPU 10000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd_tat.h"


void debugled() {
    DDRD |= (1<< PD6);
    PORTD |= (1<< PD6);
    _delay_ms(30);
    PORTD ^= (1<< PD6);
}
void Tulosta(uint16_t temp_anturista, uint8_t row);
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
void printBinary(uint8_t number) {
	int i, k;
	for (i = 9; i >= 0; i--) {
		k = number >> i;
		if (k & 1) {
			LCD_WriteChar('1');
			_delay_ms(10);
		}
		else {
			LCD_WriteChar('0');
			_delay_ms(10);
		}
	}
}

uint8_t flag1 = 0;
uint8_t flag2 = 0;
int main(void) {
    DDRD ^= (1 << PD2) | (1 << PD3);
    PORTD |= (1 << PD2) | (1 << PD3);
	Timer_init();
	uint16_t temp_anturista = 0;
	uint16_t temp_anturista2 = 0;
	LCD_init(1,0,0);
	LCD_SetCursorXY(0,0);
	LCD_Clear();
    while (1) {
        if (flag1 > 0) {
            temp_anturista = GetTemp(&PORTD, &DDRD, &PIND, (1<<PD4));
            Tulosta(temp_anturista, 0);
            flag1++;
            if (flag1 > 15) {
                flag1 = 0;
            }
        }
        if (flag2 > 0) {
            temp_anturista2 = GetTemp(&PORTD, &DDRD, &PIND, (1<<PD5));
            Tulosta(temp_anturista2, 1);
            flag2++;
            if (flag2 > 15) {
                flag2 = 0;
            }
            
        }
		_delay_ms(1000);
		LCD_SetCursorXY(0,0);
		LCD_Clear();
        if (flag1 == 0) {
            LCD_WriteString("Press 1 temp1");
        }
        if (flag2 == 0) {
            LCD_SetCursorXY(0,1);
            LCD_WriteString("Press 2 temp2");
        }	
    }
}
ISR(TIMER1_OVF_vect) {
	TCNT1 = 4835;
    if (~PIND & (1<<PD2)) {
        flag1 = 1;
        debugled();
    }
    if (~PIND & (1<<PD3)) {
        flag2 = 1; 
        debugled();
    }
}
void Tulosta(uint16_t temp_anturista, uint8_t row) {

	uint16_t temp_apu = 0;

	if(temp_anturista < 0)
	LCD_WriteChar('-');

	temp_apu = temp_anturista/16;
	// anturi palauttaa 9 bitti?, joista 9. bitti kertoo suunnan, ei huomioitu t?ss?
	// resoluutio on 0,5 astetta per bitti
	// l?mp? 0 C vastaa 0x00
	// l?mp? +125 C vastaa 0xFF = 255
	LCD_SetCursorXY(0, row);
	LCD_WriteUINT(temp_apu);

	if(temp_anturista % 2)
	LCD_WriteString(",5 C ");

	else
	LCD_WriteString(",0 C ");
	
	LCD_WriteUINT(temp_anturista);
}