// =================================================================
// PROJEKT: Blipbox v4 - VERSION: Birger DIY 38
// =================================================================

#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// Wir definieren ein Array aus Pins für die linke Platinenseite
const int BUCHSTABE_PINS[] = {6, 8, 9};   // Alle unteren linken Pins (D6, D8, D9)
const int SCROLL_PINS[]    = {2, 3, 4};   // Alle oberen linken Pins (D2, D3, D4)

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

void tapKey(uint8_t keycode) {
  if (!Bluefruit.connected()) {
    return;
  }
  blehid.keyPress(keycode);
  delay(50);
  blehid.keyRelease();
}

void setup() {
  // Alle Test-Pins als INPUT_PULLUP konfigurieren
  for (int i = 0; i < 3; i++) {
    pinMode(BUCHSTABE_PINS[i], INPUT_PULLUP);
    pinMode(SCROLL_PINS[i], INPUT_PULLUP);
  }

  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  
  Bluefruit.Security.setIOCaps(false, false, false); 
  Bluefruit.Security.setMITM(false);

  // NAME HOCHGEZÄHLT: Version 38
  Bluefruit.setName("Birger DIY 38");

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
  // 1. Prüfen, ob IRGENDEINER der unteren linken Pins gegen GND gezogen wird
  for (int i = 0; i < 3; i++) {
    if (digitalRead(BUCHSTABE_PINS[i]) == LOW) {
      tapKey(HID_KEY_A); // Sendet ein 'A'
      while (digitalRead(BUCHSTABE_PINS[i]) == LOW) { delay(10); } // Warten auf Loslassen
    }
  }

  // 2. Prüfen, ob IRGENDEINER der oberen linken Pins gegen GND gezogen wird
  for (int i = 0; i < 3; i++) {
    if (digitalRead(SCROLL_PINS[i]) == LOW) {
      tapKey(HID_KEY_ARROW_DOWN); // Scrollt nach unten
      while (digitalRead(SCROLL_PINS[i]) == LOW) { delay(10); } // Warten auf Loslassen
    }
  }

  delay(10);
}
