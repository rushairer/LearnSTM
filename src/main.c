#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "oled_bmp.h"
#include "light_sensor.h"
#include "count_sensor.h"
#include "rgb_led.h"
#include <time.h>
#include <stdlib.h>
#include "servo.h"
#include "serial.h"
#include "usart.h"
#include "iap.h"

Led led;
uint16_t led1 = GPIO_Pin_0;
uint16_t led2 = GPIO_Pin_1;

Key key;
uint16_t key1 = GPIO_Pin_15;
uint16_t key2 = GPIO_Pin_12;

Oled oled;
uint16_t oled_scl = GPIO_Pin_8;
uint16_t oled_sda = GPIO_Pin_9;

LightSensor lightSensor;
uint16_t lightSensorPin = GPIO_Pin_13;

CountSensor countSensor;
uint16_t countSensorPin = GPIO_Pin_14;

RgbLed rgbLed;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;

Serial serial;

void TestKey(void)
{
    if (Key_IsPressed(&key, key1) == 1) {
        Led_On_All(&led);
        Oled_Display_On(&oled);
    }
    if (Key_IsPressed(&key, key2) == 1) {
        Led_Off_All(&led);
        Oled_Display_Off(&oled);
    }
}

void TestOled(void)
{
    // Oled_DrawBMP(&oled, 0, 0, 128, 16, OLED_BMP1);
    Oled_ShowNum(&oled, 2, 1, 379486, 6);
    Oled_ShowSignedNum(&oled, 3, 1, -379486, 6);
    Oled_ShowHexNum(&oled, 1, 1, 0xAA55, 4);
    Oled_ShowBinNum(&oled, 4, 1, 0xAA55, 16);
    Oled_DrawBMP(&oled, 60, 1, 80, 4, googledino20x20_right);

    Oled_CleanBuffer(&oled);
    Oled_RefreshScreen(&oled);

    Oled_SetPixel(&oled, 64, 32, OLED_COLOR_NORMAL);
    Oled_DrawLine(&oled, 0, 0, 127, 63, OLED_COLOR_NORMAL);
    Oled_RefreshScreen(&oled);
}

void TestRGBA()
{
    RgbLed_SetRGBColorValue(&rgbLed, (uint8_t)rand() % 255, (uint8_t)rand() % 255, (uint8_t)rand() % 255);
    Delay_s(1);
}

void TestSerial()
{
    Serial_SendByte(&serial, 0x41);

    uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};
    Serial_SendArray(&serial, MyArray, 4);

    Serial_SendString(&serial, "\r\nNum1=");

    Serial_SendNumber(&serial, 111, 3);

    printf("\r\nNum2=%d", 222);

    char String[100];
    sprintf(String, "\r\nNum3=%d", 333);
    Serial_SendString(&serial, String);

    Serial_Printf(&serial, "\r\nNum4=%d", 444);
    Serial_Printf(&serial, "\r\n");

    Serial_Printf(&serial, "\r\ndata:%d,%d,%d,%d,%d,%d", (uint8_t)rand() % 255, (uint8_t)rand() % 255, (uint8_t)rand() % 255, (uint8_t)rand() % 255, (uint8_t)rand() % 255, (uint8_t)rand() % 255);
    Serial_Printf(&serial, "\r\n");
    Delay_ms(100);

    if (Serial_GetRxFlag(&serial) == 1) {

        Oled_ShowString(&oled, 1, 1, "                      ");

        Serial_Printf(&serial, "\r\n<<<<<<<<<<<<<<<<<");
        Serial_SendString(&serial, (char *)serial.RxData);
        Serial_Printf(&serial, ">>>>>>>>>>>>>>>>>\r\n");

        Oled_ShowString(&oled, 1, 1, (char *)serial.RxData);
    }
}

int main()
{
    u16 times = 0;

    IAP_Init();           // 程序进入之后首先执行iap初始化 将标志位清除
    Delay_ms(200);        // 延时初始化
    NVIC_Configuration(); // 设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    uart_init(115200);    // 串口初始化为9600

    srand(time(0));

    uint16_t leds[2] = {led1, led2};
    Led_Init(&led, RCC_APB2Periph_GPIOA, GPIOA, leds);

    uint16_t keys[2] = {key1, key2};
    Key_Init(&key, RCC_APB2Periph_GPIOB, GPIOB, keys);

    Oled_Init(&oled, RCC_APB2Periph_GPIOB, GPIOB, oled_scl, oled_sda);

    // LightSensor_Init(&lightSensor, RCC_APB2Periph_GPIOB, GPIOB, lightSensorPin);

    // CountSensor_Init(&countSensor, RCC_APB2Periph_GPIOB, GPIOB, GPIO_PortSourceGPIOB, countSensorPin, GPIO_PinSource14, EXTI_Line14);

    // // TIM3: PA6 PA7 PB0
    // RgbLed_Init(
    //     &rgbLed,
    //     TIM3,
    //     RCC_APB1Periph_TIM3,
    //     RCC_APB2Periph_GPIOA,
    //     RCC_APB2Periph_GPIOA,
    //     RCC_APB2Periph_GPIOB,
    //     GPIOA,
    //     GPIOA,
    //     GPIOB,
    //     GPIO_Pin_6,
    //     GPIO_Pin_7,
    //     GPIO_Pin_0);

    Servo_Init(
        &servo1,
        TIM3,
        RCC_APB1Periph_TIM3,
        RCC_APB2Periph_GPIOA,
        GPIOA,
        GPIO_Pin_6,
        1);
    Servo_Init(
        &servo2,
        TIM3,
        RCC_APB1Periph_TIM3,
        RCC_APB2Periph_GPIOA,
        GPIOA,
        GPIO_Pin_7,
        2);
    Servo_Init(
        &servo3,
        TIM3,
        RCC_APB1Periph_TIM3,
        RCC_APB2Periph_GPIOB,
        GPIOB,
        GPIO_Pin_0,
        3);
    Servo_Init(
        &servo4,
        TIM3,
        RCC_APB1Periph_TIM3,
        RCC_APB2Periph_GPIOB,
        GPIOB,
        GPIO_Pin_1,
        4);
    Servo_Init(
        &servo5,
        TIM2,
        RCC_APB1Periph_TIM2,
        RCC_APB2Periph_GPIOA,
        GPIOA,
        GPIO_Pin_0,
        1);
    Servo_Init(
        &servo6,
        TIM2,
        RCC_APB1Periph_TIM2,
        RCC_APB2Periph_GPIOA,
        GPIOA,
        GPIO_Pin_1,
        2);
    Servo_Init(
        &servo7,
        TIM2,
        RCC_APB1Periph_TIM2,
        RCC_APB2Periph_GPIOA,
        GPIOA,
        GPIO_Pin_2,
        3);
    Servo_Init(
        &servo8,
        TIM2,
        RCC_APB1Periph_TIM2,
        RCC_APB2Periph_GPIOA,
        GPIOA,
        GPIO_Pin_3,
        4);

    Serial_Init(
        &serial,
        RCC_APB2Periph_GPIOA,
        GPIOA,
        GPIO_Pin_9,
        GPIO_Pin_10);

    // TestSsd1306();
    TestOled();

    float angle = 0;
    while (1) {
        if (USART_RX_STA & 0x80) {
            USART_RX_STA = 0;
            IAP_Handle(USART_RX_BUF);
        } else {
            times++;
            if (times % 50 == 0) {
                Led_Turn(&led, led2);
            }
            Delay_ms(100);
        }

        // TestRGBA();
        TestSerial();
        if (Key_IsPressed(&key, key1) == 1) {
            angle += 30;
            if (angle > 180) {
                angle = 0;
            }
        }

        if (Key_IsPressed(&key, key2) == 1) {
            angle = 0;
        }

        // Servo_SetAngle_CH1(&servo, angle);
        // Servo_SetAngle_CH2(&servo, angle);
        // Servo_SetAngle_CH3(&servo, angle);
        Servo_SetAngle(&servo1, angle);
        Servo_SetAngle(&servo2, angle + 30);
        Servo_SetAngle(&servo3, angle);
        Servo_SetAngle(&servo4, angle + 30);
        Servo_SetAngle(&servo5, angle);
        Servo_SetAngle(&servo6, angle + 30);
        Servo_SetAngle(&servo7, angle);
        Servo_SetAngle(&servo8, angle + 30);

        Oled_ShowNum(&oled, 3, 12, angle, 3);
        // TestRGBA();
        //  TestKey();
        //  for (i = 0; i <= 100; i++) {
        //      Pwm_SetCompare1(&pwmR, i);
        //      Pwm_SetCompare1(&pwmG, i);
        //      Pwm_SetCompare1(&pwmB, i);
        //      Delay_ms(10);
        //  }
        //  for (i = 0; i <= 100; i++) {
        //      Pwm_SetCompare1(&pwmR, 100 - i);
        //      Pwm_SetCompare1(&pwmG, 100 - i);
        //      Pwm_SetCompare1(&pwmB, 100 - i);

        //     Delay_ms(10);
        // }
    }
}

// void EXTI15_10_IRQHandler(void)
// {
//     CountSensor_IRQHandler(&countSensor);
// }

// void USART1_IRQHandler(void)
// {
//     Serial_IRQHandler(&serial);
// }