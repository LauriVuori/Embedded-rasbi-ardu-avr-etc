#include "stm32l1xx.h"


#define LOWER 0
#define HIGHER 1
#define INPUT 0         // 00: Input (reset state)
#define GPIO  1         //01: General purpose output mode
#define ALTERNATE 2     // 10: Alternate function mode
#define ANALOG 3        //11: Analog mode