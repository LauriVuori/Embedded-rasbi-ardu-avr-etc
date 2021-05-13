#define F_CPU 10000000UL // clockspeed
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
// line feed \n
// carriage return \r

#define XTAL 10000000 // clockspeed for usart
#define BAUD 9600 // baudrate
#define WAIT(time) for(uint16_t i=0;i<2000;i++)_delay_loop_2(time);
void USART_sendString(uint8_t * str);
void USART_SendChar(uint8_t data);
void USART_Init(void);
void USART_ReceiveString();
void sendMenuTerminal(void);
void readString(void);
void printToTerminalFlash(const __flash uint8_t * text);
void ledsInit(void);

// prototypes

//#define MENU "Print text to lcd\nMenu:\n1)Terve\n2)Moro\n3)Jou\n4)Hei\n5)hello\n"
const __flash uint8_t menu[] = {"Print text to lcd\nMenu:\n1)Terve\n2)Moro\n3)Jou\n4)Hei\n5)hello\n\0"};

uint8_t merkki = 'A';
//uint8_t receivedString[20];
uint8_t flag = 0;
// 'uint8_t * {aka unsigned char *}' but argument is of type '__flash const __flash uint8_t (*)[61] {aka __flash const __flash unsigned char (*)[61]}


int main(void) {
	USART_Init();
	ledsInit();
	sei(); // global interrut ON

	while(1) {
		if (flag == 1) {
			PORTB ^= 0x04;
			if (merkki == '1') {
				USART_sendString((uint8_t *)"PRINT1\n");
			}
			if (merkki == '2') {
				USART_sendString((uint8_t *)"PRINT2\n");
			}
			if (merkki == '3') {
				USART_sendString((uint8_t *)"PRINT3\n");
			}
			if (merkki == '4') {
				USART_sendString((uint8_t *)"PRINT4\n");
			}
			if (merkki == '5') {
				USART_sendString((uint8_t *)"PRINT5\n");
			}
			if (merkki == '6') {
				printToTerminalFlash(menu);
			}
			if ((merkki > '6') || (merkki < '0')) {
				printToTerminalFlash(menu);
			}
			flag = 0;
		}
		_delay_ms(200);
	}
}

void printToTerminalFlash(const __flash uint8_t * text) {
	for (int i = 0; *text != '\0'; i++) {
		while (!( UCSRA & (1<<UDRE)));
		UDR = *text;
		text++;
	}
}
void ledsInit(void) {
	DDRB = 0xFF;
	PORTB = 0x00;
}
// USART 8N1
void USART_Init(void) {
	// USART Baud Rate Registers – UBRRL and UBRRH
	UBRRH = 0x00; // write high register first
	UBRRL = ((XTAL/16)/BAUD)-1;
	// rxen-receive, txen transmit
	// USART Control and Status Register B –UCSRB
	UCSRB |= (1<<RXEN)|(1<<TXEN) | (1<<RXCIE); // 0001 1000
	UCSRA |= (1 << RXC);
	//UCSRB |= 1<<RXCIE; // rx interrupt enable
	// USART Control and Status Register C – UCSRC
	// UCSRC = 0x86; // 8 Data, 1 Stop, No Parity
	UCSRC |= (1<<UCSZ1)|(1<<UCSZ0);
}
// usart receive interrupt
ISR(USART0_RX_vect) {
	merkki = UDR; // lue merkki Datarekisteristä
	// if (optionReceived == 0) {
	// 	readString();
	// }
	flag = 1;
	PORTB ^= 0x01;
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

// *** Lähetä merkki USART datarekisteriin *****************
void USART_SendChar(uint8_t data) {
	while (!( UCSRA & (1<<UDRE)));
	UDR = merkki;
}

