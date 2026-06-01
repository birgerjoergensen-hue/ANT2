/* * BLIPBOX-V35 
 * Version: 2026-06-01-V1 
 * BLE-E-Bike-Steuerung für Coros Dura
 */

#include <bluefruit.h>

BLEService        ebs = BLEService(0x183C); 
BLECharacteristic ebc = BLECharacteristic(0x2B56); 

void setup() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("E-BIKE-STEPS");

  ebs.begin();
  ebc.setProperties(CHR_PROPS_NOTIFY | CHR_PROPS_WRITE);
  ebc.setFixedLen(2);
  ebc.begin();

  // Physikalische Pin-Map für Feather nRF52840 Sense
  pinMode(NRF_GPIO_PIN_MAP(1, 6), INPUT_PULLUP);

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(0x044C); 
  Bluefruit.Advertising.addService(ebs);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.start(0);
}

void loop() {
  if (Bluefruit.connected()) {
    // Wenn Taster gedrückt: Sende expliziten "Schalt"-Befehl
    if (digitalRead(NRF_GPIO_PIN_MAP(1, 6)) == HIGH) {
      uint8_t commandData[] = {0x01, 0x01}; 
      ebc.notify(commandData, sizeof(commandData));
      delay(500); // Verzögerung, um den Coros nicht zu fluten
    }
  }
  delay(100);
}
