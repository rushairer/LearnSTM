#include "led.h"

void Led_Init(
    Led *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t *GPIO_Pins)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);

    this->RCC_APB2Periph = RCC_APB2Periph;
    this->GPIOx          = GPIOx;
    this->GPIO_Pins      = GPIO_Pins;

    uint16_t pins = 0;
    for (uint8_t i = 0; i < sizeof(GPIO_Pins); i++) {
        pins = pins | GPIO_Pins[i];
    }
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = pins;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void Led_On(Led *this, uint16_t GPIO_Pin)
{
    GPIO_ResetBits(this->GPIOx, GPIO_Pin);
}

void Led_Off(Led *this, uint16_t GPIO_Pin)
{
    GPIO_SetBits(this->GPIOx, GPIO_Pin);
}

void Led_Turn(Led *this, uint16_t GPIO_Pin)
{
    if (Led_isOn(this, GPIO_Pin) == 1) {
        Led_Off(this, GPIO_Pin);
    } else {
        Led_On(this, GPIO_Pin);
    }
}

void Led_On_All(Led *this)
{
    for (uint8_t i = 0; i < sizeof(this->GPIO_Pins); i++) {
        Led_On(this, this->GPIO_Pins[i]);
    }
}

void Led_Off_All(Led *this)
{
    for (uint8_t i = 0; i < sizeof(this->GPIO_Pins); i++) {
        Led_Off(this, this->GPIO_Pins[i]);
    }
}

uint8_t Led_isOn(Led *this, uint16_t GPIO_Pin)
{
    if (GPIO_ReadOutputDataBit(this->GPIOx, GPIO_Pin) == 0) {
        return 1;
    } else {
        return 0;
    }
}