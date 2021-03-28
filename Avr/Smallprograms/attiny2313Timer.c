#define F_CPU 10000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


void wait(uint16_t time); // function prototype
volatile  char time = 0;
volatile  char divisor = 2;
ISR(TIMER1_OVF_vect) {
	//PORTB = PORTB ^ MASK;
	// invertoi PD.4 eli RED-LED
	time ++;
	TCNT1 = 0; // onko pakollinen

}
void Timer_init(void) {
	// timer start, jakoluku CLK/64
	// TCCR1B |= (1<<CS11) | (1<<CS10); // cs12, cs 11, cs 10 = tccr1b
	
	TCCR1B |= (1<< CS12); // 256 10mHz/ 256 = 39062.5
	TIMSK |= 1 << TOIE1;
	TCNT1 = 4;
	//TCCR0 = 4;
	// TOIE1, timer1 overflow interrupt enable
}

void io_init(void) {
	DDRB = 0xFF; // RED-LED
}

void Led_init(void) {
	PORTB = 0xF0; // 0001 0000
}

void ext_int_init(void) {
	DDRD= ~((1 << PD2) | (1 << PD3)); // PD.2-port input, kokeile 0xFF
	PORTD = 0x0F; // D-portin pinnit 'ylös'
	GIMSK  |= (1 << INT0) | (1 << INT1);
	MCUCR = (1 << ISC01) | (1 << ISC11); //MCU General Control Register
}

ISR(INT0_vect) { // Ulkoinen keskeytys INT0
	divisor += 2;
	//PORTB ^= 0x80;
}

ISR(INT1_vect) { // Ulkoinen keskeytys INT1
	if (divisor >= 4) {
		divisor -=2;
	}
}

int main(void) {
	io_init();
	Led_init();
	ext_int_init();
	Timer_init();
	int counter = 0;
	sei(); // Global Interrupt Enable
	while(1){
		if (time % divisor == 1) {
			PORTB = PORTB ^ 0x0F;
		}
	}
}



