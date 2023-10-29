#include "serial.h"
#include <stdio.h>
#include <stdarg.h>

void Serial_Init(
    Serial *this,
    uint32_t RCC_APB2Periph,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pin_Tx,
    uint16_t GPIO_Pin_Rx)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    this->RCC_APB2Periph = RCC_APB2Periph;
    this->GPIOx          = GPIOx;
    this->GPIO_Pin_Tx    = GPIO_Pin_Tx;
    this->GPIO_Pin_Rx    = GPIO_Pin_Rx;

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_Tx;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_Rx;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate            = 115200;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStructure.USART_Parity              = USART_Parity_No;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_Init(&NVIC_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(Serial *this, uint8_t Byte)
{
    USART_SendData(USART1, Byte);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {
        ;
    }
}

void Serial_SendArray(Serial *this, uint8_t *Array, uint16_t Length)
{
    uint16_t i;
    for (i = 0; i < Length; i++) {
        Serial_SendByte(this, Array[i]);
    }
}

void Serial_SendData(Serial *this, uint8_t *Array, uint16_t Length)
{
    Serial_SendByte(this, 0xFF);
    Serial_SendArray(this, Array, Length);
    Serial_SendByte(this, 0xFE);
}

void Serial_SendString(Serial *this, char *String)
{
    uint8_t i;
    for (i = 0; String[i] != '\0'; i++) {
        Serial_SendByte(this, String[i]);
    }
}

uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
    uint32_t Result = 1;
    while (Y--) {
        Result *= X;
    }
    return Result;
}

void Serial_SendNumber(Serial *this, uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++) {
        Serial_SendByte(this, Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
    }
}

void Serial_Printf(Serial *this, char *format, ...)
{
    char String[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    Serial_SendString(this, String);
}

uint8_t Serial_GetRxFlag(Serial *this)
{
    if (this->RxFlag == 1) {
        this->RxFlag = 0;
        return 1;
    }
    return 0;
}

void Serial_IRQHandler(Serial *this)
{
    static uint8_t RxState   = 0;
    static uint8_t pRxPacket = 0;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET) {
        uint8_t RxData = USART_ReceiveData(USART1);

        if (RxState == 0) {
            if (RxData == '@' && this->RxFlag == 0) {
                RxState   = 1;
                pRxPacket = 0;
            }
        } else if (RxState == 1) {
            if (RxData == '\r') {
                RxState = 2;
            } else {
                this->RxData[pRxPacket] = RxData;
                pRxPacket++;
            }
        } else if (RxState == 2) {
            if (RxData == '\n') {
                RxState                 = 0;
                this->RxData[pRxPacket] = '\0';
                this->RxFlag            = 1;
            }
        }

        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}
