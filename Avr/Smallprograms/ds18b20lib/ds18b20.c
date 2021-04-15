
// ds18b20Temp(&PORTD, &DDRD, &PIND, ( 1 << PD5 ));
#include <avr/io.h>
#include <util/delay.h>
#include "ds1820.h"

int16_t GetTemp(uint8_t *port, uint8_t *datadirection, uint8_t *portin, uint8_t pinbit) {
    int16_t data1 = 0;  // l?mp?tilatieto
	int16_t data2 = 0;  // onko pos vai neg, 0=+ ja 1=-
    OwReset(port, datadirection, portin, pinbit);

	
    OwWriteByte(0xCC, port, datadirection, portin, pinbit);  


	OwWriteByte(0x44, port, datadirection, portin, pinbit);

	_delay_loop_2(DELAY45);

    OwReset(port, datadirection, portin, pinbit);

	OwWriteByte(0xCC, port, datadirection, portin, pinbit); 


	OwWriteByte(0xBE, port, datadirection, portin, pinbit); 

	data1 = OwReadByte(port, datadirection, portin, pinbit);


	//printBinary(lsb);
	//LCD_SetCursorXY(0,1);
	//LCD_WriteUINT(lsb);
	data2 = OwReadByte(port, datadirection, portin, pinbit);
	// miss? on tieto l?mp?tilan etumerkist?

	//printBinary(msb);
	//LCD_SetCursorXY(0,1);
	//printBinary(msb);
	//LCD_WriteUINT(msb);
    OwReset(port, datadirection, portin, pinbit);
	//OwReset();
	// anna reset-signaali, jolla DS1820 lopettaa bittien l?hett?misen

	//lsb |= (msb << 8);
	data2 <<= 8;
	//printBinary(lsb);
	data1 |= data2;
/*
	LCD_SetCursorXY(0,1);
	printBinary(msb);
	LCD_WriteUINT(msb);*/
	return data1; // palautetaan p??ohjelmaan

}
uint8_t OwReset(uint8_t *port, uint8_t *datadirection, uint8_t *portin, uint8_t pinbit) {
	uint8_t temp=0;

	*datadirection |= pinbit;   // B-portin 4-bitin suunta ulos
	// DS1820 on PORTB.4
	*port &= ~(pinbit);  // B-portin 4-bitti maihin

	_delay_loop_2(DELAY500); // 500 us viive
	// jos bitti? pidet??n maassa n. 500us,
	// DS1820 ymm?rt?? sen reset-signaaliksi

	// muutetaan portin suunta takaisin sis??np?in
	*datadirection &= ~pinbit;
	*port |= pinbit;  // vedet??n linja 'yl?s'

	_delay_loop_2(DELAY60); // 60 us viive
	// DS1820 vastaa reset-signaaliin n. 60us p??st?

	temp = *portin & pinbit; // luetaan DS1820:n vastaus
	// jos linja on maassa, on DS1820 ymm?rt?nyt signaalin
	// jos taas pinni on 1,  DS1820 ei ole vastannut signaaliin

	_delay_loop_2(DELAY400); // 400 us viive
	// odotetaan viel? n. 400us, jotta resetointi on varmasti loppunut

	return temp;
}

uint8_t OwReadByte(uint8_t *port, uint8_t *datadirection, uint8_t *portin, uint8_t pinbit) {
	uint8_t data = 0;  // muuttuja, johon luettu arvo tallennetaan
	uint8_t w = 0;     // silmukkalaskuri

	// luetaan v?hiten merkitsev?t bitit l?mp?tila-rekisterist?
	for(w = 0; w <= 7; w++)
	{
		data >>= 1;    // siirret??n bittej? joka kierroksella oikealle
		*datadirection |= pinbit;  // B-portin 4-bitin suunta ulos

		*port &= ~(pinbit); // 4. linja maihin

		_delay_loop_2(DELAY50); // 50 us viive
		// luku signaalissa pidet??n linjaa maissa n. 50us

		// k??nnet??n data-linjan suunta sis??n
		*datadirection &= ~pinbit;
		*port |= pinbit;    // ja vedet??n se yl?s

		_delay_loop_2(DELAY45); // 45 us viive
		// jos DS1820 l?hett?? 0:n, se ei p??st? linjaa yl?s
		// vaan pit?? sit? viel? n.45us maissa

		if(*portin & pinbit)   // testataan linjan tila
		{                // jos se on ylh??ll?, on luettava bitti 1
			data |= 0x80;
		}

		else     // jos edellinen ehto ei toteutunut,
		// pit?? DS1820 linjaa maissa ja bitti on silloin 0
		{
			data &= 0x7F;
		}
		
		_delay_loop_2(DELAY60);
		// pidet??n pieni tauko ennen seuraavaa lukukertaa
	}
	return data;  // palautetaan luettu data
}

// OwWriteByte() funktiolla annetaan DS1820:lle komentoja, **********
// parametrina funktio saa suoritettavan k?skyn
void OwWriteByte(uint8_t data, uint8_t *port, uint8_t *datadirection, uint8_t *portin, uint8_t pinbit)
{
	uint8_t e = 0;

	for(e = 0; e < 8; e++)
	// silmukassa annetaan DS1820:lle komennosta bitti kerrallaan
	// aloittaen v?hiten merkitsev?st? bitist?
	{
		if(data & 0x01)  // jos v?hiten merkitsev? bitti on 1, ehto toteutuu
		{
			*datadirection |= pinbit;
			*port &= ~(pinbit);  // kun kirjoitetaan 1, linja maihin n. 5us
			_delay_loop_2(1); // ja odotetaan n. 60us
			*datadirection &= ~(pinbit);
			*port |= pinbit;
			_delay_loop_2(DELAY60);
		}

		else     // jos kirjoitettava bitti on 0
		{
			*datadirection |= pinbit;
			// kun kirjoitetaan 0, linja maihin n. 60us
			*port &= ~(pinbit);    // ja odotetaan n. 5us
			_delay_loop_2(DELAY60);
			*datadirection &= ~(pinbit);
			*port |= (pinbit);
			_delay_loop_2(1);
		}
		data >>= 1;  // siirryt??n k?skyss? seuraavaan bittiin
	}
}