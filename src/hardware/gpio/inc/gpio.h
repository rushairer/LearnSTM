#ifndef __GPIO_H
#define __GPIO_H
#include "stm32f10x.h"

typedef struct {
    GPIO_TypeDef *GPIOx;
    GPIOMode_TypeDef GPIO_Mode;
    uint16_t GPIO_Pins;
} Gpio;

void Gpio_Init(
    Gpio *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    GPIOMode_TypeDef GPIO_Mode,
    uint16_t GPIO_Pins);

#endif
