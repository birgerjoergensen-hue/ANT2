/* * BLIPBOX-V35 
 * Version: 2026-06-01-V10
 * Strategie: HID Gamepad mit korrekter Methode: gamepadReport
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

  pinMode(NRF_GPIO_PIN_MAP(1, 6), INPUT_PULLUP);

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(0x0540); 
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.start(0);
}

void loop() {
  if (Bluefruit.connected()) {
    if (digitalRead(NRF_GPIO_PIN_MAP(1, 6)) == LOW) {
      
      // Korrekt: gamepadReport nimmt die Struktur entgegen
      hid_gamepad_report_t report = {
        .x = 0, .y = 0, .z = 0, .rz = 0, .rx = 0, .ry = 0,
        .hat = 0, .buttons = 1
      };
      blehid.gamepadReport(&report);
      delay(100);
      
      // Report mit Buttons = 0 senden
      report.buttons = 0;
      blehid.gamepadReport(&report);
      
      delay(500); 
    }
  }
  delay(100);
}
