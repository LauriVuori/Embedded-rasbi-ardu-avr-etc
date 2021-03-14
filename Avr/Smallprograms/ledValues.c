
#include <avr/io.h>
#define F_CPU 20000000UL
#include <util/delay.h>


int main (void)
{
	DDRB=0xFF;
	PORTB=0xFF;
	DDRD=~((1<<PD2)|(1<<PD3));
	PORTD=0xff;
	uint8_t output = 0x00;
	uint8_t result = 0x00;
	uint8_t shifted = 0x00;
	uint8_t counter = 0;



	while(1) {
		if(~PIND & (1<<PD2)) {
			_delay_ms(100);
			output = output << 1 | 0x01;
			counter++;

		}
		else if(~PIND & (1<<PD3))
		{
			_delay_ms(100);
			output <<= 1;
			counter++;
		
		}
		else {
			if (counter > 8) {
				output = 0;
				counter = 0;
				for (int i = 0; i < 5; i++) {
					PORTB = ~PORTB;
					_delay_ms(100);
				}
			}
			else if (counter == 8) {
			shifted = output >> 5;
			result = 0x01;
			for (int i = 1; i <= shifted; i++) {
				result = result | 0x01<< i;
			}

			PORTB = ~result;
			}
			else {
				PORTB = ~output;
			}
		}
	}
}