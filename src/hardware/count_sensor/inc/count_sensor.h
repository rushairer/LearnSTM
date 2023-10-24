#ifndef __COUNT_SENSOR_H
#define __COUNT_SENSOR_H
#include "stm32f10x.h"

typedef struct {
    uint32_t RCC_APB2Periph;
    GPIO_TypeDef *GPIOx;
    uint8_t GPIO_PortSourceGPIOx;
    uint16_t GPIO_Pin;
    uint8_t GPIO_PinSource;
    uint16_t Count;
    uint32_t EXTI_Line;
} CountSensor;

void CountSensor_Init(
    CountSensor *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint8_t GPIO_PortSourceGPIOx,
    uint16_t GPIO_Pin,
    uint8_t GPIO_PinSource,
    uint32_t EXTI_Line);

void CountSensor_IRQHandler(CountSensor *this);

#endif