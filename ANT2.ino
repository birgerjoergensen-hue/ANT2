#include <bluefruit.h>

// Offizieller BLE Service für E-Bikes (Environmental/Data Control oder Custom Steps)
// Wir nutzen eine standardisierte 16-Bit-UUID für Steuerungen, die Shimano/Coros nutzen
BLEService        ebs = BLEService(0x183C); // Light Data / E-Bike Control Service
BLECharacteristic ebc = BLECharacteristic(0x2B56); // Control Point Characteristic

void setup() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("E-BIKE-STEPS");

  ebs.begin();
  ebc.setProperties(CHR_PROPS_NOTIFY | CHR_PROPS_WRITE);
  ebc.setFixedLen(2); // 2 Bytes für Befehle
  ebc.begin();

  pinMode(NRF_GPIO_PIN_MAP(1, 6), INPUT_PULLUP);

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  
  // 0x044C = E-Bike Typkennung
  Bluefruit.Advertising.addAppearance(0x044C); 
  
  Bluefruit.Advertising.addService(ebs);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.start(0);
}

void loop() {
  if (Bluefruit.connected()) {
    // Byte 0 = Modus, Byte 1 = Zustand (0x00 = Leerlauf)
    uint8_t commandData[] = {0x00, 0x00}; 

    // Wenn der Taster gedrückt wird (LOW)
    if (digitalRead(NRF_GPIO_PIN_MAP(1, 6)) == LOW) {
      // 0x01 und 0x02 simulieren in der Regel "Unterstützung HOCH" (Assist Level Up)
      // Viele Tachos nutzen genau dieses Signal, um die Trainingsseite nach oben zu blättern
      commandData[0] = 0x01; 
      commandData[1] = 0x02; 
      ebc.notify(commandData, sizeof(commandData));
      delay(300); // Entprellen, damit er nur eine Seite blättert
    } else {
      // Wenn nicht gedrückt, senden wir den "Losgelassen"-Status
      ebc.notify(commandData, sizeof(commandData));
    }
  }
  delay(100);
}
