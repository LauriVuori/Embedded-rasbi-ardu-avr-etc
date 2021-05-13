#define F_CPU 10000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile  char time = 0;
ISR(TIMER0_OVF_vect ) {
	time ++;
	TCNT0 = 6;
	//PORTB = time;
}
int main () {
	DDRB = 0xff;
	PORTB = 0x00;
	TIMSK = (1 << TOIE0); //TIMSK = 1; (TOIE0)
	TCCR0A = 2; // TCCR0 = 2; there is no TCCR0 in attiny2313
	sei();
	while (1) {
			PORTB=time;
            for (int i = 0; i < 5; i++) {
                PORTB = 0xFF;
                _delay_ms(100);
                PORTB =0x00;
                _delay_ms(100);
            }
	}
	
}