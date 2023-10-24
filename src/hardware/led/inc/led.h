#ifndef __LED_H
#define __LED_H
#include "stm32f10x.h"

typedef struct {
    uint32_t RCC_APB2Periph;
    GPIO_TypeDef *GPIOx;
    uint16_t *GPIO_Pins;
} Led;

void Led_Init(
    Led *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t *GPIO_Pins);

void Led_On(Led *this, uint16_t GPIO_Pin);
void Led_Off(Led *this, uint16_t GPIO_Pin);
void Led_Turn(Led *this, uint16_t GPIO_Pin);
void Led_On_All(Led *this);
void Led_Off_All(Led *this);

uint8_t Led_IsOn(Led *this, uint16_t GPIO_Pin);

#endif
