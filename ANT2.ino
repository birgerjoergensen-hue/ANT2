// =================================================================
// PROJEKT: Blipbox v4 - VERSION: Birger DIY 37
// =================================================================

#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// LAUT DIAGRAMM GENAU DIE UNTEREN LINKEN PINS:
const int ANT1 = 9;   // Label D9 (Hardware P1.06) -> Sendet 'A'
const int ANT2 = 8;   // Label D8 (Hardware P1.04) -> Sendet Scroll-Down
const int ANT3 = 16;  // Reserve
const int ANT4 = 10;  // Label D10 (Hardware P0.09) -> Ganz unten rechts

const int MY_LED_RED  = 15; 
const int MY_LED_BLUE = 17;

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
  digitalWrite(MY_LED_BLUE, LOW); 
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
  digitalWrite(MY_LED_BLUE, HIGH); 
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

  pinMode(MY_LED_RED, OUTPUT);
  pinMode(MY_LED_BLUE, OUTPUT);
  digitalWrite(MY_LED_RED, HIGH);
  digitalWrite(MY_LED_BLUE, HIGH);

  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  
  Bluefruit.Security.setIOCaps(false, false, false); 
  Bluefruit.Security.setMITM(false);

  // IMMER WEITERGEZÄHLT: Version 37
  Bluefruit.setName("Birger DIY 37");

  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);
  Bluefruit.Security.setPairCompleteCallback(pairing_complete_callback);
  Bluefruit.Security.setSecuredCallback(connection_secured_callback);

  bledis.setManufacturer("GEMMI Tech");
  bledis.setModel("Blipbox v4");
  bledis.begin();

  blehid.begin();

  startAdv();
  
  digitalWrite(MY_LED_RED, LOW);
}

void loop() {
  // Überbrücke den Pin ganz unten links (D9) gegen GND -> tippt ein 'A'
  if (digitalRead(ANT1) == LOW) {
    tapKey(HID_KEY_A); 
    waitForRelease(ANT1);
  }

  // Überbrücke den Pin direkt darüber (D8) gegen GND -> Scrollt nach unten
  if (digitalRead(ANT2) == LOW) {
    tapKey(HID_KEY_ARROW_DOWN);   
    waitForRelease(ANT2);
  }

  delay(10);
}
