#include "gpio.h"

void Gpio_Init(
    Gpio *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    GPIOMode_TypeDef GPIO_Mode,
    uint16_t GPIO_Pins)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);

    this->GPIOx     = GPIOx;
    this->GPIO_Pins = GPIO_Pins;

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pins;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}