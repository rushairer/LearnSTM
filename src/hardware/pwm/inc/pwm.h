#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"

typedef struct {
    uint32_t RCC_APB1Periph;
    uint32_t RCC_APB2Periph;
    TIM_TypeDef *TIMx;
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;
} Pwm;

void Pwm_Init(
    Pwm *this,
    uint32_t RCC_APB1Periph,
    uint32_t RCC_APB2Periph,
    TIM_TypeDef *TIMx,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pin);

void Pwm_SetCompare1(Pwm *this, uint16_t Compare);
void Pwm_SetCompare2(Pwm *this, uint16_t Compare);
void Pwm_SetCompare3(Pwm *this, uint16_t Compare);

#endif
