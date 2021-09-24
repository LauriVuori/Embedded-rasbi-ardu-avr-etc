// The real-time clock (RTC) is an independent BCD timer/counter. The RTC provides a timeof-day 
// clock/calendar, two programmable alarm interrupts, and a periodic programmable 
// wakeup flag with interrupt capability. The RTC also includes an automatic wakeup unit to 
// manage low-power modes.
// Two 32-bit registers contain the seconds, minutes, hours (12- or 24-hour format), day (day 
// of week), date (day of month), month, and year, expressed in binary coded decimal format 
// (BCD). The sub-seconds value is also available in binary format (in Cat.2, Cat.3, Cat.4, 
// Cat.5 and Cat.6 devices only).
// Compensations for 28-, 29- (leap year), 30-, and 31-day months are performed 
// automatically. Daylight saving time compensation can also be performed. 
// Additional 32-bit registers contain the programmable alarm subseconds (in Cat.2, Cat.3, 
// Cat.4, Cat.5 and Cat.6 devices only), seconds, minutes, hours, day, and date.
// A digital calibration feature is available to compensate for any deviation in crystal oscillator 
// accuracy.
// After power-on reset, all RTC registers are protected against possible parasitic write 
// accesses.
// As long as the supply voltage remains in the operating range, the RTC never stops, 
// regardless of the device status (Run mode, low-power mode or under reset).



/* Includes */
#include <stddef.h>
#include "stm32l1xx.h"
#include "nucleo152start.h"
#include <stdio.h>
#include <stdlib.h>

/* Private typedef */
/* Private define  */


/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */
void USART2_Init(void);
void USART2_write(char data);
void delay_Ms(int delay);
void USART2_write_string(char data[]);
void init_push_button(void);
void init_led_board_portb(void);
void led_board_toggle();
void init_RTC_calendar(void);
void init_LSE_clock(void);

void uint8_to_char_array(uint8_t uInteger, uint8_t * dest_array, uint8_t * counter);
void set_time(char new_time[]);
void set_date(char new_date[]);
void get_time_to_buffer(char time_buf[]);
void get_date_to_buffer(char date_buf[], char current_thousands_year[]);

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
// In current RTC implementation it is possible to just set 20 last two numbers in years

int main(void) {
	/* Configure the system clock to 32 MHz and update SystemCoreClock */
	SetSysClock();
	SystemCoreClockUpdate();
	/*Init functions*/
	USART2_Init();
	//init_push_button();
	init_led_board_portb();

	init_RTC_calendar();
	/* TODO - Add your application code here */

	// Just to show that system is booting
	USART2_write_string("SYSTEM BOOT\n\r");

	char time_buffer[90];
	char date_buffer[90];

	char current_thousand_year[3] = "20";
	while(1) {
		get_time_to_buffer(time_buffer);
		get_date_to_buffer(date_buffer, current_thousand_year);
		USART2_write_string("Time: ");
		USART2_write_string(time_buffer);
		USART2_write_string("\n\r");
		USART2_write_string("Date: ");
		USART2_write_string(date_buffer);
		USART2_write_string("\n\r");
		led_board_toggle();

		delay_Ms(1000);
	}
  	return 0;
}

void get_date_to_buffer(char date_buf[], char current_thousands_year[]) {
	// Variable to every unit just to clarify different units
	uint8_t days = 0;
	uint8_t days_tens = 0;

	uint8_t months = 0;
	uint8_t months_tens = 0;

	uint8_t years = 0;
	uint8_t years_tens = 0;

	uint8_t counter = 0;
		
	// Bits 3:0 DU[3:0]: Date units in BCD format
	days = RTC->DR & 0xf;
	// Bits 5:4 DT[1:0]: Date tens in BCD format
	days_tens = (RTC->DR & 0x30) >> 4;
	// Bit 12 MT: Month tens in BCD format
	months_tens = (RTC->DR & 0x1000) >> 12;
	// Bits 11:8 MU: Month units in BCD format
	months = (RTC->DR & 0xf00) >> 8;
	// Bits 19:16 YU[3:0]: Year units in BCD format
	years = (RTC->DR & 0xF0000) >> 16;
	// Bits 23:20 YT[3:0]: Year tens in BCD format
	years_tens = (RTC->DR & 0xF00000) >> 20;

	//24.			days
	uint8_to_char_array(days_tens, &date_buf[counter], &counter);
	uint8_to_char_array(days, &date_buf[counter], &counter);
	date_buf[counter] = '.';
	counter++;

	//24.09			months
	uint8_to_char_array(months_tens, &date_buf[counter], &counter);
	uint8_to_char_array(months, &date_buf[counter], &counter);
	date_buf[counter] = '.';
	counter++;

	//24.09.2021	years
	date_buf[counter] = current_thousands_year[0];
	counter++;
	
	date_buf[counter] = current_thousands_year[1];
	counter++;
	uint8_to_char_array(years_tens, &date_buf[counter], &counter);
	uint8_to_char_array(years, &date_buf[counter], &counter);
}

void get_time_to_buffer(char time_buf[]) {
	// Variable to every unit just to clarify different units
	uint8_t seconds = 0;
	uint8_t seconds_tens = 0;

	uint8_t minutes = 0;
	uint8_t minutes_tens = 0;

	uint8_t hours = 0;
	uint8_t hours_tens = 0;

	uint8_t counter = 0;

	// Bits 3:0 SU[3:0]: Second units in BCD format
	seconds = RTC->TR & 0xF;
	// Bits 6:4 ST[2:0]: Second tens in BCD format
	seconds_tens = (RTC->TR & 0x70) >> 4;
	// Bit 11:8 MNU[3:0]: Minute units in BCD format
	minutes = (RTC->TR & 0xF00) >> 8;
	// Bits 14:12 MNT[2:0]: Minute tens in BCD format
	minutes_tens = (RTC->TR & 0x7000) >> 12;
	// Bits 19:16 HU[3:0]: Hour units in BCD format
	hours = (RTC->TR & 0xF0000) >> 16;
	// Bits 21:20 HT[1:0]: Hour tens in BCD format
	hours_tens = (RTC->TR & 0x300000) >> 20;
	//14:			hours
	uint8_to_char_array(hours_tens, &time_buf[counter], &counter);
	uint8_to_char_array(hours, &time_buf[counter], &counter);
	time_buf[counter] = ':';
	counter++;
	//14:55			minutes
	uint8_to_char_array(minutes_tens, &time_buf[counter], &counter);
	uint8_to_char_array(minutes, &time_buf[counter], &counter);
	time_buf[counter] = ':';
	counter++;
	//14:55:25		seconds
	uint8_to_char_array(seconds_tens, &time_buf[counter], &counter);
	uint8_to_char_array(seconds, &time_buf[counter], &counter);
}

void set_date(char new_date[]) {
	// Bits 31-24 Reserved
	// Bits 23:20 YT[3:0]: Year tens in BCD format
	// Bits 19:16 YU[3:0]: Year units in BCD format
	// Bits 15:13 WDU[2:0]: Week day units
	// 000: forbidden
	// 001: Monday
	// ...
	// 111: Sunday
	// Bit 12 MT: Month tens in BCD format
	// Bits 11:8 MU: Month units in BCD format
	// Bits 7:6 Reserved, must be kept at reset value.
	// Bits 5:4 DT[1:0]: Date tens in BCD format
	// Bits 3:0 DU[3:0]: Date units in BCD format
	// "24.09.2021"
	uint32_t temp = 0;
    temp |= new_date[1]-'0';
	temp |= new_date[0]-'0' << 4;
    temp |= new_date[3]-'0' << 12;
    temp |= (new_date[4]-'0' << 8);
    temp |= (new_date[8]-'0' << 20);
	temp |= (new_date[9]-'0' << 16);

	RTC->DR = temp;
}

void set_time(char new_time[]) {
	// seconds = RTC->TR & 0xF;
	// // Bits 6:4 ST[2:0]: Second tens in BCD format
	// seconds_tens = (RTC->TR & 0x70) >> 4;
	// // Bit 11:8 MNU[3:0]: Minute units in BCD format
	// minutes = (RTC->TR & 0xF00) >> 8;
	// // Bits 14:12 MNT[2:0]: Minute tens in BCD format
	// minutes_tens = (RTC->TR & 0x7000) >> 12;
	// // Bits 19:16 HU[3:0]: Hour units in BCD format
	// hours = (RTC->TR & 0xF0000) >> 16;
	// // Bits 21:20 HT[1:0]: Hour tens in BCD format
	// hours_tens = (RTC->TR & 0x300000) >> 20;

	uint32_t temp = 0;
	// "15:51:00"
	temp |= new_time[7]-'0';
	temp |= new_time[6]-'0' << 4;
	temp |= new_time[4]-'0' << 8;
	temp |= new_time[3]-'0' << 12;
	temp |= new_time[1]-'0' << 16;
	temp |= new_time[0]-'0' << 20;
	
	RTC->TR = temp; 					//set new time

}

// Control/status register (RCC_CSR)
// Setting LSE
void init_LSE_clock(void) {

	// Bit 8 LSEON: External low-speed oscillator enable
	// This bit is set and cleared by software.
	// It is reset by setting the RTCRST bit or by a POR. 
	// 0: LSE oscillator OFF
	// 1:LSE oscillator ON
	RCC->CSR |= (1 << 8); // LSE oscillator on

	// Bit 9 LSERDY: External low-speed oscillator ready
	// This bit is set and cleared by hardware to indicate when the LSE oscillator is stable. After the 
	// LSEON bit is cleared, LSERDY goes low after 6 LSE oscillator clock cycles.
	// It is reset by setting the RTCRST bit or by a POR. 
	// 0: External 32 kHz oscillator not ready
	// 1: External 32 kHz oscillator ready
	while (~RCC->CSR & (1 << 9)); // wait untill oscillator is ready

}

void init_RTC_calendar(void) {


	// Bit 22 RTCEN: RTC clock enable
	// This bit is set and cleared by software.
	// It is reset by setting the RTCRST bit or by a POR. 
	// 0: RTC clock disabled
	// 1: RTC clock enabled


	// __disable_irq();
	// RTC date register (RTC_DR)

	// 1. set DPB bit in PWR_CR register
	// PWR power control register (PWR_CR)
	// Bit 8 DBP: Disable backup write protection
	// In reset state, the RTC, RTC backup registers and RCC CSR register are protected against 
	// parasitic write access. This bit must be set to enable write access to these registers.
	// 0: Access to RTC, RTC Backup and RCC CSR registers disabled
	// 1: Access to RTC, RTC Backup and RCC CSR registers enabled
	PWR->CR |= (1 << 8); 				// Set DBP to allow writing
	RCC->CSR |= (1 << 23); 				// Reset RTC pheripheral, clock source, etc..
	while(RCC->CSR & (1 << 23)){
		RCC->CSR &= ~(1 << 23);
	}
	init_LSE_clock();

	// Bits 17:16 RTCSEL[1:0]: RTC and LCD clock source selection
	// These bits are set by software to select the clock source for the RTC. 
	// Once the RTC and LCD clock source has been selected it cannot be switched until RTCRST 
	// is set or a Power On Reset occurred. The only exception is if the LSE oscillator clock was 
	// selected, if the LSE clock stops and it is detected by the CSS, in that case the clock can be 
	// switched.
	// 00: No clock
	// 01: LSE oscillator clock used as RTC/LCD clock
	// 10: LSI oscillator clock used as RTC/LCD clock
	// 11: HSE oscillator clock divided by a programmable prescaler (selection through the 
	// RTCPRE[1:0] bits in the RCC clock control register (RCC_CR)) used as the RTC/LCD clock

	//Clear oscillator desicion
	
	//RCC->CSR &= ~((1 << 17) | (1 << 16));
	RCC->CSR |= (1 << 16); // LSE clock source
	RCC->CSR |= (1 << 22); //enable RTC

	// Bits 30:29 RTCPRE[1:0] RTC/LCD prescaler
	// These bits are set and reset by software to obtain a 1 MHz clock from HSE. This prescaler 
	// cannot be modified if HSE is enabled (HSEON = 1).
	// These bits are reset by power on reset, they keep their value after system reset.
	// 00: HSE is divided by 2 for RTC/LCD clock
	// 01: HSE is divided by 4 for RTC/LCD clock
	// 10: HSE is divided by 8 for RTC/LCD clock
	// 11: HSE is divided by 16 for RTC/LCD clockw
	// RCC->CR |= (1 << 30) | (1 << 29);
	

	// 2. Disable the RTC registers Write protection. Write "0xCA" and then "0x53" to RTC_WPR register.
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	// 1. Set INIT bit to 1 in the RTC_ISR register to enter initialization mode. In this mode, the 
	// calendar counter is stopped and its value can be updated.

	// Bit 7 INIT: Initialization mode
	// 0: Free running mode
	// 1: Initialization mode used to program time and date register (RTC_TR and RTC_DR), and 
	// prescaler register (RTC_PRER). Counters are stopped and start counting from the new 
	// value when INIT is reset.

	RTC->ISR |= (1 << 7);


	// 2. Poll INITF bit of in the RTC_ISR register. The initialization phase mode is entered when 
	// INITF is set to 1. It takes from 1 to 2 RTCCLK clock cycles (due to clock 
	// synchronization). 

	// Bit 6 INITF: Initialization flag
	// When this bit is set to 1, the RTC is in initialization state, and the time, date and prescaler 
	// registers can be updated.
	// 0: Calendar registers update is not allowed
	// 1: Calendar registers update is allowed.

	while (~RTC->ISR & (1 << 6)); 		// Wait untill init flag is on

	// RTC_PRER register: Write first the synchronous value and then write the asynchronous
	//By default, the RTC_PRER prescalers register is initialized to provide 1Hz to the Calendar unit when RTCCLK = 32768Hz
	//RTC->PRER = 32768-1;
	
	// Load time and date values in the shadow registers Set RTC_TR and RTC_DR register
	
	// 20.6.1 RTC time register (RTC_TR)
	// Bit 22 PM: AM/PM notation
	// 0: AM or 24-hour format
	// 1: PM
	// Bits 21:20 HT[1:0]: Hour tens in BCD format
	// Bits 19:16 HU[3:0]: Hour units in BCD format
	// Bit 15 Reserved, must be kept at reset value.
	// Bits 14:12 MNT[2:0]: Minute tens in BCD format
	// Bit 11:8 MNU[3:0]: Minute units in BCD format
	// Bit 7 Reserved, must be kept at reset value.
	// Bits 6:4 ST[2:0]: Second tens in BCD format
	// Bits 3:0 SU[3:0]: Second units in BCD format

	set_time("15:53:00");
	set_date("24.09.2021");
	// RTC->TR = 0x111115;
	// RTC->DR = 0x00002101;
	// delay_Ms(1000);

	// Bit 10 DBG_RTC_STOP: Debug RTC stopped when core is halted
	// 0: The clock of the RTC counter is fed even if the core is halted
	// 1: The clock of the RTC counter is stopped when the core is halted
	// Note: This bit is available only in Cat.2, Cat.3, Cat.4, Cat.5 and Cat.6 devices
	// DBGMCU->APB1FZ |= (1 << 10);		//Freeze RTC while debugging
	/*******************/
	// Turn of init mode
	RTC->ISR &= ~(1 << 7);
	while (RTC->ISR & (1 << 6));

	// Turn on RTC register write protection
	RTC->WPR = 0xFF;
	// turn on backup write protection
	PWR->CR &= ~(1 << 8);
	// __enable_irq();
}



void led_board_toggle(void) {
	// switch board led state on and off by calling this function
    GPIOA->ODR ^= (1 << 5);
}

void init_led_board_portb(void) {
	// RCC->AHBENR|=0x00000001;   Usart enables GPIOA clock already		
    GPIOA->MODER |= (1 << 10);
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

void uint8_to_char_array(uint8_t uInteger, uint8_t * dest_array, uint8_t * counter) {
    // needs atleast [6] array
	uint8_t* ptr_to_buffer;
	uint8_t int_buffer [5];

	ptr_to_buffer = &int_buffer[4];        // Point to buffer end
    *ptr_to_buffer = 0;
	do {
        // make characters, (uInteger % 10) = 5, 5 + '0' = 53=='5'
        *--ptr_to_buffer = (uInteger % 10) + '0';
    }while (uInteger /= 10 );
	while (*ptr_to_buffer) {
        *dest_array = *ptr_to_buffer;
        dest_array++;
        ptr_to_buffer++;
		*counter += 1;
	}
    // end char
    *dest_array = '\0';
}
