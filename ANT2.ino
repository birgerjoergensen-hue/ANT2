// =================================================================
// PROJEKT: Birger DIY 31v04 (Rad-Sensor Profil)
// =================================================================
#include <bluefruit.h>

BLEDis bledis;
BLECSCS blecsc; // Cycling Speed & Cadence Profil

void setup() {
  Bluefruit.begin();
  
  bledis.setManufacturer("Birger");
  bledis.setModel("ANT-Bridge");
  bledis.begin();

  blecsc.begin();
  
  Bluefruit.setName("Birger DIY 31v04");
  
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(blecsc);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Wir senden keine Daten, nur das Profil-Signal
  delay(1000);
}
