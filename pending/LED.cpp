#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN     48
#define NUM_LEDS    1
#define BRIGHTNESS  35          // 亮度 0~255，建议 50~150 之间，太亮刺眼

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// HSV 转 RGB，hue: 0~360, sat: 0~255, val: 0~255
uint32_t hsvToRgb(uint16_t hue, uint8_t sat, uint8_t val) {
    uint8_t r, g, b;
    uint8_t region, remainder, p, q, t;
    
    if (sat == 0) {
        r = g = b = val;
    } else {
        region = hue / 60;
        remainder = (hue % 60) * 255 / 60;
        
        p = (val * (255 - sat)) >> 8;
        q = (val * (255 - ((sat * remainder) >> 8))) >> 8;
        t = (val * (255 - ((sat * (255 - remainder)) >> 8))) >> 8;
        
        switch (region) {
            case 0: r = val; g = t; b = p; break;
            case 1: r = q; g = val; b = p; break;
            case 2: r = p; g = val; b = t; break;
            case 3: r = p; g = q; b = val; break;
            case 4: r = t; g = p; b = val; break;
            default: r = val; g = p; b = q; break;
        }
    }
    return strip.Color(r, g, b);
}

void setup() {
    strip.begin();
    strip.setBrightness(BRIGHTNESS);
    strip.show(); // 初始熄灭
}
/*
void loop() {
    static uint16_t hue = 0;          // 色相 0~360
    static unsigned long lastTime = 0;
    const unsigned long interval = 20; // 每 20ms 变化一次，控制渐变速度
    
    if (millis() - lastTime >= interval) {
        lastTime = millis();
        
        // 根据当前色相计算 RGB 并设置 LED
        uint32_t color = hsvToRgb(hue, 255, BRIGHTNESS); // 饱和度、亮度均最大，最终亮度由 setBrightness 控制
        strip.setPixelColor(0, color);
        strip.show();
        
        // 色相递增，实现平滑渐变
        hue++;
        if (hue >= 360) hue = 0;
    }
}
*/