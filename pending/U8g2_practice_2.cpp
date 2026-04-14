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

#define PWR_OUT 1   // 输出高电平：GPIO1
#define PWR_IN 2    // 接收电平：GPIO2

#define LED_PWR_OUT 7   // LED输出脚

#define LED_PIN 16          // PWM 引脚: GPIO16
#define CHANNEL 0           // LEDC 通道 0
#define PWM_FREQ 5000       // PWM 频率 5kHz
#define PWM_RES 8           // 分辨率 8 位（0～255）

void setup () {
    // I2C初始化
    Wire.begin(I2C_SDA, I2C_SCL);
    Wire.setClock(400000);  // 设置 I2C 时钟频率为 400 kHz
    // OLED 初始化
    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.setFont(u8g2_font_wqy16_t_gb2312);
    u8g2.setFontPosTop();

    pinMode(PWR_OUT, OUTPUT);
    pinMode(LED_PWR_OUT, OUTPUT);
    pinMode(PWR_IN, INPUT_PULLUP);
    digitalWrite(PWR_OUT, HIGH);
    digitalWrite(LED_PWR_OUT, HIGH);

    ledcSetup(CHANNEL, PWM_FREQ, PWM_RES);
    ledcAttachPin(LED_PIN, CHANNEL);

    Serial.print("初始化完成\n");
}

void loop() {
    // 渐亮：占空比从 0 增加到 255
    for (int duty = 0; duty <= 255; duty++) {
        ledcWrite(CHANNEL, duty);
        delay(5);           // 控制变化速度
    }
    // 渐暗：占空比从 255 减少到 0
    for (int duty = 255; duty >= 0; duty--) {
        ledcWrite(CHANNEL, duty);
        delay(5);
    }
}