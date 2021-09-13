// board NUCLEO-F302R8
// reference manual s.723
// https://elektroniikka.narkive.fi/JhXgbmFh/riippumaton-vahtikoira-iwdg-vai-ikkunavartija-wwdg
// In STM32 microcontrollers the independent watchdog (IWDG) is a 12-bit down-counter timer 
// clocked by its own dedicated low-speed clock (LSI) and thus stays active even if the main clock fails.

// The independent watchdog (IWDG) is clocked by its own dedicated low-speed clock (LSI) 
// and thus stays active even if the main clock fails.
// The IWDG is best suited for applications that require the watchdog to run as a totally 
// independent process outside the main application, but have lower timing accuracy 
// constraints. (ref. 723)
void iwdg_init(void) {
    // initialize intependet independent watchdog
    
    
}

void MX_IWDG_Init(void) {

  /* USER CODE BEGIN IWDG_Init 0 */

  /* USER CODE END IWDG_Init 0 */

  /* USER CODE BEGIN IWDG_Init 1 */

  /* USER CODE END IWDG_Init 1 */
  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_4;
  hiwdg.Init.Window = 4095;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN IWDG_Init 2 */

  /* USER CODE END IWDG_Init 2 */

}
/**
  * @brief  Initialize the IWDG according to the specified parameters in the
  *         IWDG_InitTypeDef and start watchdog. Before exiting function,
  *         watchdog is refreshed in order to have correct time base.
  * @param  hiwdg  pointer to a IWDG_HandleTypeDef structure that contains
  *                the configuration information for the specified IWDG module.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_IWDG_Init(IWDG_HandleTypeDef *hiwdg)
{
  uint32_t tickstart;

  /* Check the IWDG handle allocation */
  if (hiwdg == NULL)
  {
    return HAL_ERROR;
  }

  /* Check the parameters */
  assert_param(IS_IWDG_ALL_INSTANCE(hiwdg->Instance));
  assert_param(IS_IWDG_PRESCALER(hiwdg->Init.Prescaler));
  assert_param(IS_IWDG_RELOAD(hiwdg->Init.Reload));
  assert_param(IS_IWDG_WINDOW(hiwdg->Init.Window));

  /* Enable IWDG. LSI is turned on automatically */
  __HAL_IWDG_START(hiwdg);

  /* Enable write access to IWDG_PR, IWDG_RLR and IWDG_WINR registers by writing
  0x5555 in KR */
  IWDG_ENABLE_WRITE_ACCESS(hiwdg);

  /* Write to IWDG registers the Prescaler & Reload values to work with */
  hiwdg->Instance->PR = hiwdg->Init.Prescaler;
  hiwdg->Instance->RLR = hiwdg->Init.Reload;

  /* Check pending flag, if previous update not done, return timeout */
  tickstart = HAL_GetTick();

  /* Wait for register to be updated */
  while ((hiwdg->Instance->SR & IWDG_KERNEL_UPDATE_FLAGS) != 0x00u)
  {
    if ((HAL_GetTick() - tickstart) > HAL_IWDG_DEFAULT_TIMEOUT)
    {
      if ((hiwdg->Instance->SR & IWDG_KERNEL_UPDATE_FLAGS) != 0x00u)
      {
        return HAL_TIMEOUT;
      }
    }
  }

  /* If window parameter is different than current value, modify window
  register */
  if (hiwdg->Instance->WINR != hiwdg->Init.Window)
  {
    /* Write to IWDG WINR the IWDG_Window value to compare with. In any case,
    even if window feature is disabled, Watchdog will be reloaded by writing
    windows register */
    hiwdg->Instance->WINR = hiwdg->Init.Window;
  }
  else
  {
    /* Reload IWDG counter with value defined in the reload register */
    __HAL_IWDG_RELOAD_COUNTER(hiwdg);
  }

  /* Return function status */
  return HAL_OK;
}


// int main (void) {
//   int i;

//   stm32_Init ();                                  // STM32 setup

//   if (RCC->CSR & (1<<29)) {                       // IWDG Reset Flag set
//     RCC->CSR |= (1<<24);                          // Clear Reset Flags
// 	GPIOB->BSRR = 1 << (ledPosIwdg+8);            // LED on
//   }
//   else {
//     GPIOB->BRR  = 1 << (ledPosIwdg+8);            // LED off
//   }

//   for (i = 0; i < 10; i++) {
//     delay(1000000);                               // wait less than watchdog interval
//     IWDG->KR  = 0xAAAA;                           // reload the watchdog
//   }
//   GPIOB->BSRR = 1 << (ledPosEnd+8);               // LED on

//   while (1) {                                     // Loop forever
//   } // end while
// } // end main
