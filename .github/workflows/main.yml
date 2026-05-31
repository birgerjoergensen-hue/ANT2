#include <bluefruit.h>

BLEDis bledis;
BLEHrm blehrm; // Profil für Herzfrequenz-Sensor

void setup() {
  Bluefruit.begin();
  
  // Ich habe die Versionierung für dich übernommen:
  Bluefruit.setName("GEMMI_31v10");
  
  bledis.setManufacturer("GEMMI DIY");
  bledis.setModel("ANT-Bridge");
  bledis.begin();

  blehrm.begin();
  
  // Sichtbarkeit für das Coros Dura (als Sensor)
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(blehrm);
  Bluefruit.Advertising.addName();
  
  // Schnelles Senden für den Suchmodus
  Bluefruit.Advertising.setInterval(32, 244); 
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Simulierter Puls von 80 BPM
  blehrm.measure(80); 
  delay(1000);
}
