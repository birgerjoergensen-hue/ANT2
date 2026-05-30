#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// Definition deiner 4 Knöpfe laut Plan
const int ANT1 = 9;  // Pin D9  (unten links)
const int ANT2 = 10; // Pin D10 (unten rechts)
const int ANT3 = 16; // Pin D16 (über ANT2, rechts)
const int ANT4 = 8;  // Pin D8  (über ANT1, links)

// Eigene Namen für die nice!nano v2 LEDs
const int MY_LED_RED  = 15; 
const int MY_LED_BLUE = 17;

// Timer-Variablen für das LED-Blinken
unsigned long previousMillis = 0;
const long blinkInterval = 300; 
bool ledState = HIGH;           

void setup() {
  pinMode(ANT1, INPUT_PULLUP);
  pinMode(ANT2, INPUT_PULLUP);
  pinMode(ANT3, INPUT_PULLUP);
  pinMode(ANT4, INPUT_PULLUP);

  pinMode(MY_LED_RED, OUTPUT);
  pinMode(MY_LED_BLUE, OUTPUT);
  digitalWrite(MY_LED_RED, HIGH);
  digitalWrite(MY_LED_BLUE, HIGH);

  // Wichtig: TinyUSB vor dem Bluetooth-Start initialisieren
  TinyUSBDevice.begin();

  Bluefruit.begin();
  Bluefruit.setTxPower(4); 

  // NAME ERHÖHT: Verhindert, dass alte Cache-Leichen die Erkennung blockieren
  Bluefruit.setName("Birger DIY 03");

  bledis.setManufacturer("GEMMI Tech");
  bledis.setModel("Blipbox v4");
  bledis.begin();

  // Schaltet das HID-Protokoll (Tastatur) sauber frei
  blehid.begin();

  // Advertising einrichten
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); 

  // 120 Sekunden Sendezeit beim Start
  Bluefruit.Advertising.start(120); 
}

void loop() {
  unsigned long currentMillis = millis();

  // --- LED BLINK-LOGIK ---
  if (Bluefruit.Advertising.isRunning() && !Bluefruit.connected()) {
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      ledState = !ledState; 
      digitalWrite(MY_LED_RED, ledState); 
    }
  } else {
    digitalWrite(MY_LED_RED, HIGH); 
  }

  // --- KNOPF-ABFRAGEN MIT DETEKTIERBAREN SIGNALEN ---

  // ANT1 (D9) -> Pfeiltaste Links
  if (digitalRead(ANT1) == LOW) {
    if (!Bluefruit.Advertising.isRunning()) { Bluefruit.Advertising.start(5); } 
    blehid.keyPress(HID_KEY_ARROW_LEFT);
    delay(50); // Entprellen
    blehid.keyRelease();
    while (digitalRead(ANT1) == LOW) { delay(10); } 
  }

  // ANT2 (D10) -> Pfeiltaste Rechts
  if (digitalRead(ANT2) == LOW) {
    if (!Bluefruit.Advertising.isRunning()) { Bluefruit.Advertising.start(5); }
    blehid.keyPress(HID_KEY_ARROW_RIGHT);
    delay(50);
    blehid.keyRelease();
    while (digitalRead(ANT2) == LOW) { delay(10); }
  }

  // ANT3 (D16) - Bereit gehalten
  if (digitalRead(ANT3) == LOW) {
    while (digitalRead(ANT3) == LOW) { delay(10); }
  }

  // ANT4 (D8) - Bereit gehalten
  if (digitalRead(ANT4) == LOW) {
    while (digitalRead(ANT4) == LOW) { delay(10); }
  }

  delay(10); 
}
