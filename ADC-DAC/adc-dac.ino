#include <Arduino.h>

const int adcPin = 34;      
const int dacPin = 25;      
const int adcOutpin = 35;   
const int buttonPin = 18;

float phase = 0;

int waveType = 0; // 0=seno, 1=cuadrada, 2=triangular
bool lastButtonState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {

  // detectar presión del botón
  bool buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && lastButtonState == HIGH) {
    waveType++;
    if (waveType > 2) waveType = 0;
  }

  lastButtonState = buttonState;

  // leer potenciómetro
  int adcValue = analogRead(adcPin);

  // convertir a amplitud (0–127)
  float amplitude = (adcValue / 4095.0) * 127;

  // avanzar fase
  phase += 0.1;

  if (phase > 2 * PI) {
    phase -= 2 * PI;
  }

  float signal = 0;

  // seleccionar tipo de onda
  if (waveType == 0) {
    // seno
    signal = sin(phase);
  }

  else if (waveType == 1) {
    // cuadrada
    signal = (sin(phase) >= 0) ? 1 : -1;
  }

  else if (waveType == 2) {
    // triangular
    signal = (2.0 / PI) * asin(sin(phase));
  }

  int dacValue = 128 + amplitude * signal;

  dacWrite(dacPin, dacValue);

  int adcOutput = analogRead(adcOutpin);

  Serial.print(">adcValue:");
  Serial.println(adcOutput);

  Serial.print(">dacValue:");
  Serial.println(dacValue);

  Serial.printf(
    "Pot: %d | Amplitud: %.2f | DAC: %d | ADC salida: %d\n",
    adcValue,
    amplitude,
    dacValue,
    adcOutput
  );

  delay(5);
}
