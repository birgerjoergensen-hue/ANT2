#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// Definition der 4 Knöpfe laut deinem Plan
const int ANT1 = 9;  // Pin D9  (unten links)
const int ANT2 = 10; // Pin D10 (unten rechts)
const int ANT3 = 16; // Pin D16 (über ANT2, rechts)
const int ANT4 = 8;  // Pin D8  (über ANT1, links)

void setup() {
  // Alle 4 Pins als Eingang mit internem Pull-Up-Widerstand aktivieren
  pinMode(ANT1, INPUT_PULLUP);
  pinMode(ANT2, INPUT_PULLUP);
  pinMode(ANT3, INPUT_PULLUP);
  pinMode(ANT4, INPUT_PULLUP);

  Bluefruit.begin();
  Bluefruit.setTxPower(4); // Maximale Sendeleistung

  // Dein Wunschname im Bluetooth-Netzwerk
  Bluefruit.setName("Birgers DIY");

  bledis.setManufacturer("GEMMI Tech");
  bledis.setModel("Blipbox v4");
  bledis.begin();

  blehid.begin();

  // Advertising (Funkbarke) einrichten
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);
  
  Bluefruit.Advertising.addName();
  
  // Verbindungseinstellungen für schnelle Entdeckung
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); 
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0); 
}

void loop() {
  // KNOPF 1: ANT1 (D9) -> Pfeil nach links
  if (digitalRead(ANT1) == LOW) {
    blehid.keyPress(HID_KEY_ARROW_LEFT);
    delay(50); // Entprellen
    blehid.keyRelease();
    while (digitalRead(ANT1) == LOW) { delay(10); } // Warten bis losgelassen
  }

  // KNOPF 2: ANT2 (D10) -> Pfeil nach rechts
  if (digitalRead(ANT2) == LOW) {
    blehid.keyPress(HID_KEY_ARROW_RIGHT);
    delay(50);
    blehid.keyRelease();
    while (digitalRead(ANT2) == LOW) { delay(10); }
  }

  // KNOPF 3: ANT3 (D16) -> Pfeil nach oben
  if (digitalRead(ANT3) == LOW) {
    blehid.keyPress(HID_KEY_ARROW_UP);
    delay(50);
    blehid.keyRelease();
    while (digitalRead(ANT3) == LOW) { delay(10); }
  }

  // KNOPF 4: ANT4 (D8) -> Pfeil nach unten
  if (digitalRead(ANT4) == LOW) {
    blehid.keyPress(HID_KEY_ARROW_DOWN);
    delay(50);
    blehid.keyRelease();
    while (digitalRead(ANT4) == LOW) { delay(10); }
  }

  delay(10); // Stromsparen im Loop
}
