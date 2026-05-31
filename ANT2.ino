// =================================================================
// PROJEKT: Birger DIY 31v06 (Universeller Batterie-Sensor)
// =================================================================
#include <bluefruit.h>

BLEDis bledis;
BLEBas blebas; // Battery Service

void setup() {
  Bluefruit.begin();
  
  // Wir simulieren ein Gerät, das einen Akkustand meldet
  bledis.setManufacturer("Birger");
  bledis.setModel("ANT-Bridge");
  bledis.begin();

  blebas.begin();
  blebas.write(95); // Sende 95% Akkustand
  
  Bluefruit.setName("Birger DIY 31v06");
  
  // Advertising
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(blebas);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  delay(1000);
}
