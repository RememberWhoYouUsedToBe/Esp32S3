#include <Arduino.h>

int Note = 0;

void setup(){
    Serial.begin(115200);
    delay(3000);
    Serial.println("Hello_World");
}

void loop(){
    Serial.println(Note);
    delay(1000);
    Note ++;
}