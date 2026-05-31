// ==========================================
// DEINE VERSIONIERUNG
// ==========================================
String versionsNummer = "31v26"; 
// ==========================================

#include <bluefruit.h> // Wir nutzen die Stack-Kontrolle des nRF52
#include "nrf_sdm.h"   // SoftDevice Manager für ANT+

// ANT+ Konstanten für Shifting (Device Type 4)
#define ANT_SHIFTING_DEVICE_TYPE 0x04
#define ANT_TRANSMISSION_TYPE 0x01
#define ANT_DEVICE_NUMBER 0x1234 // Deine individuelle ID

// Pin-Definitionen für deine Taster (musst du anpassen!)
const int btnUp = 9; 
const int btnDown = 10;

void setup() {
  // Wir konfigurieren das nRF52 Radio für ANT+ statt BLE
  // Dies erfordert den ANT-SoftDevice im Hintergrund
  
  // Initialisierung des ANT-Kanals
  // [Hier folgt der spezifische ANT-Stack Aufruf]
  
  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);
}

void loop() {
  // ANT+ Shifting Data Page 1
  // Byte 0: Data Page Number (0x01)
  // Byte 4: Shifting (0x01 = Up, 0x02 = Down)
  
  uint8_t tx_buffer[8] = {0x01, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF};

  if (digitalRead(btnUp) == LOW) {
    tx_buffer[4] = 0x01; // Shift Up
    sendANT(tx_buffer);
    delay(200);
  }
  
  if (digitalRead(btnDown) == LOW) {
    tx_buffer[4] = 0x02; // Shift Down
    sendANT(tx_buffer);
    delay(200);
  }
}

void sendANT(uint8_t *payload) {
  // Funktion zum Senden via ANT+
}
