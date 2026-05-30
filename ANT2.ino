// =================================================================
// PROJEKT: Birger DIY 47 (Koppel-Fix: HID-Mode erzwungen)
// =================================================================
#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

void setup() {
  Bluefruit.begin();
  
  // WICHTIG: Identität als Tastatur festlegen, damit keine App-Anfrage kommt
  Bluefruit.setAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  bledis.setManufacturer("GEMMI");
  bledis.setModel("Blipbox");
  bledis.begin();

  blehid.begin();
  
  Bluefruit.setName("Birger DIY 47");
  
  // Advertising-Einstellungen für Standard-HID-Koppelung
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.start(0);
}

void loop() {
  delay(100);
}
