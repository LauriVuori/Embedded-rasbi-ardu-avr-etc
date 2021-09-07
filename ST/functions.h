void led_board_init(void);
void led_board_toggle(void);
void init_pa3_output(void); 
void led_pa3_toggle(void);
void init_board_button1(void);
void delay_Ms(int delay);
void board_led_toggle_bsrr(void);
void board_button_state(void);
void USART2_Init(void);
void USART2_write(char data);
void USART2_read();




void led_board_init(void) {
	// initialize board led

    // RCC_AHBENR_GPIOBEN ((uint32_t)0x00040000)
    // Bit 18 IOPBEN: I/O port B clock enable
    // RCC->AHBENR |= (RCC_AHBENR_GPIOBEN);
    RCC->AHBENR |= (1 << 18);
    // MODER13 (26-27bits) pin 13
    // 01 output
    GPIOB->MODER |= (1 << 26);
}

void led_board_toggle(void) {
	// switch board led state on and off

    // ODR 13, pin 13, bit 13
    GPIOB->ODR ^= (1 << 13);
}

void init_pa3_output(void) {
	// set port a pin 3 as output

    // Bit 17 IOPAEN: I/O port A clock enable
    RCC->AHBENR |= (1 << 17);
    // pin 0 output
    GPIOA->MODER |= (1 << 0);
} 

void led_pa3_toggle(void) {
	// toggle port a pin 3 state

    // toggle ODR 0
    GPIOA->ODR ^=  (1<<0);
}

void board_led_toggle_bsrr(void) {
	  GPIOB->BSRRL |= (1 << 13);
	  delay_Ms(1000);
	  GPIOB->BSRRH |= (1 << 13);
	  delay_Ms(1000);

}

void init_board_button1(void) {
    // B1 USER: the user button is connected to the I/O PC13 (pin 2) of the STM32 
    // microcontroller.
    // PORT C 19 bit
    RCC->AHBENR |= (1 << 19);
    // 01 output
    GPIOC->MODER |= (0 << 26) | (0 << 27);

}

void board_button_state(void) {
	//if PC13 is high state (button released)

    if(~GPIOC->IDR & (1 << 13)) {
        delay_Ms(20);
        // GPIOA->BSRR=0x200000;	//turn led off (PA5=low state)
    	// led_board_toggle();
        // board_led_toggle_bsrr();
        USART2_write('a');
    }
}

void delay_Ms(int delay) {
	int i = 0;
	for(; delay > 0; delay--) {
		for(i = 0;i < 2460; i++); //measured with oscilloscope
    }
}


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


