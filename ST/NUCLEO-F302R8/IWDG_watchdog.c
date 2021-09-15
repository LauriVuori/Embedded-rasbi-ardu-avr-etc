#include "IWDG_watchdog.h"

void refresh_IWDG(void) {
    IWDG->KR = NOTIFY_IWDG;
}

void iwdg_init(void) {
    // initialize intependet independent watchdog

    // IWDG Key register
    // These bits must be written by software at regular intervals with the key value 0xAAAA, 
    // otherwise the watchdog generates a reset when the counter reaches 0
    // Use function refresh_IWDG
    IWDG->KR = ENABLE_IWDG;
    IWDG->SR = 0x0;                           //Values can be only updatet when all bits are 0
    
    // Write access to IWDG prescaler register (IWDG_PR), IWDG reload register (IWDG_RLR)
    // and IWDG window register (IWDG_WINR) is protected. To modify them, the user must first 
    // write the code 0x0000 5555 in the IWDG key register (IWDG_KR).
    IWDG->KR = 0x00005555;                  // Remove protection

    // IWDG prescaler register (IWDG_PR)
    // IWDG->PR = 0x0;                     // reset prescaler
    // IWDG->PR = (1 << 2);                // PR[2:0], bits 100: divider /64. 40000 hz / 64 = 625
    IWDG->PR = 0x7;                        // PR[2:0], bits 111: divider /256. 40000 hz / 256 = 156
    IWDG->RLR = 156-1;                     // approx 2 sec?? 

    


    // DBG_IWDG_STOP: Debug independent watchdog stopped when core is halted, 12th bit
    // 0: The independent watchdog counter clock continues even if the core is halted
    // 1: The independent watchdog counter clock is stopped when the core is halted
    // Debug MCU APB1 freeze register (DBGMCU_APB1_FZ)
    DBGMCU->APB1FZ |= (1 << 12);
}
