#include <Arduino.h>

const int adcPin = 34;

void setup() {
  Serial.begin(115200);
}

void loop() {

  int value = analogRead(adcPin);
  
  Serial.print(">value:");
  Serial.println(value);
  delay(100);
}
