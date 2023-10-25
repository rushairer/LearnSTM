#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "oled.h"
#include "oled_bmp.h"
#include "light_sensor.h"
#include "count_sensor.h"
#include "driver_ssd1306_advance.h"

CountSensor countSensor;

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

    LightSensor lightSensor;
    uint16_t lightSensorPin = GPIO_Pin_13;
    LightSensor_Init(&lightSensor, RCC_APB2Periph_GPIOB, GPIOB, lightSensorPin);

    uint16_t countSensorPin = GPIO_Pin_14;
    CountSensor_Init(&countSensor, RCC_APB2Periph_GPIOB, GPIOB, GPIO_PortSourceGPIOB, countSensorPin, GPIO_PinSource14, EXTI_Line14);
    Oled_ShowString(&oled, 2, 1, "Count:");

    uint8_t res;
    res = ssd1306_advance_init(SSD1306_INTERFACE_IIC, SSD1306_ADDR_SA0_0);

    if (res != 0) {
        return 1;
    }
    // res = ssd1306_advance_enable_zoom_in();
    res = ssd1306_advance_string(0, 0, "123323", 3, 0, SSD1306_FONT_12);
    res = ssd1306_advance_rect(10, 20, 30, 30, 1);

    res = ssd1306_advance_fade_blinking(SSD1306_FADE_BLINKING_MODE_BLINKING, 0);
    res = ssd1306_advance_vertical_left_horizontal_scroll(0, 7, 0, SSD1306_SCROLL_FRAME_2);
    // res = ssd1306_advance_picture(0, 0, 127, 63, (uint8_t *)OLED_BMP2);

    // Oled_DrawBMP(&oled, 0, 0, 128, 16, OLED_BMP1);

    // Oled_ShowNum(&oled, 2, 1, 379486, 6);
    // Oled_ShowSignedNum(&oled, 3, 1, -379486, 6);
    // Oled_ShowHexNum(&oled, 1, 1, 0xAA55, 4);
    // Oled_ShowBinNum(&oled, 4, 1, 0xAA55, 16);

    // // 测试水平滚动
    // // Oled_WriteCommand(&oled, 0x2F);
    // // Oled_WriteCommand(&oled, 0x26);
    // // Oled_ShowString(&oled, 4, 10, "6666666666666666666666666677777777777777778888888888888888888888");

    // // Oled_DrawBMP(&oled, 0, 0, 128, 16, OLED_BMP1);
    // Oled_DrawBMP(&oled, 0, 0, 128, 2, OLED_BMP2);
    // Oled_DrawBMP(&oled, 60, 1, 80, 4, googledino20x20_right);
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

        // if (Key_IsPressed(&key, key1) == 1) {
        //     // Led_Turn(&led, led1);
        //     Led_On_All(&led);
        //     Oled_Display_On(&oled);

        //     // if (Led_IsOn(&led, led1) == 1) {
        //     //     Oled_ShowString(&oled, 3, 10, "Das");
        //     // } else {
        //     //     Oled_ShowString(&oled, 3, 10, "   ");
        //     // }
        // }
        // if (Key_IsPressed(&key, key2) == 1) {
        //     // Led_Turn(&led, led2);
        //     Led_Off_All(&led);
        //     Oled_Display_Off(&oled);
        //     // if (Led_IsOn(&led, led2) == 1) {
        //     //     Oled_ShowString(&oled, 3, 6, "Aben");
        //     // } else {
        //     //     Oled_ShowString(&oled, 3, 6, "    ");
        //     // }
        // }

        if (LightSensor_IsOn(&lightSensor) == 1) {
            Led_On_All(&led);
            // Oled_Display_On(&oled);

        } else {
            Led_Off_All(&led);
            // Oled_Display_Off(&oled);
        }

        // Oled_ShowNum(&oled, 1, 1, LightSensor_IsOn(&lightSensor), 4);

        // Oled_ShowNum(&oled, 3, 7, countSensor.Count, 5);
    }
}

void EXTI15_10_IRQHandler(void)
{
    CountSensor_IRQHandler(&countSensor);
}
