#define F_CPU 20000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> // keskeytyskirjasto
#define TOSI 1
#define EPATOSI 0
// function prototype
void wait(uint16_t time);
void Taski(void);
volatile uint8_t lippu = 0;

void wait(uint16_t time);
	uint8_t test = 0x0f;
int main(void) {
	DDRB = 0xFF;
	
	DDRD= ~((1 << PD2) | (1 << PD3)); // PD.2-port input, kokeile 0xFF
	PORTD = 0x0F; // D-portin pinnit 'ylös'
	GIMSK  |= (1 << INT0) | (1 << INT1);
	MCUCR = (1 << ISC01) | (1 << ISC11); //MCU General Control Register
	// laskeva reuna (PD.2) generoi keskeytyksen
	sei(); // globaali keskeytysten sallinta
	while (1) {
		Taski();
		//PORTB = ~test;
		PORTB = test;
		wait(50);
		PORTB = 0x00;
		wait(50);
	}
}

void wait(uint16_t time) {
	volatile uint16_t i;
	for(i=0;i<2000;i++) {
	     _delay_loop_2(time);
	 }
}
ISR(INT0_vect) { // Ulkoinen keskeytys INT0
	lippu = TOSI;
	wait(40);
}

ISR(INT1_vect) { // Ulkoinen keskeytys INT0
	lippu = TOSI;
	wait(40);
    for (int i = 0; i < 5; i++) {
        PORTB = 0xFF;
        wait(20);
        PORTB = 0x00;
        wait(20);
    }
}
void Taski(void)
{
	if(lippu) { // jos keskeytyspyyntö tapahtunut
		test = ~test; // 0001 1000
		wait(50);
		lippu = EPATOSI;
	}
}