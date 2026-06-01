#include <Arduino.h>

void setup() {
  // Pin-Definitionen für Feather nRF52840 Sense
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  // Status: System startet
  digitalWrite(LED_BLUE, LOW);  // BLE aus
  digitalWrite(LED_RED, HIGH);  // Rot an als Lebenszeichen
  delay(1000);
  digitalWrite(LED_RED, LOW);
}

void loop() {
  // Minimaler Loop, um den Prozessor aktiv zu halten
  __WFI(); 
}
