/* * BLIPBOX-V35 
 * Version: 2026-06-01-V12
 * Strategie: Zurück zum stabilen Keyboard-Profil (HID)
 */

#include <bluefruit.h>

BLEDis       bledis;
BLEHidAdafruit blehid;

void setup() {
  Bluefruit.begin();
  // Name so gewählt, dass er als Gerät erkannt wird
  Bluefruit.setName("BLIPBOX-V35");

  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Blipbox V35");
  bledis.begin();

  blehid.begin();

  pinMode(NRF_GPIO_PIN_MAP(1, 6), INPUT_PULLUP);

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.start(0);
}

void loop() {
  if (Bluefruit.connected()) {
    if (digitalRead(NRF_GPIO_PIN_MAP(1, 6)) == LOW) {
      
      // Anstatt Page Down senden wir "Enter" (0x28). 
      // Viele Radcomputer nutzen Enter/Select als Bestätigung oder Seitenwechsel
      blehid.keyPress(0x28, 0); 
      delay(50);
      blehid.keyRelease();
      
      delay(1000); // Längere Pause
    }
  }
  delay(100);
}
