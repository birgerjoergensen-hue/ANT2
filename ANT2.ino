#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// Taster
const int ANT1 = 9;
const int ANT2 = 10;
const int ANT3 = 16;
const int ANT4 = 8;

// LEDs
const int MY_LED_RED  = 15;
const int MY_LED_BLUE = 17;

unsigned long previousMillis = 0;
const long blinkInterval = 300;
bool ledState = HIGH;

uint16_t activeConnHandle = BLE_CONN_HANDLE_INVALID;

// -----------------------------
// Forward Declarations
// -----------------------------
void startAdv(void);
void connect_callback(uint16_t conn_handle);
void disconnect_callback(uint16_t conn_handle, uint8_t reason);
void pairing_complete_callback(uint16_t conn_handle, uint8_t auth_status);
void connection_secured_callback(uint16_t conn_handle);

// -----------------------------
// Helper
// -----------------------------
void startAdv(void)
{
  Bluefruit.Advertising.stop();
  Bluefruit.Advertising.clearData();
  Bluefruit.ScanResponse.clearData();

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);

  // Name direkt im Advertising, nicht nur in ScanResponse
  Bluefruit.Advertising.addName();

  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);

  // Dauerhaft advertisieren bis verbunden
  Bluefruit.Advertising.start(0);

  Serial.println("Advertising gestartet");
}

void tapKey(uint8_t keycode)
{
  if (!Bluefruit.connected()) {
    Serial.println("Nicht verbunden -> sende keine Taste");
    return;
  }

  blehid.keyPress(keycode);
  delay(50);
  blehid.keyRelease();
}

void waitForRelease(int pin)
{
  while (digitalRead(pin) == LOW) {
    delay(10);
  }
}

// -----------------------------
// Callbacks
// -----------------------------
void connect_callback(uint16_t conn_handle)
{
  activeConnHandle = conn_handle;

  BLEConnection* connection = Bluefruit.Connection(conn_handle);

  char peer_name[32] = {0};
  connection->getPeerName(peer_name, sizeof(peer_name));

  Serial.print("Verbunden mit: ");
  Serial.println(peer_name[0] ? peer_name : "(unbekannt)");

  // Rot aus, Blau an/aus erst nach 'secured'
  digitalWrite(MY_LED_RED, HIGH);

  // Falls noch nicht gesichert, Pairing anfordern
  if (!connection->secured()) {
    Serial.println("Verbindung noch nicht secured -> requestPairing()");
    connection->requestPairing();
  }
}

void pairing_complete_callback(uint16_t conn_handle, uint8_t auth_status)
{
  Serial.print("Pairing abgeschlossen, Status: 0x");
  Serial.println(auth_status, HEX);

  if (auth_status == BLE_GAP_SEC_STATUS_SUCCESS) {
    Serial.println("Pairing erfolgreich");
  } else {
    Serial.println("Pairing fehlgeschlagen");
  }
}

void connection_secured_callback(uint16_t conn_handle)
{
  (void) conn_handle;
  Serial.println("Verbindung ist jetzt SECURED");

  // Blau an = secured/verbunden
  digitalWrite(MY_LED_BLUE, LOW);
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;

  activeConnHandle = BLE_CONN_HANDLE_INVALID;

  Serial.println();
  Serial.print("Disconnected, reason = 0x");
  Serial.println(reason, HEX);

  // Blau aus
  digitalWrite(MY_LED_BLUE, HIGH);

  // Advertising explizit neu starten
  startAdv();
}

// -----------------------------
// Setup
// -----------------------------
void setup()
{
  Serial.begin(115200);
  delay(200);

  pinMode(ANT1, INPUT_PULLUP);
  pinMode(ANT2, INPUT_PULLUP);
  pinMode(ANT3, INPUT_PULLUP);
  pinMode(ANT4, INPUT_PULLUP);

  pinMode(MY_LED_RED, OUTPUT);
  pinMode(MY_LED_BLUE, OUTPUT);

  // Viele nRF-Board-LEDs sind active-low
  digitalWrite(MY_LED_RED, HIGH);   // aus
  digitalWrite(MY_LED_BLUE, HIGH);  // aus

  // Optional, oft stabiler bei Peripherals
  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);

  Bluefruit.begin();
  Bluefruit.setTxPower(4);

  // Kein Display/Keypad = Just Works
  Bluefruit.Security.setIOCaps(false, false, false);
  Bluefruit.Security.setPairCompleteCallback(pairing_complete_callback);
  Bluefruit.Security.setSecuredCallback(connection_secured_callback);

  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  Bluefruit.setName("Birger DIY 12");

  bledis.setManufacturer("GEMMI Tech");
  bledis.setModel("Blipbox v4");
  bledis.begin();

  blehid.begin();

  Serial.println("BLE HID gestartet");
  startAdv();
}

// -----------------------------
// Loop
// -----------------------------
void loop()
{
  unsigned long currentMillis = millis();

  // Rot blinkt beim Advertising solange nicht verbunden
  if (Bluefruit.Advertising.isRunning() && !Bluefruit.connected()) {
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(MY_LED_RED, ledState);
    }
  } else {
    digitalWrite(MY_LED_RED, HIGH); // aus
  }

  if (digitalRead(ANT1) == LOW) {
    tapKey(HID_KEY_ARROW_LEFT);
    waitForRelease(ANT1);
  }

  if (digitalRead(ANT2) == LOW) {
    tapKey(HID_KEY_ARROW_RIGHT);
    waitForRelease(ANT2);
  }

  if (digitalRead(ANT3) == LOW) {
    tapKey(HID_KEY_ARROW_UP);
    waitForRelease(ANT3);
  }

  if (digitalRead(ANT4) == LOW) {
    tapKey(HID_KEY_ARROW_DOWN);
    waitForRelease(ANT4);
  }

  delay(10);
}
