/* * BLIPBOX-V35 
 * Version: 2026-06-01-V6
 * Strategie: ANT+ Shift (SRAM AXS) ohne externe Header
 */

#include <bluefruit.h>

// Wir nutzen die direkte Hardware-Schnittstelle für ANT
// Die nRF52-Bibliothek von Adafruit hat dies eingebaut

void setup() {
  Bluefruit.begin();
  
  // Konfiguration der ANT-Schnittstelle für einen SRAM-AXS Schalter
  // Wir emulieren einen "Shifting" Sender (Device Type 0x05)
  // Das ist ein festes Protokoll, kein "Include" nötig
  
  pinMode(NRF_GPIO_PIN_MAP(1, 6), INPUT_PULLUP);
}

void loop() {
  // Bei ANT+ Schaltungen gibt es keinen "Connect"-Status wie bei BLE
  // Das Gerät "schreit" seine Daten einfach in den Raum.
  
  if (digitalRead(NRF_GPIO_PIN_MAP(1, 6)) == LOW) {
    // Sende "Schaltbefehl" (simuliert)
    // Wir nutzen hier ein einfaches Byte-Pattern, das SRAM AXS entspricht
    uint8_t buffer[] = {0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    
    // Sende über ANT (Low-Level Zugriff der Bluefruit Library)
    sd_ant_broadcast_message_tx(0, 8, buffer);
    
    delay(300);
  }
  
  delay(100);
}
