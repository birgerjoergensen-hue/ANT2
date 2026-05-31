#include <bluefruit.h>

void setup() {
  // 1. Bootloader-Zeitfenster sofort beenden
  // Der nRF52840 Bootloader wartet oft 5-10 Sekunden.
  // Wir sagen dem System, dass es den BLE-Stack gar nicht erst laden soll.
  
  // LED Status
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_BLUE, LOW);  // Blau aus erzwingen
  digitalWrite(LED_RED, HIGH);  // Rot an = Wir sind im Code
  
  // ANT+ Stack Initialisierung (nur der Grundaufbau)
  // Wir nutzen hier keine Bluefruit-BLE-Funktionen mehr!
}

void loop() {
  // Wenn die blaue LED an der Powerbank immer noch blinkt,
  // ist das ein Zeichen, dass der Bootloader auf einem Tastendruck wartet.
  delay(1000);
}
