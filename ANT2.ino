/* * BLIPBOX-V35 
 * Version: 2026-06-01-V8
 * Strategie: Gamepad-Emulation (HID Gamepad)
 */

#include <bluefruit.h>

BLEDis       bledis;
BLEHidGamepad blehid;

void setup() {
  Bluefruit.begin();
  Bluefruit.setName("BLIPBOX-REMOTE");

  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Blipbox V35");
  bledis.begin();

  blehid.begin();

  // Pin definieren
  pinMode(NRF_GPIO_PIN_MAP(1, 6), INPUT_PULLUP);

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  // Appearance 0x0540 = Gamepad
  Bluefruit.Advertising.addAppearance(0x0540); 
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.start(0);
}

void loop() {
  if (Bluefruit.connected()) {
    // Wenn Taster gedrückt (LOW)
    if (digitalRead(NRF_GPIO_PIN_MAP(1, 6)) == LOW) {
      // Button 1 drücken
      blehid.buttonPress(1);
      delay(100);
      blehid.buttonRelease();
      
      delay(500); // Entprellen
    }
  }
  delay(100);
}
