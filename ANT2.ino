#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// Taster
const int ANT1 = 9;
const int ANT2 = 10;
const int ANT3 = 16;
const int ANT4 = 8;

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
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

void connect_callback(uint16_t conn_handle)
{
  (void) conn_handle;
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
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
  while (digitalRead(pin) == LOW)
  {
    delay(10);
  }
}

void setup()
{
  pinMode(ANT1, INPUT_PULLUP);
  pinMode(ANT2, INPUT_PULLUP);
  pinMode(ANT3, INPUT_PULLUP);
  pinMode(ANT4, INPUT_PULLUP);

  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("Birger DIY 15");

  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  bledis.setManufacturer("GEMMI Tech");
  bledis.setModel("Blipbox v4");
  bledis.begin();

  blehid.begin();

  startAdv();
}

void loop()
{
  if (digitalRead(ANT1) == LOW)
  {
    tapKey(HID_KEY_ARROW_LEFT);
