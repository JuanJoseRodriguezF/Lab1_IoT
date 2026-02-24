#define BUTTON_PIN 4
#define RELAY_PIN 18

bool relayState = false;
bool lastButtonState = HIGH;

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, HIGH); // Relé apagado (si es activo LOW)
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW && lastButtonState == HIGH) {
    delay(50); // Antirrebote
    relayState = !relayState;
    digitalWrite(RELAY_PIN, relayState ? HIGH : LOW );
    Serial.println(relayState ? "RELE ACTIVADO" : "RELE DESACTIVADO");
  }

  lastButtonState = buttonState;
}
