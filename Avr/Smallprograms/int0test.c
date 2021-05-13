#define F_CPU 10000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> // keskeytyskirjasto
#define TOSI 1
#define EPATOSI 0
// function prototype
void wait(uint16_t time);
void Taski(void);
volatile uint8_t lippu = 0;
uint8_t test = 0x0f;
int main(void) {
	DDRB = 0xFF;
	
	DDRD |= (1<<PD2) | (1 << PD3); // pd2 ja pd3 käyttöön
	PORTD = (1<<PD2) | (1 << PD3); 
	GIMSK  |= (1<<INT0); // general interrupt mask, int 0 käyttöön
	MCUCR = 1 << ISC01; //MCU General Control Register
	// laskeva reuna (PD.2) generoi keskeytyksen
	sei(); // globaali keskeytysten sallinta
	while (1) {
		while(~PIND & (1<<PD3)){
			Taski();
			//PORTB = ~test;
			PORTB = test;
			wait(50);
			PORTB = 0xFF;
			wait(50);
		}
		PORTB = 0xFF;
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
void Taski(void)
{
	if(lippu) { // jos keskeytyspyyntö tapahtunut
		test = ~test; // 0001 1000
		wait(50);
		lippu = EPATOSI;
	}
}