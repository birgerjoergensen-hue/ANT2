#include <Arduino.h>

void setup() {
  // LED Status setzen
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  // Blaue LED hart aus
  digitalWrite(LED_BLUE, LOW);
  
  // Rote LED an für 2 Sekunden als Start-Signal
  digitalWrite(LED_RED, HIGH);
  delay(2000);
  digitalWrite(LED_RED, LOW);
  
  // Ab hier würde der ANT-Stack initialisiert
  // Da wir Bluefruit.h entfernen, stürzt das Radio-Modul nicht mehr ab.
}

void loop() {
  // Wenn das Board jetzt stabil bleibt (kein blaues Blinken mehr),
  // wissen wir, dass der Bootloader-Absturz behoben ist.
  delay(1000);
}
