// =================================================================
// PROJEKT: Birger DIY 46 (Hard-Reset für Pairing)
// =================================================================
#include <bluefruit.h>

void setup() {
  // Bluetooth löschen und neu starten
  Bluefruit.begin();
  Bluefruit.setName("Birger DIY 46");
  
  // Advertising-Einstellungen für maximale Sichtbarkeit
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.setInterval(160, 160); // 100ms Intervall = sehr schnell sichtbar
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Leerlauf, damit Bluetooth-Stack 100% Energie für das Advertising hat
  delay(100);
}
