#include "servo.h"

void Servo_Init(
    Servo *this,
    TIM_TypeDef *TIMx,
    uint32_t RCC_APB1Periph_TIMx,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pin)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIMx, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);

    this->TIMx                = TIMx;
    this->RCC_APB1Periph_TIMx = RCC_APB1Periph_TIMx;
    this->RCC_APB2Periph      = RCC_APB2Periph;
    this->GPIOx               = GPIOx;
    this->GPIO_Pin            = GPIO_Pin;

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision     = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode       = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period            = 20000 - 1; // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler         = 72 - 1;    // PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseInitStructure);

    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse       = 0; // CCR
    TIM_OC4Init(TIMx, &TIM_OCInitStructure);

    TIM_Cmd(TIMx, ENABLE);
}

void Servo_SetAngle_CH1(Servo *this, float Angle)
{
    TIM_SetCompare1(this->TIMx, Angle / 180 * 2000 + 500);
}

void Servo_SetAngle_CH2(Servo *this, float Angle)
{
    TIM_SetCompare2(this->TIMx, Angle / 180 * 2000 + 500);
}

void Servo_SetAngle_CH3(Servo *this, float Angle)
{
    TIM_SetCompare3(this->TIMx, Angle / 180 * 2000 + 500);
}

void Servo_SetAngle_CH4(Servo *this, float Angle)
{
    TIM_SetCompare4(this->TIMx, Angle / 180 * 2000 + 500);
}