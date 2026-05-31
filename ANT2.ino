#include <bluefruit.h>

void setup() {
  // Starte Bluetooth
  Bluefruit.begin();
  
  // Setze einen eindeutigen Namen, den du sofort wiedererkennst
  Bluefruit.setName("Birger_31v08");
  
  // Advertising starten (Broadcast-Modus)
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Nichts tun, einfach nur sichtbar bleiben
  delay(1000);
}
