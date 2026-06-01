/* * BLIPBOX-V35 
 * Version: 2026-06-01-V9
 * Strategie: Gamepad-Emulation (HID Gamepad - Korrigierte Methode)
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
      
      // Gamepad-Report erstellen: Button 1 aktiv
      // Die Methode 'send' erwartet eine Struktur mit x, y, z, rz, rx, ry, hatHat, buttons
      blehid.send(0, 0, 0, 0, 0, 0, 0, 1);
      delay(100);
      
      // Report mit "keine Buttons gedrückt" senden (Loslassen)
      blehid.send(0, 0, 0, 0, 0, 0, 0, 0);
      
      delay(500); 
    }
  }
  delay(100);
}
