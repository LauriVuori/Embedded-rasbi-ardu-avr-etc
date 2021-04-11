#define ROWMAX 2
#define COLMAX 16


void printFlashToLcd(const __flash uint8_t * text);

void USART_Init(void);
void USART_sendString(uint8_t * str);
void wait(uint16_t time);
void drawing(uint8_t button, uint8_t * currentRow, uint8_t * currentCol);
unsigned char luenappi();
unsigned char test();
void printBinary(uint8_t number, uint8_t * currentRow, uint8_t * currentCol);
void printMenu(void);