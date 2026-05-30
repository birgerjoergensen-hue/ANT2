// =================================================================
// PROJEKT: Blipbox v4 - VERSION: Birger DIY 41
// =================================================================

#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// Wir nutzen im Setup KEINE festen Port-1-Zahlen mehr, um den Boot-Konflikt zu lösen.
// Die Zuweisung erfolgt sauber über die Standard-Makros D8 und D9 im loop.

void startAdv(void) {
  Bluefruit.Advertising.stop();
  Bluefruit.Advertising.clearData();
  Bluefruit.ScanResponse.clearData();

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();

  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0); 
}

void pairing_complete_callback(uint16_t conn_handle, uint8_t auth_status) {
  (void) conn_handle;
  (void) auth_status;
}

void connection_secured_callback(uint16_t conn_handle) {
  (void) conn_handle;
}

void connect_callback(uint16_t conn_handle) {
  BLEConnection* connection = Bluefruit.Connection(conn_handle);
  if (connection != NULL) {
    if (!connection->secured()) {
      connection->requestPairing();
    }
  }
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason) {
  (void) conn_handle;
  (void) reason;
  startAdv();
}

void setup() {
  // Initialisiere die Pins über die sicheren Arduino-Bezeichnungen
  pinMode(D9, INPUT_PULLUP);
  pinMode(D8, INPUT_PULLUP);

  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  
  // No-PIN-Security Modus für schnellen Handshake
  Bluefruit.Security.setIOCaps(false, false, false); 
  Bluefruit.Security.setMITM(false);

  // NAME ERHÖHT: Version 41 (Frischer Koppel-Versuch)
  Bluefruit.setName("Birger DIY 41");

  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);
  Bluefruit.Security.setPairCompleteCallback(pairing_complete_callback);
  Bluefruit.Security.setSecuredCallback(connection_secured_callback);

  bledis.setManufacturer("GEMMI Tech");
  bledis.setModel("Blipbox v4");
  bledis.begin();

  blehid.begin();

  startAdv();
}

void loop() {
  // Unten links: D9 (Hardware P1.06) -> Sendet das 'A'
  if (digitalRead(D9) == LOW) {
    blehid.keySequence("a"); 
    delay(100);
    while (digitalRead(D9) == LOW) { delay(10); }
  }

  // Direkt darüber: D8 (Hardware P1.04) -> Sendet Scrollen
  if (digitalRead(D8) == LOW) {
    blehid.keyPress(HID_KEY_ARROW_DOWN);
    delay(50);
    blehid.keyRelease();
    delay(100);
    while (digitalRead(D8) == LOW) { delay(10); }
  }

  delay(10);
}
