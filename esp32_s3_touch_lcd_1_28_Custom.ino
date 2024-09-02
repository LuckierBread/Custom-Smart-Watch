#include <Arduino.h>
#include "LCD_Test.h"

Paint.Width = 240;
Paint.Height = 240;

UWORD Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
UWORD *BlackImage;
CST816S touch(6, 7, 13, 5); // sda, scl, rst, irq

float acc[3], gyro[3];
unsigned int tim_count = 0;
uint16_t result;
const float conversion_factor = 3.3f / (1 << 12) * 3;

void setup()
{
    Serial.begin(115200);
    touch.begin();

    // PSRAM Initialize
    if (psramInit()) {
        Serial.println("\nPSRAM is correctly initialized");
    } else {
        Serial.println("PSRAM not available");
    }

    if ((BlackImage = (UWORD *)ps_malloc(Imagesize)) == NULL) {
        Serial.println("Failed to apply for black memory...");
        exit(0);
    }

    // Initialize display and accelerometer
    if (DEV_Module_Init() != 0) {
        Serial.println("GPIO Init Fail!");
        exit(0);
    } else {
        Serial.println("GPIO Init successful!");
    }
    
    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(WHITE);
    
    QMI8658_init();
    Serial.println("QMI8658_init\r\n");
}

void loop()
{   
  Serial.println("Start");
    Paint_Clear(WHITE);
    Paint_DrawPoint(120,120,RED,DOT_PIXEL_1X1,DOT_FILL_AROUND);
    delay(2000); // Delay to prevent excessive updates
  Serial.println("End");
}
