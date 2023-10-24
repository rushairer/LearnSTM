#ifndef __LIGHT_SENSOR_H
#define __LIGHT_SENSOR_H
#include "stm32f10x.h"

typedef struct {
    uint32_t RCC_APB2Periph;
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;
} LightSensor;

void LightSensor_Init(
    LightSensor *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pin);

uint8_t LightSensor_IsOn(LightSensor *this);

#endif