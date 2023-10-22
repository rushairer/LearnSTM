#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "oled_bmp.h"

int main()
{
    Led led;
    uint16_t led1    = GPIO_Pin_0;
    uint16_t led2    = GPIO_Pin_1;
    uint16_t leds[2] = {led1, led2};

    Led_Init(&led, RCC_APB2Periph_GPIOA, GPIOA, leds);

    Key key;
    uint16_t key1    = GPIO_Pin_15;
    uint16_t key2    = GPIO_Pin_12;
    uint16_t keys[2] = {key1, key2};

    Key_Init(&key, RCC_APB2Periph_GPIOB, GPIOB, keys);

    Oled oled;
    uint16_t oled_scl = GPIO_Pin_8;
    uint16_t oled_sda = GPIO_Pin_9;
    Oled_Init(&oled, RCC_APB2Periph_GPIOB, GPIOB, oled_scl, oled_sda);

    // Oled_DrawBMP(&oled, 0, 0, 128, 16, OLED_BMP1);

    Oled_ShowNum(&oled, 2, 1, 379486, 6);
    Oled_ShowSignedNum(&oled, 3, 1, -379486, 6);
    Oled_ShowHexNum(&oled, 1, 1, 0xAA55, 4);
    Oled_ShowBinNum(&oled, 4, 1, 0xAA55, 16);

    // 测试水平滚动
    // Oled_WriteCommand(&oled, 0x2F);
    // Oled_WriteCommand(&oled, 0x26);
    // Oled_ShowString(&oled, 4, 10, "6666666666666666666666666677777777777777778888888888888888888888");

    // Oled_DrawBMP(&oled, 0, 0, 128, 16, OLED_BMP1);
    Oled_DrawBMP(&oled, 0, 0, 128, 2, OLED_BMP2);
    Oled_DrawBMP(&oled, 60, 1, 80, 4, googledino20x20_right);
    while (1) {
        // Oled_Clear(&oled);
        // Oled_ShowNum(&oled, 2, 1, 379486, 6);
        // Oled_ShowSignedNum(&oled, 3, 1, -379486, 6);
        // Oled_ShowHexNum(&oled, 1, 1, 0xAA55, 4);
        // Oled_ShowBinNum(&oled, 4, 1, 0xAA55, 16);
        // Delay_s(2);

        // Oled_Clear(&oled);
        // Oled_Clear(&oled);
        // Oled_DrawBMP(&oled, 0, 0, 128, 16, OLED_BMP2);
        // Delay_s(2);

        // Oled_Clear(&oled);
        // Oled_DrawBMP(&oled, 0, 0, 128, 16, OLED_BMP2);
        // Delay_s(2);

        // Oled_Clear(&oled);
        // Oled_DrawBMP(&oled, 0, 0, 128, 2, OLED_BMP2);
        // Oled_DrawBMP(&oled, 60, 1, 80, 4, googledino20x20_right);
        // Delay_s(1);

        if (Key_IsPressed(&key, key1) == 1) {
            // Led_Turn(&led, led1);
            Led_On_All(&led);
            Oled_Display_On(&oled);

            // if (Led_isOn(&led, led1) == 1) {
            //     Oled_ShowString(&oled, 3, 10, "Das");
            // } else {
            //     Oled_ShowString(&oled, 3, 10, "   ");
            // }
        }
        if (Key_IsPressed(&key, key2) == 1) {
            // Led_Turn(&led, led2);
            Led_Off_All(&led);
            Oled_Display_Off(&oled);
            // if (Led_isOn(&led, led2) == 1) {
            //     Oled_ShowString(&oled, 3, 6, "Aben");
            // } else {
            //     Oled_ShowString(&oled, 3, 6, "    ");
            // }
        }
    }
}
