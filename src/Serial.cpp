#include <Arduino.h>

void setup(){
    Serial.begin(115200);
    while (!Serial);
    delay(2000);    // 等待2秒，让电脑和监视器完成连接
    Serial.println("Hello_World");
}

void loop(){
    Serial.println("ESP32");
    delay(1000);

}