// =================================================================
// PROJEKT: Blipbox v4 - VERSION: Birger DIY 29
// =================================================================

#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

const int ANT1 = 9;
const int ANT2 = 10;
const int ANT3 = 16;
const int ANT4 = 8;

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

void waitForRelease(int pin) {
  while (digitalRead(pin) == LOW) {
    delay(10);
  }
}

void setup() {
  pinMode(ANT1, INPUT_PULLUP);
  pinMode(ANT2, INPUT_PULLUP);
  pinMode(ANT3, INPUT_PULLUP);
  pinMode(ANT4, INPUT_PULLUP);

  // --- DIE RADIKALKUR FÜR VERSION 29 (REPARIERT) ---
  // Initialisiert das interne Dateisystem und formatiert es.
  // Das löscht alle alten Verschlüsselungs-Dateien (Bonds) physisch vom Chip!
  InternalFileSys.begin();
  InternalFileSys.format();

  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  
  // Die 3 Schalter für deine Library-Version
  Bluefruit.Security.setIOCaps(false, false, false); 
  Bluefruit.Security.setMITM(false);

  // NAME ERHÖHT: Version 29
  Bluefruit.setName("Birger DIY 29");

  // Callbacks registrieren
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
  if (digitalRead(ANT1) == LOW) {
    tapKey(HID_KEY_ARROW_LEFT);
    waitForRelease(ANT1);
  }

  if (digitalRead(ANT2) == LOW) {
    tapKey(HID_KEY_ARROW_RIGHT);
    waitForRelease(ANT2);
  }

  if (digitalRead(ANT3) == LOW) {
    waitForRelease(ANT3);
  }

  if (digitalRead(ANT4) == LOW) {
    waitForRelease(ANT4);
  }

  delay(10);
}
