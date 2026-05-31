// =================================================================
// PROJEKT: Birger DIY 31v05 (Fix für Sensor-Profil)
// =================================================================
#include <bluefruit.h>

BLEDis bledis;
BLECscs blecsc; // Die Klasse schreibt sich BLECscs (C für Cycling, s für Speed, c für Cadence, s für Service)

void setup() {
  Bluefruit.begin();
  
  bledis.setManufacturer("Birger");
  bledis.setModel("ANT-Bridge");
  bledis.begin();

  // Initialisiere den Cycling Speed & Cadence Service
  blecsc.begin();
  
  Bluefruit.setName("Birger DIY 31v05");
  
  // Advertising
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(blecsc);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  delay(1000);
}
