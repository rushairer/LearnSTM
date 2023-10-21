#ifndef __LED_H
#define __LED_H
#include "gpio.h"

typedef struct {
    Gpio gpio;
} Led;

void Led_Init(
    Led *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pins);

void Led_On(Led *this, uint16_t GPIO_Pin);
void Led_Off(Led *this, uint16_t GPIO_Pin);
void Led_Turn(Led *this, uint16_t GPIO_Pin);

uint8_t Led_isOn(Led *this, uint16_t GPIO_Pin);

#endif
