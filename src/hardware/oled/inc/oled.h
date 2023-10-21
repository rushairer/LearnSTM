#ifndef __OLED_H
#define __OLED_H
#include "gpio.h"

typedef struct {
    Gpio gpio;
    uint16_t GPIO_Scl_Pin;
    uint16_t GPIO_Sda_Pin;
} Oled;

void Oled_Init(
    Oled *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Scl_Pin,
    uint16_t GPIO_Sda_Pin);

void Oled_Clear(Oled *this);

void Oled_ShowChar(Oled *this, uint8_t Line, uint8_t Column, char Char);
void Oled_ShowString(Oled *this, uint8_t Line, uint8_t Column, char *String);
void Oled_ShowNum(Oled *this, uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void Oled_ShowSignedNum(Oled *this, uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);
void Oled_ShowHexNum(Oled *this, uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);
void Oled_ShowBinNum(Oled *this, uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);

#endif // !__OLED_H