/* * BLIPBOX-V35 
 * Version: 2026-06-01-V5
 * Strategie: ANT+ Schaltungs-Emulation (SRAM AXS)
 */

#include <bluefruit.h>
#include "ant_plus.h" // Die ANT+ Bibliothek der Adafruit-Plattform

// Wir emulieren einen Schalt-Sender
// SRAM AXS Device ID ist meist 12345 (kann frei gewählt werden)
#define SHIFT_DEVICE_ID 12345 
#define SHIFT_DEVICE_TYPE 0x05 // Typ 0x05 ist Shifting (Schaltung)

void setup() {
  Bluefruit.begin();
  
  // ANT+ initialisieren
  AntPlus.begin();
  
  // Taster auf deinem bewährten Pin
  pinMode(NRF_GPIO_PIN_MAP(1, 6), INPUT_PULLUP);
}

void loop() {
  // ANT+ läuft zyklisch. Wir senden ein Status-Paket.
  // 0x00 = Status, 0x01 = Schalten
  static uint8_t shift_state = 0;

  if (digitalRead(NRF_GPIO_PIN_MAP(1, 6)) == LOW) {
    shift_state = 1; // "Schaltbefehl" aktiv
    delay(200);      // Entprellen
  } else {
    shift_state = 0; // Leerlauf
  }

  // ANT+ Übertragung: Wir senden den Status als Shifting-Event
  // Das ist das Format, das SRAM AXS Geräte nutzen
  AntPlus.send_shifting_data(shift_state); 
  
  delay(100);
}
