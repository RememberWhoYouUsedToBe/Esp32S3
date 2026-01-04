#include <Arduino.h>
#include <U8g2lib.h>

void LED();  // 函数声明

void setup(){
  Serial.begin(115200);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  digitalWrite(1, HIGH);
}
void loop(){
  delay(1000);
  LED();
  Serial.println("1");
  
}

void LED() {
    // 定义亮的时间数组（毫秒）
    int onTimes[] = {1000, 1000, 500, 500, 500, 500};
    int offTime = 100;  // 每次灭的时间固定为 100ms

    // 循环次数 = 数组元素个数
    for (int i = 0; i < 6; i++) {
        digitalWrite(1, HIGH);
        delay(onTimes[i]);   // 亮 onTimes[i] 毫秒
        digitalWrite(1, LOW);
        delay(offTime);      // 灭 offTime 毫秒
    }
}