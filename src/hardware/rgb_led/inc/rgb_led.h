#ifndef __RGB_LED_H
#define __RGB_LED_H
#include "stm32f10x.h"

typedef struct {
    TIM_TypeDef *TIMx;
    uint32_t RCC_APB1Periph_TIMx;
    uint32_t RCC_APB2Periph_R;
    uint32_t RCC_APB2Periph_G;
    uint32_t RCC_APB2Periph_B;
    GPIO_TypeDef *GPIOx_R;
    GPIO_TypeDef *GPIOx_G;
    GPIO_TypeDef *GPIOx_B;
    uint16_t GPIO_Pin_R;
    uint16_t GPIO_Pin_G;
    uint16_t GPIO_Pin_B;
} RgbLed;

void RgbLed_Init(
    RgbLed *this,
    TIM_TypeDef *TIMx,
    uint32_t RCC_APB1Periph_TIMx,
    uint32_t RCC_APB2Periph_R,
    uint32_t RCC_APB2Periph_G,
    uint32_t RCC_APB2Periph_B,
    GPIO_TypeDef *GPIOx_R,
    GPIO_TypeDef *GPIOx_G,
    GPIO_TypeDef *GPIOx_B,
    uint16_t GPIO_Pin_R,
    uint16_t GPIO_Pin_G,
    uint16_t GPIO_Pin_B);

void RgbLed_SetRGBColor(RgbLed *this, uint32_t rgb);
void RgbLed_SetRGBColorValue(RgbLed *this, uint8_t r, uint8_t g, uint8_t b);

#endif // !__RGB_LED_H