#include "pin_config.h"
// s.141
void init_port_a_clock(void) {
    RCC->AHBENR |= (1 << 17);
}
void init_port_b_clock(void) {
    // RCC_AHBENR_GPIOBEN ((uint32_t)0x00040000)
    // Bit 18 IOPBEN: I/O port B clock enable
    // RCC->AHBENR |= (RCC_AHBENR_GPIOBEN);
    RCC->AHBENR |= (1 << 18);
}

void init_port_c_clock(void) {
    // B1 USER: the user button is connected to the I/O PC13 (pin 2) of the STM32 
    // microcontroller.
    // PORT C 19 bit
    RCC->AHBENR |= (1 << 19);
}

void init_port_d_clock(void) {
    RCC->AHBENR |= (1 << 20);
}

void init_led_board_portb(void) {
	// initialize board led

    // RCC_AHBENR_GPIOBEN ((uint32_t)0x00040000)
    // Bit 18 IOPBEN: I/O port B clock enable
    // RCC->AHBENR |= (RCC_AHBENR_GPIOBEN);
    // RCC->AHBENR |= (1 << 18);
    init_port_b_clock();
    // MODER13 (26-27bits) pin 13
    // 01 output
    GPIOB->MODER |= (1 << 26);
}

void led_board_toggle(void) {
	// switch board led state on and off

    // ODR 13, pin 13, bit 13
    GPIOB->ODR ^= (1 << 13);
}

// void init_pa3_output(void) {
// 	// set port a pin 3 as output

//     // Bit 17 IOPAEN: I/O port A clock enable
//     RCC->AHBENR |= (1 << 17);
//     // pin 0 output
//     GPIOA->MODER |= (1 << 0);
// }

void init_pa0_output(void) {
	// set port a pin 3 as output
    // pin 0 output
    GPIOA->MODER |= (1 << 0) | (0 << 1);
} 
void toggle_pa0(void) {
    GPIOA->ODR ^=  (1<<0);
}
// void led_pa3_toggle(void) {
// 	// toggle port a pin 3 state

//     // toggle ODR 0
//     GPIOA->ODR ^=  (1<<0);
// }

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

uint8_t board_button_state(void) {
	//if PC13 is high state (button released)

    if(~GPIOC->IDR & (1 << 13)) {
        //delay_Ms(20);
        // GPIOA->BSRR=0x200000;	//turn led off (PA5=low state)
    	// led_board_toggle();
        // board_led_toggle_bsrr();
        // USART2_write('a');
        return 1;
    }
    return 0;
}
// void delay_Ms(int delay);
// void delay_Ms(int delay) {
// 	int i = 0;
// 	for(; delay > 0; delay--) {
// 		for(i = 0;i < 2460; i++); //measured with oscilloscope
//     }
// }
