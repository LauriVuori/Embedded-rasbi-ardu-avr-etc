
#include <avr/io.h>
#include <util/delay.h>

void wait(uint16_t time);

int main(void) {
	DDRB = 0xFF; 
	unsigned char kuvio = 0x55; 
	uint8_t kuvio8 = 0x55;
	
	uint16_t kuvio16 = 0x055;
	uint32_t kuvio32 = 0x0055;
	uint8_t counter = 0;
	while(1) {
		PORTB = 0xF0;
		wait(500);
		if (counter == 0) {
			PORTB = kuvio8;
		}
		else if (counter == 1) {
			PORTB = kuvio8;
		}
		else if (counter == 2) {
			PORTB = kuvio8;
		}
		wait(500);
		PORTB = 0x0F;
		wait(500);
		if (counter == 2) {
			counter = 0;
		}
		else{
			counter++;
		}
	}
}

void wait(uint16_t time) {
	volatile uint16_t i;
	// for(i=0;i<2000;i++) {
	//     _delay_loop_2(time);
	// }
}
