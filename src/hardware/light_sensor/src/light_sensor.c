#include "light_sensor.h"

void LightSensor_Init(
    LightSensor *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pin)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);

    this->RCC_APB2Periph = RCC_APB2Periph;
    this->GPIOx          = GPIOx;
    this->GPIO_Pin       = GPIO_Pin;

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

uint8_t LightSensor_IsOn(LightSensor *this)
{
    if (GPIO_ReadInputDataBit(this->GPIOx, this->GPIO_Pin) == 0) {
        return 1;
    } else {
        return 0;
    }
}