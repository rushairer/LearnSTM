#include "led.h"

void Led_Init(
    Led *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pins)
{
    Gpio_Init(&this->gpio, RCC_APB2Periph, GPIOx, GPIO_Mode_Out_PP, GPIO_Pins);
}

void Led_On(Led *this, uint16_t GPIO_Pin)
{
    GPIO_ResetBits(this->gpio.GPIOx, GPIO_Pin);
}

void Led_Off(Led *this, uint16_t GPIO_Pin)
{
    GPIO_SetBits(this->gpio.GPIOx, GPIO_Pin);
}

void Led_Turn(Led *this, uint16_t GPIO_Pin)
{
    if (Led_isOn(this, GPIO_Pin) == 1) {
        Led_Off(this, GPIO_Pin);
    } else {
        Led_On(this, GPIO_Pin);
    }
}

uint8_t Led_isOn(Led *this, uint16_t GPIO_Pin)
{
    if (GPIO_ReadOutputDataBit(this->gpio.GPIOx, GPIO_Pin) == 0) {
        return 1;
    } else {
        return 0;
    }
}