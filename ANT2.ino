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

void startAdv(void)
{
  Bluefruit.Advertising.stop();
  Bluefruit.Advertising.clearData();
  Bluefruit.ScanResponse.clearData();

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);

  // Name direkt im Advertising-Paket
  Bluefruit.Advertising.addName();

  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

void connect_callback(uint16_t conn_handle)
{
  (void) conn_handle;
  digitalWrite(MY_LED_RED, HIGH);   // aus
  digitalWrite(MY_LED_BLUE, LOW);   // an
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;

  digitalWrite(MY_LED_BLUE, HIGH);  // aus
  startAdv();
}

void tapKey(uint8_t keycode)
{
  if (!Bluefruit.connected()) return;

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

void setup()
{
  pinMode(ANT1, INPUT_PULLUP);
