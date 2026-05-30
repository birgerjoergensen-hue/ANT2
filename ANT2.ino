// =================================================================
// PROJEKT: Blipbox v4 - VERSION: Birger DIY 42 (Mit LED-Feedback)
// =================================================================

#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

#define PIN_P1_06 (32 + 6)  // Entspricht D9 (unten links)
#define PIN_P1_04 (32 + 4)  // Entspricht D8 (direkt darüber)

// Die rote LED deiner nice!nano v2
const int MY_LED_RED = 15;  

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
  pinMode(PIN_P1_06, INPUT_PULLUP);
  pinMode(PIN_P1_04, INPUT_PULLUP);

  // LED initialisieren und ausschalten (HIGH = Aus bei der nice!nano)
  pinMode(MY_LED_RED, OUTPUT);
  digitalWrite(MY_LED_RED, HIGH);

  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  
  Bluefruit.Security.setIOCaps(false, false, false); 
  Bluefruit.Security.setMITM(false);

  // NEUER NAME: Version 42
  Bluefruit.setName("Birger DIY 42");

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
  // D9 (P1.06) -> Sendet das 'A'
  if (digitalRead(PIN_P1_06) == LOW) {
    digitalWrite(MY_LED_RED, LOW); // Rote LED AN
    
    blehid.keyPress(HID_KEY_A);
    delay(50);
    blehid.keyRelease();
    delay(200); 
    
    while (digitalRead(PIN_P1_06) == LOW) { delay(10); } // Warten, bis Kontakt gelöst ist
    
    digitalWrite(MY_LED_RED, HIGH); // Rote LED wieder AUS
  }

  // D8 (P1.04) -> Sendet Scrollen
  if (digitalRead(PIN_P1_04) == LOW) {
    digitalWrite(MY_LED_RED, LOW); // Rote LED AN
    
    blehid.keyPress(HID_KEY_ARROW_DOWN);
    delay(50);
    blehid.keyRelease();
    delay(200);
    
    while (digitalRead(PIN_P1_04) == LOW) { delay(10); } // Warten, bis Kontakt gelöst ist
    
    digitalWrite(MY_LED_RED, HIGH); // Rote LED wieder AUS
  }

  delay(10);
}
