#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define XTAL 10000000 // MCU:n kellotaajuus
#define BAUD 9600 // sarjaportin nopeus 9600 bps

void USART_sendString(uint8_t str[30]);
void USART_Transmit(uint8_t data);
void USART_Init(void);
#define WAIT(time) for(uint16_t i=0;i<2000;i++)_delay_loop_2(time); 
void ledsInit(void);
// prototypes



uint8_t merkki = 'A';
int main(void) {
	uint8_t merki = 'V';
	uint8_t mer = 'R';
	USART_Init();
	ledsInit();
	sei(); // global interrut ON
	while(1) {
		USART_sendString("Terve\n\r");
		//USART_Transmit(merkki);
		WAIT(500);
		// USART_Transmit(merki);
		// WAIT(200);
		// USART_Transmit(mer); 
		// WAIT(200);
		//USART_Transmit(0x0A); // uusi rivi, new line
		//USART_Transmit(0x0D); // rivin alkuun, CR, carridge return
		//WAIT(200);
	}
}
void ledsInit(void) {
	DDRB = 0xFF;
	PORTB = 0x00;
}
// USART eli sarjaportin asetukset, 8 data, 1 stop bit, 8N1
void USART_Init(void) {




// USART Baud Rate Registers – UBRRL and UBRRH
UBRRH = 0x00; // write high register first
UBRRL = ((XTAL/16)/BAUD)-1;
// rxen-receive, txen transmit
// USART Control and Status Register B –UCSRB
UCSRB |= (1<<RXEN)|(1<<TXEN) | (1<<RXCIE); // 0001 1000
UCSRA |= (1 << RXC);
//UCSRB |= 1<<RXCIE; // rx interrupt enable, 1xx1 1xxx

// USART Control and Status Register C – UCSRC
// UCSRC = 0x86; // 8 Data, 1 Stop, No Parity 1xxx x11x
UCSRC |= (1<<UCSZ1)|(1<<UCSZ0);
}
// usart receive interrupt
ISR(USART0_RX_vect) {
	merkki = UDR; // lue merkki Datarekisteristä
	PORTB ^= 0xFF;
	// USART_Transmit(merkki); // lähetä merkki
	// // USART_Transmit(0x0A); // uusi rivi, new line
	// // USART_Transmit(0x0D); // rivin alkuun, CR, carridge return
}



void USART_sendString(uint8_t str[30]) {
	for (int i = 0; str[i] != '\0'; i++) {
		while (!( UCSRA & (1<<UDRE)));
		UDR = str[i];
	}
	
}
// *** Lähetä merkki USART datarekisteriin *****************
void USART_Transmit(uint8_t data) {
	// If UDRE is one, the buffer is empty, and therefore ready to be written
	while (!( UCSRA & (1<<UDRE)));
	// 0010 0000, odota kunnes UDRE == 1
	// UDRE on 1, jos puskuri on tyhjä, eli ed. merkki on lähetetty
	// Bit 5 – UDRE: USART Data Register Empty, if 1
	/*
	UCSRA xx0x xxxx jos edellistä merkkiä lähetetään
	1<<UDRE 0010 0000
	AND & ---------
	0000 0000 eli false, ! invertoi, joten tosi-true eli odota
	*/ 

	// Put data into buffer, sends the data
	UDR = merkki; // lähtevä merkki datarekisteriin
} 

