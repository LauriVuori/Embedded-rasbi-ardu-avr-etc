#include "timer.h"

void TIM2_IRQHandler(void) {
	TIM2->SR=0;			                //clear UIF
    // USART2_write('a');
    led_board_toggle();
}

void init_timer2_ISR(void) {
    // APB1 peripheral clock enable register (RCC_APB1ENR)

    RCC->APB1ENR |= BIT_SET(0);
    TIM2->PSC = 32-1;	                //32 000 000 MHz / 32 = 1 000 000 Hz
    TIM2->ARR = 1000-1;	                //1 000 000 Hz / 1000 = 1000 Hz ~ 1ms
    TIM2->CR1 = 1;			            //enable counter
    TIM2->DIER |= 1;		            //enable UIE, interrupt enable
    NVIC_EnableIRQ(TIM2_IRQn);
}


void init_timer1(void) {
    RCC->APB2ENR |= (1 << 11); 	        //TIM11EN: Timer 1 clock enable. p160
    // TIM1 prescaler
	TIM1->PSC = 32-1; 		            //32 000 000 MHz / 32 = 1 000 000 Hz. p435
	// TIM1 auto-reload register (TIM1_ARR) , will generate interrupt when this value is reached
    TIM1->ARR = 1000-1; 		        //TIM1 counter. 1 000 000 Hz / 1000 = 1000 Hz ~ 1ms. p435
    TIM1->CNT = 0;			            //counter start value = 0
}

// void delay_ms_timer1(unsigned long delay) {
// 	unsigned long i=0;
//     TIM1->CNT = 0;			            //counter start value = 0
//     TIM1->CR1 = 1;
//     while(i < delay) {
//         while(!((TIM1->SR)&1));         //Update interrupt flag. p427
//         i++;
//         TIM1->SR &= ~1; 	            //flag cleared. p427
//         TIM1->CNT = 0;	  	            //counter start value = 0
// 	}
//     TIM1->CR1=0;
// }


void delay_ms_timer1(unsigned long delay) {
	unsigned long i = 0;
    RCC->APB2ENR |= (1 << 11); 	//TIM11EN: Timer 1 clock enable. p160
    // TIM1 prescaler
	TIM1->PSC = 32-1; 		//32 000 000 MHz / 32 = 1 000 000 Hz. p435 
	// TIM1 auto-reload register (TIM1_ARR)
    TIM1->ARR = 1000-1; 		//TIM11 counter. 1 000 000 Hz / 1000 = 1000 Hz ~ 1ms. p435
    TIM1->CNT = 0;			//counter start value = 0
    // TIM1 counter (TIM1_CNT)
	TIM1->CR1 = 1; 			//TIM11 Counter enabled. p421
    while(i < delay) {
        while(!((TIM1->SR)&1)); //Update interrupt flag. p427
        i++;
        TIM1->SR &= ~1; 	//flag cleared. p427
        TIM1->CNT = 0;	  	//counter start value = 0
	}
    TIM1->CR1=0; 		//TIM1 Counter disabled. p421
}
