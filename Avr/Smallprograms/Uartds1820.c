/*
 * dallas.c
 *
 * Created: 6.10.2014 19:27:34
 *  Author: mm
  
Project : DS1820_lampo.c
Hardware: PV-M32, (4 MHz), PV-EMO
Software: WinAVR-2000610 + AVRStudio 4.14
Date	: 04.06.2005 & 07042006 + 30.09.2007 + 18.10.07
25.08.2008
Authors	:
** DS1820 Funktiot by Jukka Pitk�nen
** GetTemp-korjaus, Olli-Pekka Korpela
** ds1820.h by Ilari Nummila
** sovitus Pentti Vahtera

Comments:
DS1820 l�mp�tila-anturi
ts. PD.0 ja lcd on PORTA

T�t� koodia saa k�ytt�� vapaasti, omalla vastuulla.
Parannusehdotukset -->> pentti.vahtera@microsalo.com
**********************************************************/
#define F_CPU 10000000UL
#include <avr/io.h>
#include <util/delay.h>

#define XTAL 10000000 // MCU:n kellotaajuus
#define BAUD 9600 // sarjaportin nopeus 9600 bps

#define DELAY 1041	
#define TAUSTAVALO 1<<0 // PC.0
void USART_Init(void);
void USART_Transmit(uint8_t data);
void USART_sendString(uint8_t * str);
void printDs(volatile uint16_t temp_anturista);
void USART_WRITE_UINT(uint16_t uInteger);
void wait(uint16_t time) {
	volatile uint16_t i;
	for(i=0;i<2000;i++)
	_delay_loop_2(time);
}
uint8_t merkki = 'A';
int main(void) {

	uint16_t temp_anturista = 0;
	uint16_t temp_anturista2 = 0;
	uint16_t temp_anturista = 0;
	USART_Init();
	while(1) {
		temp_anturista = GetTemp(&PORTD, &DDRD, &PIND, (1<<PD4));
		temp_anturista2 = GetTemp(&PORTD, &DDRD, &PIND, (1<<PD5));
		Tulosta(temp_anturista);
		USART_Transmit('\n');
		Tulosta(temp_anturista2);
		USART_Transmit('\n');
		wait(200);

	}
}
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
void USART_sendString(uint8_t * str) {
	for (int i = 0; *str != '\0'; i++) {
		while (!( UCSRA & (1<<UDRE)));
		UDR = *str;
		str++;
	}
	
}

void printDs(volatile uint16_t temp_anturista) {
	uint16_t temp_apu = 0;

	temp_apu = temp_anturista/16;
	// anturi palauttaa 9 bitti?, joista 9. bitti kertoo suunnan, ei huomioitu t?ss?
	// resoluutio on 0,5 astetta per bitti
	// l?mp? 0 C vastaa 0x00
	// l?mp? +125 C vastaa 0xFF = 255
	USART_WRITE_UINT(temp_apu);

	if(temp_anturista % 2)

	USART_sendString(",5 C ");

	else
	USART_sendString(",0 C ");
}

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
	//uint16_t test = 97;
	// Put data into buffer, sends the data
	UDR = data; // lähtevä merkki datarekisteriin
} 

void USART_WRITE_UINT(uint16_t uInteger) {
	uint8_t* pBuffer;
	uint8_t intBuffer [6];

	pBuffer    = &intBuffer[5];        // Point to buffer end
    *pBuffer    = 0;                // Terminate buffer with NULL
	while( uInteger /= 10 ) {
		*--pBuffer    = (uInteger % 10) + '0';
	}
	while ( *pBuffer ) {
		while (!( UCSRA & (1<<UDRE)));
        UDR =*pBuffer++;
	}

}