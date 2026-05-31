// =================================================================
// PROJEKT: Birger DIY 31v02 (Laptop-Sichtbarkeits-Optimierung)
// =================================================================
#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

void setup() {
  Bluefruit.begin();
  
  // Wir geben dem Gerät einen offiziellen Charakter
  bledis.setManufacturer("Birger DIY");
  bledis.setModel("ANT-Bridge");
  bledis.begin();

  blehid.begin();
  
  Bluefruit.setName("Birger DIY 31v02");
  
  // Advertising-Einstellungen für maximale Kompatibilität
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  delay(1000);
}
