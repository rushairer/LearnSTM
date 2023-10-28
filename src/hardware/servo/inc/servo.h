#ifndef __SERVO_H
#define __SERVO_H
#include "stm32f10x.h"

typedef struct {
    TIM_TypeDef *TIMx;
    uint32_t RCC_APB1Periph_TIMx;
    uint32_t RCC_APB2Periph;
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;
} Servo;

void Servo_Init(
    Servo *this,
    TIM_TypeDef *TIMx,
    uint32_t RCC_APB1Periph_TIMx,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pin);

void Servo_SetAngle_CH1(Servo *this, float Angle);
void Servo_SetAngle_CH2(Servo *this, float Angle);
void Servo_SetAngle_CH3(Servo *this, float Angle);
void Servo_SetAngle_CH4(Servo *this, float Angle);

#endif
