// =================================================================
// PROJEKT: Blipbox v4 - VERSION: Birger DIY 39
// =================================================================

#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

unsigned long lastSendTime = 0;

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
  Bluefruit.Advertising.setInterval(16, 112); // Schnellere Intervalle für stabilere Übertragung
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

// Optimierte Sende-Funktion, die dem Handy explizit sagt: "Taste gedrückt UND losgelassen!"
void sendAutopilotKey() {
  if (!Bluefruit.connected()) {
    return;
  }
  
  // Wir nutzen keySequence, das feuert den Buchstaben garantiert sofort ab
  blehid.keySequence("a"); 
}

void setup() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  
  Bluefruit.Security.setIOCaps(false, false, false); 
  Bluefruit.Security.setMITM(false);

  // NAME HOCHGEZÄHLT: Version 39
  Bluefruit.setName("Birger DIY 39");

  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);
  Bluefruit.Security.setPairCompleteCallback(pairing_complete_callback);
  Bluefruit.Security.setSecuredCallback(connection_secured_callback);

  bledis.setManufacturer("GEMMI Tech");
  bledis.setModel("Blipbox v4");
  bledis.begin();

  blehid.begin();

  startAdv();
  
  lastSendTime = millis();
}

void loop() {
  // AUTOPILOT: Jede 5 Sekunden (5000 Millisekunden) wird stur ein "A" gesendet
  if (millis() - lastSendTime >= 5000) {
    sendAutopilotKey();
    lastSendTime = millis();
  }

  delay(10);
}
