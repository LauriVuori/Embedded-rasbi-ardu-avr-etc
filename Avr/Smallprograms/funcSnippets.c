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
// PD2 upper button
// PD3 lower button

void init_leds(){
	DDRB=0xFF; //suuntarekisteri ja suunta ulos
	PORTB=0xff; //B-port 1111 1111 leds off
	DDRD=~((1<<PD2)|(1<<PD3)); //suuntarekisteri , bitti siirto
	PORTD=0xff; //D-porttiin

}

void init_pwm(){
	DDRB   |= (1 << PB2);                   // PWM output on PB2
	TCCR0A = (1 << COM0A1) | (1 << WGM00);  // phase correct PWM mode
	OCR0A  = 0x10;                          // initial PWM pulse width
		
	TCCR0B = (1 << CS01);   // clock source = CLK/8, start PWM
}



void test(){
	int a = 0;
	int suunta = 0;
		while(~PIND & (1<<PD2)) {
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
		while(~PIND & (1<<PD3)){
            PORTB =~1;
		}
		
		PORTB=0xFF;
}