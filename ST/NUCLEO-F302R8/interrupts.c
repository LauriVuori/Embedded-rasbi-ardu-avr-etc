#include "interrupts.h"

void init_interrupts(void) {
    __disable_irq();
    // NVIC_EnableIRQ(USART2_IRQn); 	//enable interrupt in NVIC
	__enable_irq();					//global enable IRQs, M3_Generic_User_Guide p135
}