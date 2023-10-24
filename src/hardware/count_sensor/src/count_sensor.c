#include "count_sensor.h"

CountSensor *current;

void CountSensor_Init(
    CountSensor *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint8_t GPIO_PortSourceGPIOx,
    uint16_t GPIO_Pin,
    uint8_t GPIO_PinSource,
    uint32_t EXTI_Line)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    this->RCC_APB2Periph       = RCC_APB2Periph;
    this->GPIOx                = GPIOx;
    this->GPIO_PortSourceGPIOx = GPIO_PortSourceGPIOx;
    this->GPIO_Pin             = GPIO_Pin;
    this->GPIO_PinSource       = GPIO_PinSource;
    this->EXTI_Line            = EXTI_Line;

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOx, GPIO_PinSource);

    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line    = EXTI_Line;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel                   = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_Init(&NVIC_InitStructure);
}

void CountSensor_IRQHandler(CountSensor *this)
{
    if (EXTI_GetITStatus(this->EXTI_Line) == SET) {
        /*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
        if (GPIO_ReadInputDataBit(this->GPIOx, this->GPIO_Pin) == 0) {
            this->Count++;
        }
        EXTI_ClearITPendingBit(this->EXTI_Line);
    }
}
