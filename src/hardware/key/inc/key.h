#ifndef __KEY_H
#define __KEY_H
#include "gpio.h"

typedef struct {
    Gpio gpio;
} Key;

void Key_Init(
    Key *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pins);

uint8_t Key_IsPressed(Key *this, uint16_t GPIO_Pin);

#endif
