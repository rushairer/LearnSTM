#ifndef __I2C_H
#define __I2C_H
#include "stm32f10x.h"

typedef struct {
    uint32_t RCC_APB2Periph;
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Scl_Pin;
    uint16_t GPIO_Sda_Pin;
} I2c;

void I2c_Init(
    I2c *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Scl_Pin,
    uint16_t GPIO_Sda_Pin);

void I2c_Start(I2c *this);
void I2c_Stop(I2c *this);
void I2c_Wait(I2c *this);
void I2c_SendByte(I2c *this, uint8_t Byte);
uint8_t I2c_ReceiveByte(I2c *this);
void I2c_SendAck(I2c *this, uint8_t AckBit);
uint8_t I2c_ReceiveAck(I2c *this);

#endif