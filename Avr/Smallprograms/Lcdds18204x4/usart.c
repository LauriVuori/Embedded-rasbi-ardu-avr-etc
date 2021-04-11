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
ISR(USART0_RX_vect) {
	//merkki = UDR; // lue merkki Datarekisteristä
	// if (optionReceived == 0) {
	// 	readString();
	// }
	//readString();
	PORTB ^= 0x01;
	lippu = 1;
	
	// USART_Transmit(merkki); // lähetä merkki
	// // USART_Transmit(0x0A); // uusi rivi, new line
	// // USART_Transmit(0x0D); // rivin alkuun, CR, carridge return
}
void USART_sendString(uint8_t * str) {
	for (int i = 0; *str != '\0'; i++) {
		while (!( UCSRA & (1<<UDRE)));
		UDR = *str;
		str++;
	}

}