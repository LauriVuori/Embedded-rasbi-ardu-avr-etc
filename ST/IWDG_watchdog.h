#include "../main.h"

// board NUCLEO-F302R8
// reference manual s.723
// https://elektroniikka.narkive.fi/JhXgbmFh/riippumaton-vahtikoira-iwdg-vai-ikkunavartija-wwdg
// In STM32 microcontrollers the independent watchdog (IWDG) is a 12-bit down-counter timer 
// clocked by its own dedicated low-speed clock (LSI) and thus stays active even if the main clock fails.

// The independent watchdog (IWDG) is clocked by its own dedicated low-speed clock (LSI clock frequency is 
// around 40 kHz (between 30 kHz and 50 kHz))  
// and thus stays active even if the main clock fails.
// The IWDG is best suited for applications that require the watchdog to run as a totally 
// independent process outside the main application, but have lower timing accuracy 
// constraints. (ref. 723)


// Configuring the IWDG when the window option is disabled
// When the window option it is not used, the IWDG can be configured as follows:
// 1. Enable the IWDG by writing 0x0000 CCCC in the IWDG key register (IWDG_KR).
// 2. Enable register access by writing 0x0000 5555 in the IWDG key register (IWDG_KR).
// 3. Write the prescaler by programming the IWDG prescaler register (IWDG_PR) from 0 to 7.
// 4. Write the IWDG reload register (IWDG_RLR).
// 5. Wait for the registers to be updated (IWDG_SR = 0x0000 0000).
// 6. Refresh the counter value with IWDG_RLR (IWDG_KR = 0x0000 AAAA)

// typedef struct
// {
//   __IO uint32_t KR;   /*!< IWDG Key register,       Address offset: 0x00 */
//   __IO uint32_t PR;   /*!< IWDG Prescaler register, Address offset: 0x04 */
//   __IO uint32_t RLR;  /*!< IWDG Reload register,    Address offset: 0x08 */
//   __IO uint32_t SR;   /*!< IWDG Status register,    Address offset: 0x0C */
//   __IO uint32_t WINR; /*!< IWDG Window register,    Address offset: 0x10 */
// } IWDG_TypeDef;


// IWDG->KR must be written by software at regular intervals with the key value 0xAAAA, 
// otherwise the watchdog generates a reset when the counter reaches 0
#define NOTIFY_IWDG 0xAAAA

// Writing the key value 0xCCCC starts the watchdog (except if the hardware watchdog option 
// is selected)
#define ENABLE_IWDG 0xCCCC

void refresh_IWDG(void);
void iwdg_init(void);