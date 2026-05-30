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
  // Falls noch nicht verbunden: erst wieder advertisieren
  if (!Bluefruit.connected()) {
    if (!Bluefruit.Advertising.isRunning()) {
      startAdv();
    }
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
// Setup
// -----------------------------
void setup()
{
  pinMode(ANT1, INPUT_PULLUP);
  pinMode(ANT2, INPUT_PULLUP);
  pinMode(ANT3, INPUT_PULLUP);
  pinMode(ANT4, INPUT_PULLUP);

  pinMode(MY_LED_RED, OUTPUT);
  pinMode(MY_LED_BLUE, OUTPUT);

  // LEDs erstmal aus (bei vielen nRF-Boards sind LEDs active-low)
  digitalWrite(MY_LED_RED, HIGH);
  digitalWrite(MY_LED_BLUE, HIGH);

  Bluefruit.begin();
  Bluefruit.setTxPower(4);

  // Just Works Pairing: kein Display, keine Tastatur, kein PIN
  Bluefruit.Security.setIOCaps(false, false, false);

  // Gerätename +1 hochgezählt
  Bluefruit.setName("Birger DIY 10");

  bledis.setManufacturer("GEMMI Tech");
  bledis.setModel("Blipbox v4");
  bledis.begin();

  // HID-Tastatur starten
  blehid.begin();

  // Advertising starten
  startAdv();
}

// -----------------------------
// Loop
// -----------------------------
void loop()
{
  unsigned long currentMillis = millis();

  // --- LED BLINK-LOGIK ---
  if (Bluefruit.Advertising.isRunning() && !Bluefruit.connected()) {
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      ledState = !ledState;
      digitalWrite(MY_LED_RED, ledState);
    }
  } else {
    // LED aus wenn verbunden oder nicht am advertisieren
    digitalWrite(MY_LED_RED, HIGH);
  }

  // --- KNOPF-ABFRAGEN ---

  // ANT1 (D9) -> Pfeiltaste Links
  if (digitalRead(ANT1) == LOW) {
    tapKey(HID_KEY_ARROW_LEFT);
    waitForRelease(ANT1);
  }

  // ANT2 (D10) -> Pfeiltaste Rechts
  if (digitalRead(ANT2) == LOW) {
    tapKey(HID_KEY_ARROW_RIGHT);
    waitForRelease(ANT2);
  }

  // ANT3 (D16) -> optional: Pfeiltaste Hoch
  if (digitalRead(ANT3) == LOW) {
    tapKey(HID_KEY_ARROW_UP);
    waitForRelease(ANT3);
  }

  // ANT4 (D8) -> optional: Pfeiltaste Runter
  if (digitalRead(ANT4) == LOW) {
    tapKey(HID_KEY_ARROW_DOWN);
    waitForRelease(ANT4);
  }

  delay(10);
}
