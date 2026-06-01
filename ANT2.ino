#include <bluefruit.h>

// Offizielle Bluetooth-UUIDs für elektronische Schaltungen
BLEService        shs = BLEService(0x183A); 
BLECharacteristic shc = BLECharacteristic(0x2B3A);

void setup() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("BLIPBOX-AXS"); // Name angepasst, damit der Coros "Schaltung" assoziiert

  // Schaltungs-Service aufsetzen
  shs.begin();
  shc.setProperties(CHR_PROPS_NOTIFY);
  shc.setFixedLen(4); // Typischer Schaltungsstatus (4 Bytes)
  shc.begin();

  // Deinen Taster als Eingang definieren
  pinMode(NRF_GPIO_PIN_MAP(1, 6), INPUT_PULLUP);

  // Dem Coros signalisieren, dass wir eine Schaltung (Cycling Shifting) sind
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  
  // 0x0440 ist die offizielle "Appearance" für Rad-Sensoren/Schaltungen
  Bluefruit.Advertising.addAppearance(0x0440); 
  
  Bluefruit.Advertising.addService(shs);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.start(0);
}

void loop() {
  if (Bluefruit.connected()) {
    // Standard-Status-Bytes für eine Schaltung im Leerlauf
    // Byte 0: Anzahl Gänge hinten, Byte 1: Aktueller Gang, etc.
    uint8_t gearData[] = {0x0B, 0x05, 0x02, 0x01}; 

    // Wenn der Taster gedrückt wird (LOW), simulieren wir einen Schaltvorgang (z.B. Gangwechsel)
    if (digitalRead(NRF_GPIO_PIN_MAP(1, 6)) == LOW) {
      gearData[1] = 0x06; // Ändere den aktuellen Gang auf 6
      shc.notify(gearData, sizeof(gearData));
      delay(200); // Entprellen
    } else {
      shc.notify(gearData, sizeof(gearData));
    }
  }
  delay(250);
}
