#include <Arduino.h>
#include <U8g2lib.h>

void setup(){
  Serial.begin(1150200);
  pinMode(1, OUTPUT);
  pinMode(2, INPUT);
  digitalWrite(1, HIGH);
}
void loop(){
  delay(1000);
  digitalWrite(1, !digitalRead(1));
  Serial.println("1");
}