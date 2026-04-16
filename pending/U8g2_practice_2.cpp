/*U8g2_practice_2
尝试一下时钟
*/

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <WiFi.h>
#include <time.h>

// --- 硬件配置 ---
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// --- 引脚定义 ---
#define I2C_SDA 4   // SDA：GPIO4
#define I2C_SCL 5   // SCL：GPIO5

int Num = 0;

void setup () {
    // I2C初始化
    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.setClock(400000);  // 设置 I2C 时钟频率为 400 kHz
    // OLED 初始化
    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.setFont(u8g2_font_wqy16_t_gb2312);
    u8g2.setFontPosTop();
    delay(5000);
    Serial.print("初始化完成\n");
}

void loop() {
    u8g2.clearBuffer();
    u8g2.setCursor(5,5);
    u8g2.println(Num);
    u8g2.sendBuffer(); // 必须调用
    Num ++;
    delay(1000);
}