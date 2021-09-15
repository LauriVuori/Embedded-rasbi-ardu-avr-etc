#include "usart.h"
// FIX THIS
// void Usart2_write_uint(uint16_t uInteger) {
// 	uint8_t* pBuffer;
// 	uint8_t intBuffer [6];

// 	pBuffer    = &intBuffer[5];        // Point to buffer end
//     *pBuffer    = 0;                // Terminate buffer with NULL
// 	while( uInteger /= 10 ) {
// 		*--pBuffer    = (uInteger % 10) + '0';
// 	}
// 	while ( *pBuffer ) {
// 		while(!(USART2->ISR & (1 << 7))); 	// USART register map and reset values, TXe bit 7
//         USART2->TDR=*pBuffer++;
// 	}

// }


void USART2_Init(void) {
    // PA2 USART2_TX
    // PA3 USART2_RX
    // USART2 RCC_APB1ENR 17 bit clock enable
	RCC->APB1ENR |= (1 << 17);
    RCC->AHBENR |= (1 << 17); // enable PORT a clock
    // MODER = 10: Alternate function mode
    // PA2 and PA3
    GPIOA->MODER |= (1 << 5) | (1 << 7);
	GPIOA->AFR[0] = 0x000007700;	//Alterante mode

	USART2->BRR = 0xd05;	//9600 BAUD
    USART2->CR1 |= (1 << 0) | (1 << 2) | (1 << 3); // enable usart, enable tx, enable rx
}

void USART2_write(char data) {
	//wait while TX buffer is empty
    while(!(USART2->ISR & (1 << 7)));	// USART register map and reset values, TXe bit 7
        USART2->TDR=(data);		
}
// ..\src\functions\.././functions/usart.h:6:6: note: expected 'char *' but argument is of type 'uint8_t * {aka unsigned char *}'
//  void USART2_write_string(char data[]);

void USART2_write_string(char data[]) {
    for (int i = 0; data[i] != '\0'; i++) {
        //wait while TX buffer is empty
        while(!(USART2->ISR & (1 << 7))); // USART register map and reset values, TXe bit 7
        
        USART2->TDR=(data[i]);
    }
}


void USART2_read() {
	char data=0;
	//wait while RX buffer is data is ready to be read
	while(!(USART2->ISR & 0x0020)); 	//Bit 5 RXNE: Read data register not empty
		data=USART2->RDR;			//p739
    USART2_write_string("Received: ");
    USART2_write(data);
    USART2_write('\n');
}

