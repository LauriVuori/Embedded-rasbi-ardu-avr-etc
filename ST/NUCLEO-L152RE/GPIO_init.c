
#include "GPIO.init.h"


void GPIO_init_pin(GPIO_TypeDef *GPIOx, uint8_t pin, uint8_t mode_value, uint8_t alternate_function_val) {
	GPIOx->MODER &= ~((uint32_t)(0x3 << (pin * 2))); // clear pins
	GPIOx->MODER |= (uint32_t)(mode_value << (pin * 2));
	if (pin < 7) {
		GPIOx->AFR[LOWER] &= ~((uint32_t)(0xF << (pin * 4)));
		GPIOx->AFR[LOWER] |= (uint32_t)(alternate_function_val << (pin * 4));
	}
	else {
		GPIOx->AFR[HIGHER] &= ~((uint32_t)(0xF << (pin * 4)));
		GPIOx->AFR[HIGHER] |= (uint32_t)(alternate_function_val << (pin * 4));
	}
}

void GPIO_WritePin(GPIO_TypeDef *GPIOx, uint8_t pin_num, uint32_t bit_value) {
	if (bit_value) {
		GPIOx->BSRR |= (uint16_t)(1 << pin_num);
	}
	else {
		GPIOx->BRR |= (uint16_t)(1 << pin_num);
	}
}

void GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint32_t pin_num) {
	GPIOx->ODR ^= (uint16_t)(1 << pin_num);
}

uint32_t GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint32_t pin_num) {
	uint32_t bit_value;
	
	bit_value = (GPIOx->IDR & (uint16_t)(1 << pin_num)) >> pin_num;
	
	return bit_value;
}
