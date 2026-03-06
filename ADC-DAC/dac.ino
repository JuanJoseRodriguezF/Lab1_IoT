#include <Arduino.h>

const int adcPin = 34;   // potenciómetro
const int dacPin = 25;   // DAC del ESP32
const int buttonPin = 18;

bool enabled = false;
bool lastButtonState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {

  bool buttonState = digitalRead(buttonPin) == LOW;

  if(buttonState == LOW && lastButtonState == HIGH){
    enabled = !enabled;   // cambiar estado
    delay(200); // debounce simple
  }

  lastButtonState = buttonState;

  if(enabled){
    // Leer ADC (12 bits)
    int adcValue = analogRead(adcPin);

    // Escalar a 8 bits
    int dacValue = adcValue / 16;

    // Escribir en el DAC
    dacWrite(dacPin, dacValue);

    Serial.print(">value:");
    Serial.println(dacValue);

    Serial.printf("ADC: %d  |  DAC: %d\n", adcValue, dacValue);

  }else{
    Serial.println("ADC deshabilitado");
  }

  delay(50);
}
