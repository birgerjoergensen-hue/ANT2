#include <bluefruit.h>

BLEDis bledis;
BLEHeartRate blehr; 

void setup() {
  Bluefruit.begin();
  
  // Identität
  bledis.setManufacturer("Birger");
  bledis.setModel("ANT-Bridge");
  bledis.begin();

  // Herzfrequenz-Profil (HRM) - Das ist der "Universal-Türöffner" für Radcomputer
  blehr.begin();
  
  Bluefruit.setName("Birger_31v09");
  
  // Wichtig für Coros/Handy: Explizites Advertising
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(blehr);
  Bluefruit.Advertising.addName();
  
  // Schnellere Wiederholung für bessere Erkennung
  Bluefruit.Advertising.setInterval(32, 244); 
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Simuliere einen Herzschlag von 80 BPM, damit das Gerät "aktiv" wirkt
  blehr.notify(80);
  delay(1000);
}
