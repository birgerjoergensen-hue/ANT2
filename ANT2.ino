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

void startAdv()
{
  Bluefruit.Advertising.stop();
  Bluefruit.Advertising.clearData();
  Bluefruit.ScanResponse.clearData();

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);

  // WICHTIG: Name direkt ins Advertising-Paket
  Bluefruit.Advertising.addName();

  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);

  // Dauerhaft sichtbar bis verbunden
  Bluefruit.Advertising.start(0);
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
  pinMode(ANT2, INPUT_PULLUP);
  pinMode(ANT3, INPUT_PULLUP);
  pinMode(ANT4, INPUT_PULLUP);

  pinMode(MY_LED_RED, OUTPUT);
  pinMode(MY_LED_BLUE, OUTPUT);

  digitalWrite(MY_LED_RED, HIGH);
  digitalWrite(MY_LED_BLUE, HIGH);

  Bluefruit.begin();
  Bluefruit.setTxPower(4);

  // Just Works
  Bluefruit.Security.setIOCaps(false, false, false);

  // Name +1 hochgezählt
  Bluefruit.setName("Birger DIY 11");

  bledis.setManufacturer("GEMMI Tech");
  bledis.setModel("Blipbox v4");
  bledis.begin();

  blehid.begin();

  startAdv();
}

void loop()
{
  unsigned long currentMillis = millis();

  // Blinkt während Advertising, solange nicht verbunden
  if (Bluefruit.Advertising.isRunning() && !Bluefruit.connected()) {
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(MY_LED_RED, ledState);
    }
  } else {
    digitalWrite(MY_LED_RED, HIGH);
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
