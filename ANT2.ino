#include <bluefruit.h>

// Wir nutzen die CPS (Cycling Power Service) UUID, die oft für E-Bikes/Trainer genutzt wird
BLEService        ebs = BLEService(0x1818); 
BLECharacteristic ebc = BLECharacteristic(0x2A63); // Cycling Power Measurement

void setup() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("E-BIKE-STEPS"); // Wir tarnen uns als Shimano Steps System

  ebs.begin();
  ebc.setProperties(CHR_PROPS_NOTIFY);
  ebc.setFixedLen(4);
  ebc.begin();

  pinMode(NRF_GPIO_PIN_MAP(1, 6), INPUT_PULLUP);

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  
  // Appearance 0x044C steht für E-Bike / Power Sensor
  Bluefruit.Advertising.addAppearance(0x044C); 
  
  Bluefruit.Advertising.addService(ebs);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.start(0);
}

void loop() {
  if (Bluefruit.connected()) {
    // Dummy-Leistungsdaten (80 Watt im Leerlauf)
    uint8_t powerData[] = {0x00, 0x00, 0x50, 0x00}; 

    // Wenn der Taster gedrückt wird, simulieren wir eine Änderung (z.B. "Unterstützungsstufe hoch" via Leistungssprung)
    if (digitalRead(NRF_GPIO_PIN_MAP(1, 6)) == LOW) {
      powerData[2] = 0xC8; // Sprung auf 200 Watt / Signal
      ebc.notify(powerData, sizeof(powerData));
      delay(200);
    } else {
      ebc.notify(powerData, sizeof(powerData));
    }
  }
  delay(250);
}
