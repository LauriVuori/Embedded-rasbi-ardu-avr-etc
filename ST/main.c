#include "main.h"

/** @addtogroup STM32F3xx_HAL_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

void led_board_init(void);
void led_board_toggle(void);
void init_pa3_output(void); 
void led_pa3_toggle(void);
void init_board_button1(void);
void delay_Ms(int delay);

int main(void) {
    //HAL_Init();
    /* Configure the system clock to 64 MHz */
    SystemClock_Config();

    led_board_init();
    init_pa3_output();
    init_board_button1();
    /* -3- Toggle IOs in an infinite loop */
    while (1) {
        // led_board_toggle();
        // led_pa3_toggle();
        board_button_state();
        HAL_Delay(100);
    }
}


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
    	led_board_toggle();
    }
}

void delay_Ms(int delay) {
	int i = 0;
	for(; delay > 0; delay--) {
		for(i = 0;i < 2460; i++); //measured with oscilloscope
    }
}
































/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 64000000
  *            HCLK(Hz)                       = 64000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 2
  *            APB2 Prescaler                 = 1
  *            PLLMUL                         = RCC_PLL_MUL16 (16)
  *            Flash Latency(WS)              = 2
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  
  /* HSI Oscillator already ON after system reset, activate PLL with HSI as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct)!= HAL_OK)
  {
    Error_Handler();
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2)!= HAL_OK)
  {
    Error_Handler();
  }
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
static void Error_Handler(void)
{
  /* User may add here some code to deal with this error */
  while(1)
  {
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
