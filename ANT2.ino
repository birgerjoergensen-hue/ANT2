// ==========================================
// DEINE VERSIONIERUNG (Nur noch hier ändern!)
// ==========================================
String versionsNummer = "31v22"; 
// ==========================================

#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

void setup() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4); // Volle Sendeleistung
  
  String kompletterName = "GEMMI_" + versionsNummer;
  Bluefruit.setName(kompletterName.c_str());
  
  bledis.setManufacturer("GEMMI DIY");
  bledis.setModel("Blipbox");
  bledis.begin();

  blehid.begin();
  
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  
  // HIER DER FIX FÜR COROS: Cycling Remote Control (0x0443) statt Tastatur
  Bluefruit.Advertising.addAppearance(0x0443); 
  
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.setInterval(32, 244); 
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

void loop() {
  if (Bluefruit.connected()) {
    // Lautstärke-Test bleibt aktiv für Handy/PC Gegenprobe
    blehid.consumerKeyPress(HID_USAGE_CONSUMER_VOLUME_INCREMENT);
    delay(100);
    blehid.consumerKeyRelease();
    
    delay(5000);
  }
}
