#ifndef __SERIAL_H
#define __SERIAL_H
#include <stdio.h>
#include "stm32f10x.h"

typedef struct {
    uint32_t RCC_APB2Periph;
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin_Tx;
    uint16_t GPIO_Pin_Rx;
    uint8_t RxData[4];
    uint8_t RxFlag;
} Serial;

void Serial_Init(
    Serial *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pin_Tx,
    uint16_t GPIO_Pin_Rx);

void Serial_SendByte(Serial *this, uint8_t Byte);
void Serial_SendArray(Serial *this, uint8_t *Array, uint16_t Length);
void Serial_SendString(Serial *this, char *String);
void Serial_SendNumber(Serial *this, uint32_t Number, uint8_t Length);
void Serial_SendData(Serial *this, uint8_t *Array, uint16_t Length);
void Serial_Printf(Serial *this, char *format, ...);
uint8_t Serial_GetRxFlag(Serial *this);
void Serial_IRQHandler(Serial *this);

#endif // !__SERIAL_H
