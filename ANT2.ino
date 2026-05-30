// =================================================================
// PROJEKT: Birger DIY 60 (Minimal-Sichtbarkeit)
// =================================================================
#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

void setup() {
  Bluefruit.begin();
  
  // Setze Basis-Informationen
  bledis.setManufacturer("Birger");
  bledis.setModel("DIY");
  bledis.begin();

  blehid.begin();
  
  // Advertising: Maximale Kompatibilität
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Kein Code hier, nur Sichtbarkeit
  delay(1000);
}
