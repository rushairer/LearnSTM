#include "key.h"
#include "delay.h"

void Key_Init(
    Key *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pins)
{
    Gpio_Init(&this->gpio, RCC_APB2Periph, GPIOx, GPIO_Mode_IPU, GPIO_Pins);
}

uint8_t Key_IsPressed(Key *this, uint16_t GPIO_Pin)
{
    uint8_t isPressed = 0;

    if (GPIO_ReadInputDataBit(this->gpio.GPIOx, GPIO_Pin) == 0) {
        Delay_ms(20);
        while (GPIO_ReadInputDataBit(this->gpio.GPIOx, GPIO_Pin) == 0)
            ;
        Delay_ms(20);
        isPressed = 1;
    }
    return isPressed;
}