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
  Bluefruit.Advertising.addName();

  Bluefruit.Advertising.restartOnDisconnect(true);
