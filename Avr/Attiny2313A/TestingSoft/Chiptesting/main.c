
#include <avr/io.h>
#define F_CPU 10000000UL
#include <util/delay.h>


int main (void)
{
	DDRB=0xFF; //suuntarekisteri ja suunta ulos
	PORTB=0xff; //B-porttiin 1111 1111 , looginen alatila -> virta kulkee
	DDRD=~((1<<PD2)|(1<<PD3)); //suuntarekisteri , bitti siirto
	PORTD=0xff; //D-porttiin



	while(1)
	{

		//	PIND		1111 1111
		
		//Tilanne jos nappia ei painettu
		//	~PIND		0000 0000
		//	(1<<PD2)	0000 0100
		//		&		0000 0000
		// tulos		0000 0000 ep?tosi
		
		//Tilanne jos nappia painettu
		//	PIND		1111 1011
		// ~PIND		0000 0100
		// (1<<PD2)		0000 0100
		//	&			0000 0100
		// tulos		0000 0100 tosi koska poikkeaa nollasta

		//~PIND eli invertoidaan koko D-portti
	int a = 0;
	int suunta = 0;
		while(~PIND & (1<<PD2)) 
		{

			_delay_ms(60);
			PORTB=~(0x07 << a); // looginen alatila on ledi p??ll? 1111 1110 1111 1100
			if ((a <= 5) && (suunta == 0)){
				a++;
				if (a == 5){
					suunta = 1;
				}
			}
			else if((a >= 0) && (suunta == 1)){
				a--;
				if (a == 0){
					suunta = 0;
				}
			}
			
		}
		while(~PIND & (1<<PD3))
		{
			_delay_ms(100);
			PORTB=0b10101010;
			_delay_ms(100);
			PORTB=~0b10101010;
		}
		
		
		PORTB=0xFF;
		/*
		else
		{
			PORTB=0xff;
		}*/
	}
}

