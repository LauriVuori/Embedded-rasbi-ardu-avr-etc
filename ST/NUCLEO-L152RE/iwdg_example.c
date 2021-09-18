// In STM32 microcontrollers the independent watchdog (IWDG) is a 12-bit down-counter timer 
// clocked by its own dedicated low-speed clock (LSI) and thus stays active even if the main clock fails.

// The independent watchdog (IWDG) is clocked by its own dedicated low-speed clock (LSI clock frequency is 
// around 40 kHz (between 30 kHz and 50 kHz))  
// and thus stays active even if the main clock fails.
// The IWDG is best suited for applications that require the watchdog to run as a totally 
// independent process outside the main application, but have lower timing accuracy 
// constraints. (ref. 723)


/* Includes */
#include <stddef.h>
#include "stm32l1xx.h"
#include "nucleo152start.h"
#include <stdio.h>
#include <stdlib.h>

/* Private typedef */
/* Private define  */

// IWDG->KR must be written by software at regular intervals with the key value 0xAAAA, 
// otherwise the watchdog generates a reset when the counter reaches 0
#define NOTIFY_IWDG 0xAAAA

// Writing the key value 0xCCCC starts the watchdog (except if the hardware watchdog option 
// is selected)
#define ENABLE_IWDG 0xCCCC

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */
void USART2_Init(void);
void USART2_write(char data);
void delay_Ms(int delay);
void refresh_IWDG(void);
void iwdg_init(void);
void USART2_write_string(char data[]);
void init_push_button(void);
void init_led_board_portb(void);
void led_board_toggle();


/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
	/* Configure the system clock to 32 MHz and update SystemCoreClock */
	SetSysClock();
	SystemCoreClockUpdate();
	/*Init functions*/
	USART2_Init();
	init_push_button();
	init_led_board_portb();
	iwdg_init();
	/* TODO - Add your application code here */

	// Just to show that system is booting
	USART2_write_string("SYSTEM BOOT\n\r");
	while(1) {
		// stay in while loop when button is pressed, otherwise we will continue
		// press button and wait approx 2. seconds to so watchdog will reset MCU
		while(~GPIOC->IDR & 0x2000);
		// Just to show program is running
		USART2_write_string("test\n\r");
		led_board_toggle();
		// To refresh timer. There maybe more reliable ways to call refresh like timer.
		refresh_IWDG();
		delay_Ms(1000);
	}
  	return 0;
}

void refresh_IWDG(void) {
	// use this function to refresh IWDG timer. Desired value is already defined #define NOTIFY_IWDG 0xAAAA
    IWDG->KR = NOTIFY_IWDG;
}

void led_board_toggle(void) {
	// switch board led state on and off by calling this function
    GPIOA->ODR ^= (1 << 5);
}

void init_led_board_portb(void) {
	// RCC->AHBENR|=0x00000001;   Usart enables GPIOA clock already		
    GPIOA->MODER |= (1 << 10);
}

void iwdg_init(void) {
    // initialize intependet independent watchdog

    // IWDG Key register
    // These bits must be written by software at regular intervals with the key value 0xAAAA, 
    // otherwise the watchdog generates a reset when the counter reaches 0
    // Use function refresh_IWDG
    IWDG->KR = ENABLE_IWDG;
    IWDG->SR = 0x0;                     	//Values can be only updadet when all bits are 0
    
    // Write access to IWDG prescaler register (IWDG_PR), IWDG reload register (IWDG_RLR)
    // and IWDG window register (IWDG_WINR) is protected. To modify them, the user must first 
    // write the code 0x0000 5555 in the IWDG key register (IWDG_KR).
    IWDG->KR = 0x00005555;                  // Remove protection

    // IWDG prescaler register (IWDG_PR)
    // IWDG->PR = 0x0;                     // reset prescaler
    IWDG->PR = 0x7;                        // PR[2:0], bits 111: divider /256. 40000 hz / 256 = 156
    IWDG->RLR = 300;                     // approx 2 sec 


    // DBG_IWDG_STOP: Debug independent watchdog stopped when core is halted, 12th bit
    // 0: The independent watchdog counter clock continues even if the core is halted
    // 1: The independent watchdog counter clock is stopped when the core is halted
    // Debug MCU APB1 freeze register (DBGMCU_APB1_FZ)
    DBGMCU->APB1FZ |= (1 << 12);
}

void USART2_write_string(char data[]) {
    for (int i = 0; data[i] != '\0'; i++) {
        //wait while TX buffer is empty
    	while(!(USART2->SR&0x0080)){} // USART register map and reset values, TXe bit 7
		USART2->DR=(data[i]);

    }
}

void init_push_button(void) {
	RCC->AHBENR|=0x4; //GPIOC enable. p154
	GPIOC->MODER&=~0xC000000; //PC13 configured to input, C=1100. p184
}

void USART2_Init(void)
{
	RCC->APB1ENR|=0x00020000; 	//set bit 17 (USART2 EN)
	RCC->AHBENR|=0x00000001; 	//enable GPIOA port clock bit 0 (GPIOA EN)
	GPIOA->AFR[0]=0x00000700;	//GPIOx_AFRL p.188,AF7 p.177
	GPIOA->AFR[0]|=0x00007000;	//GPIOx_AFRL p.188,AF7 p.177
	GPIOA->MODER|=0x00000020; 	//MODER2=PA2(TX) to mode 10=alternate function mode. p184
	GPIOA->MODER|=0x00000080; 	//MODER2=PA3(RX) to mode 10=alternate function mode. p184

	USART2->BRR = 0x00000D05;	//9600 BAUD and crystal 32MHz. p710, D05
	USART2->CR1 = 0x00000008;	//TE bit. p739-740. Enable transmit
	USART2->CR1 |= 0x00000004;	//RE bit. p739-740. Enable receiver
	USART2->CR1 |= 0x00002000;	//UE bit. p739-740. Uart enable
}

void USART2_write(char data)
{
	//wait while TX buffer is empty
	while(!(USART2->SR&0x0080)){} 	//6. p736-737
		USART2->DR=(data);		//p739
}

void delay_Ms(int delay)
{
	int i=0;
	for(; delay>0;delay--)
		for(i=0;i<2460;i++); //measured with oscilloscope
}
