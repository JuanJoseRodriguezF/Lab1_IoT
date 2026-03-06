#include <Arduino.h>

const int adcPin = 34;
const int buttonPin = 18;

bool adcEnabled = false;
bool lastButtonState = HIGH;


void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {

  bool buttonState = digitalRead(buttonPin) == LOW;

  if(buttonState == LOW && lastButtonState == HIGH){
    adcEnabled = !adcEnabled;   // cambiar estado
    delay(200); // debounce simple
  }

  lastButtonState = buttonState;

  if(adcEnabled){
    int value = analogRead(adcPin);
    Serial.print(">value:");
    Serial.println(value);
    Serial.print("habilitado, valor: ");
    Serial.println(value);
  }
  else{
    Serial.println("ADC deshabilitado");
  }
  delay(100);
}
