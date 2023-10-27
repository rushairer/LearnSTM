#include "rgb_led.h"

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
    uint16_t GPIO_Pin_B)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_R, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_G, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_B, ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMx, ENABLE);

    this->TIMx                = TIMx;
    this->RCC_APB1Periph_TIMx = RCC_APB1Periph_TIMx;
    this->RCC_APB2Periph_R    = RCC_APB2Periph_R;
    this->RCC_APB2Periph_G    = RCC_APB2Periph_G;
    this->RCC_APB2Periph_B    = RCC_APB2Periph_B;
    this->GPIOx_R             = GPIOx_R;
    this->GPIOx_G             = GPIOx_G;
    this->GPIOx_B             = GPIOx_B;
    this->GPIO_Pin_R          = GPIO_Pin_R;
    this->GPIO_Pin_G          = GPIO_Pin_G;
    this->GPIO_Pin_B          = GPIO_Pin_B;

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_R | GPIO_Pin_G | GPIO_Pin_B;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx_R, &GPIO_InitStructure);
    GPIO_Init(GPIOx_G, &GPIO_InitStructure);
    GPIO_Init(GPIOx_B, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period            = 255;  // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler         = 1999; // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = 0; // CCR

    TIM_OC1Init(TIMx, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);

    TIM_OC2Init(TIMx, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);

    TIM_OC3Init(TIMx, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIMx, ENABLE);
    TIM_Cmd(TIMx, ENABLE);
}

void RgbLed_SetRGBColor(RgbLed *this, uint32_t rgb)
{
    TIM_SetCompare1(this->TIMx, (uint16_t)(rgb >> 16));
    TIM_SetCompare2(this->TIMx, (uint16_t)(rgb >> 8));
    TIM_SetCompare3(this->TIMx, (uint16_t)rgb);
}

void RgbLed_SetRGBColorValue(RgbLed *this, uint8_t r, uint8_t g, uint8_t b)
{
    TIM_SetCompare1(this->TIMx, (uint16_t)(r));
    TIM_SetCompare2(this->TIMx, (uint16_t)(g));
    TIM_SetCompare3(this->TIMx, (uint16_t)(b));
}
