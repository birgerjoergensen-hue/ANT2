#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// Definition deiner 4 Knöpfe laut Plan
const int ANT1 = 9;   // Pin D9  (unten links)
const int ANT2 = 10;  // Pin D10 (unten rechts)
const int ANT3 = 16;  // Pin D16 (über ANT2, rechts)
const int ANT4 = 8;   // Pin D8  (über ANT1, links)

// Eigene Namen für die nice!nano v2 LEDs
const int MY_LED_RED  = 15;
const int MY_LED_BLUE = 17;

// Timer-Variablen für das LED-Blinken
unsigned long previousMillis = 0;
const long blinkInterval = 300;
bool ledState = HIGH;

// -----------------------------
// Hilfsfunktionen
// -----------------------------
void startAdv()
{
  Bluefruit.Advertising.stop();

  Bluefruit.Advertising.clearData();
  Bluefruit.ScanResponse.clearData();

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);

  // Name lieber in ScanResponse, damit das Advertising-Paket nicht zu voll wird
  Bluefruit.ScanResponse.addName();

  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);

  // 0 = dauerhaft advertisieren bis verbunden
  Bluefruit.Advertising.start(0);
}

void tapKey(uint8_t keycode)
{
