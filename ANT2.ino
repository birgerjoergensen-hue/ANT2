#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// Definition deiner 4 Knöpfe laut Plan
const int ANT1 = 9;  // Pin D9  (unten links)
const int ANT2 = 10; // Pin D10 (unten rechts)
const int ANT3 = 16; // Pin D16 (über ANT2, rechts)
const int ANT4 = 8;  // Pin D8  (über ANT1, links)

void setup() {
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
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_GENERIC_HID);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); // Schnelle Intervalle für flinkes Pairing

  // JETZT GANZ EINFACH: Bei jedem Start/Reset 120 Sekunden dauerhaft senden!
  // Danach schaltet sich das Funkmodul von alleine ab, um Batterie zu sparen.
  Bluefruit.Advertising.start(120); 
}

void loop() {
  // ANT1 (D9) -> Weckt Funk bei Bedarf kurz auf und schickt "Seite zurück"
  if (digitalRead(ANT1) == LOW) {
    // Falls der Timer abgelaufen ist, für 5 Sekunden Funk einschalten
    if (!Bluefruit.Advertising.isRunning()) { Bluefruit.Advertising.start(5); } 
    blehid.consumerKeyPress(HID_USAGE_CONSUMER_SCAN_PREVIOUS);
    delay(50); // Entprellen
    blehid.consumerKeyRelease();
    while (digitalRead(ANT1) == LOW) { delay(10); } // Warten bis losgelassen
  }

  // ANT2 (D10) -> Weckt Funk bei Bedarf kurz auf und schickt "Seite vor"
  if (digitalRead(ANT2) == LOW) {
    if (!Bluefruit.Advertising.isRunning()) { Bluefruit.Advertising.start(5); }
    blehid.consumerKeyPress(HID_USAGE_CONSUMER_SCAN_NEXT);
    delay(50);
    blehid.consumerKeyRelease();
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

  // Generelles Stromsparen im Loop (100ms Schlafpause)
  delay(100); 
}
