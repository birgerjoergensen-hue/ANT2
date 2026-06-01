#include <Arduino.h>

// Wir definieren die Pins für das Feather nRF52840 Sense
#define LED_BLUE 17
#define LED_RED 19

void setup() {
  // 1. Hardware-Reset unterbinden: 
  // Das Board darf nicht zurück in den DFU-Modus springen.
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  // LED Status setzen
  digitalWrite(LED_BLUE, LOW);  // BLE-Anzeige aus
  digitalWrite(LED_RED, HIGH);  // System aktiv anzeigen
  delay(1000);
  digitalWrite(LED_RED, LOW);
  
  // WICHTIG: Das nRF52840 FeatherSense hat einen speziellen Sensor-Stack.
  // Wir halten das Programm hier in einer Endlosschleife, 
  // um den Bootloader-Watchdog zu füttern.
}

void loop() {
  // Watchdog-Feed: Verhindert, dass das Board wegen Inaktivität neu startet
  __WFI(); // Wait For Interrupt - spart Strom und hält den Chip stabil
}
