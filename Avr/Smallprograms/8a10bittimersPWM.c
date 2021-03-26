#include <avr/io.h>
#define F_CPU 10000000UL
#include <util/delay.h>


int main(void) {
	uint8_t PWMval = 0; // pwm value
	uint16_t PWM10val = 0;
	uint8_t flag = 0x00; // direction up down
	DDRB   = (1 << PB2) | (1 << PB3);                   // OUTPUT PB2
	TCCR0A = (1 << COM0A1) | (1 << WGM00);  // phase correct PWM mode 8 bit timer
	TCCR0B = (1 << CS01);   // clock source = CLK/8, start PWM
	
	    TCCR1A = (1 << COM1A1)| (1 << WGM11) | (1 << WGM10); // phase correct pwm mode 10 bit 
	    TCCR1B = (1 << CS10);
	
	while(1) {
		if ((PWMval == 255) || (PWMval == 0)) {
			flag ^= 0x01;
		}
		_delay_ms(5);
		OCR0A  = PWMval;       // write new PWM value
		OCR1A = PWM10val;
	
		if (flag == 1) {            // increment or decrement PWM value
			PWMval++;
			PWM10val += 4;
		}
		else {
			PWMval--;
			PWM10val -= 4;
		}
	}
}