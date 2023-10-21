#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "oled_bmp.h"

int main()
{
    Led led;
    uint16_t led1 = GPIO_Pin_0;
    uint16_t led2 = GPIO_Pin_1;
    Led_Init(&led, RCC_APB2Periph_GPIOA, GPIOA, led1 | led2);

    Key key;
    uint16_t key1 = GPIO_Pin_15;
    uint16_t key2 = GPIO_Pin_12;
    Key_Init(&key, RCC_APB2Periph_GPIOB, GPIOB, key1 | key2);

    Oled oled;
    uint16_t oled_scl = GPIO_Pin_8;
    uint16_t oled_sda = GPIO_Pin_9;
    Oled_Init(&oled, RCC_APB2Periph_GPIOB, GPIOB, oled_scl, oled_sda);

    // Oled_ShowNum(&oled, 2, 1, 379486, 6);
    // Oled_ShowSignedNum(&oled, 3, 1, -379486, 6);
    // Oled_ShowHexNum(&oled, 1, 1, 0xAA55, 4);
    // Oled_ShowBinNum(&oled, 4, 1, 0xAA55, 16);

    Oled_DrawBMP(&oled, 0, 0, 128, 64, OLED_BMP2);

    while (1) {
        if (Key_IsPressed(&key, key1) == 1) {
            Led_Turn(&led, led1);
            if (Led_isOn(&led, led1) == 1) {
                Oled_ShowString(&oled, 1, 5, "Das");
            } else {
                Oled_ShowString(&oled, 1, 5, "   ");
            }
        }
        if (Key_IsPressed(&key, key2) == 1) {
            Led_Turn(&led, led2);
            if (Led_isOn(&led, led2) == 1) {
                Oled_ShowString(&oled, 1, 1, "Aben");
            } else {
                Oled_ShowString(&oled, 1, 1, "    ");
            }
        }
    }
}
