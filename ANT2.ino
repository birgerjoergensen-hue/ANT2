#include <Arduino.h>

void setup() {
  // Wir nutzen die Namen, die das Board von Haus aus kennt
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  // Blaue LED (BLE-Status) hart auf LOW
  digitalWrite(LED_BLUE, LOW);
  
  // Rote LED (System-Status) kurz an
  digitalWrite(LED_RED, HIGH);
  delay(1000);
  digitalWrite(LED_RED, LOW);
}

void loop() {
  // Warteschleife
  __WFI(); 
}
