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




void test();

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