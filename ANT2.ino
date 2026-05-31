#include <Arduino.h>

// Wir verzichten auf #include <bluefruit.h>, um BLE-Konflikte zu vermeiden.
// Wir steuern die Hardware direkt über die Register des nRF52.

void setup() {
  // Status-LEDs initialisieren
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  // Blaue LED (BLE-Status) hart auf LOW (Aus)
  digitalWrite(LED_BLUE, LOW);
  
  // Rote LED (System-Status) kurz an, um Lebenszeichen zu geben
  digitalWrite(LED_RED, HIGH);
  delay(1000);
  digitalWrite(LED_RED, LOW);
}

void loop() {
  // Hier passiert zur Zeit nur die Warteschleife.
  // Das Board sendet in diesem Zustand (hoffentlich) kein BLE-Signal mehr.
  delay(1000);
}
