#include "i2c.h"
#include "delay.h"

void I2c_Init(
    I2c *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Scl_Pin,
    uint16_t GPIO_Sda_Pin)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);

    this->RCC_APB2Periph = RCC_APB2Periph;
    this->GPIOx          = GPIOx;
    this->GPIO_Scl_Pin   = GPIO_Scl_Pin;
    this->GPIO_Sda_Pin   = GPIO_Sda_Pin;

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Scl_Pin | GPIO_Sda_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
    GPIO_SetBits(GPIOx, GPIO_Scl_Pin | GPIO_Sda_Pin);
}
void I2c_WriteScl(I2c *this, BitAction BitVal)
{
    GPIO_WriteBit(this->GPIOx, this->GPIO_Scl_Pin, BitVal);
    Delay_us(10);
}

void I2c_WriteSda(I2c *this, BitAction BitVal)
{
    GPIO_WriteBit(this->GPIOx, this->GPIO_Sda_Pin, BitVal);
    Delay_us(10);
}

uint8_t I2c_ReadSda(I2c *this)
{
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(this->GPIOx, this->GPIO_Sda_Pin);
    Delay_us(10);
    return BitValue;
}

void I2c_Start(I2c *this)
{
    I2c_WriteSda(this, Bit_SET);
    I2c_WriteScl(this, Bit_SET);
    I2c_WriteSda(this, Bit_RESET);
    I2c_WriteScl(this, Bit_RESET);
}

void I2c_Stop(I2c *this)
{
    I2c_WriteSda(this, Bit_RESET);
    I2c_WriteScl(this, Bit_SET);
    I2c_WriteSda(this, Bit_SET);
}

void I2c_Wait(I2c *this)
{
    I2c_WriteScl(this, Bit_SET);
    I2c_WriteScl(this, Bit_RESET);
}

void I2c_SendByte(I2c *this, uint8_t Byte)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        I2c_WriteSda(this, Byte & (0x80 >> i));
        I2c_WriteScl(this, Bit_SET);
        I2c_WriteScl(this, Bit_RESET);
    }
}

uint8_t I2c_ReceiveByte(I2c *this)
{
    uint8_t i, Byte = 0x00;
    I2c_WriteSda(this, Bit_SET);
    for (i = 0; i < 8; i++) {
        I2c_WriteScl(this, Bit_SET);
        if (I2c_ReadSda(this) == 1) {
            Byte |= (0x80 >> i);
        }
        I2c_WriteScl(this, Bit_RESET);
    }
    return Byte;
}
void I2c_SendAck(I2c *this, uint8_t AckBit)
{
    I2c_WriteSda(this, AckBit);
    I2c_WriteScl(this, Bit_SET);
    I2c_WriteScl(this, Bit_RESET);
}
uint8_t I2c_ReceiveAck(I2c *this)
{
    uint8_t AckBit;
    I2c_WriteSda(this, Bit_SET);
    I2c_WriteScl(this, Bit_SET);
    AckBit = I2c_ReadSda(this);
    I2c_WriteScl(this, Bit_RESET);

    return AckBit;
}