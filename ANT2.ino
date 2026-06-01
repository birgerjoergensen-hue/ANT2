/* * BLIPBOX-V35 
 * Version: 2026-06-01-V2
 * HID-Test-Modus (5s Intervall)
 */

#include <bluefruit.h>

// Globale HID-Objekte
BLEDis       bledis;
BLEHidAdafruit blehid;

void setup() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("BLIPBOX-HID-TEST");

  // Geräteinfo für das Pairing
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Blipbox V35");
  bledis.begin();

  // HID-Dienst initialisieren
  blehid.begin();

  // Advertising-Einstellungen für ein HID-Gerät
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  
  // Wiederverbinden ermöglichen
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.start(0);
}

void loop() {
  if (Bluefruit.connected()) {
    // 0x4B ist Page Down, 0 ist der Modifier (Shift/Ctrl etc.)
    // Die Signatur blehid.keyPress(keycode, modifier) ist hier zwingend
    blehid.keyPress(0x4B, 0); 
    delay(100);
    blehid.keyRelease();
    
    // Warte 5 Sekunden bis zum nächsten "Tastendruck"
    delay(5000); 
  }
  delay(100);
}
