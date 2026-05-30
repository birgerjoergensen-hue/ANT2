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

  // Startet die HID-Bibliothek (beinhaltet Keyboard und Consumer Control)
  blehid.begin();

  // Advertising (Funkbarke) einrichten
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  
  // Universelle HID-Kennung, die in dieser Library-Version existiert
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_GENERIC_HID);
  Bluefruit.Advertising.addService(blehid);
  
  Bluefruit.Advertising.addName();
  
  // Schnelles Senden für zügiges Pairing
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); 
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0); 
}

void loop() {
  // ANT1 (D9) -> "Vorheriger Titel" (Wahoo blättert Seite zurück)
  if (digitalRead(ANT1) == LOW) {
    blehid.consumerKeyPress(HID_USAGE_CONSUMER_SCAN_PREVIOUS);
    delay(50); // Entprellen
    blehid.consumerKeyRelease();
    while (digitalRead(ANT1) == LOW) { delay(10); } // Warten bis losgelassen
  }

  // ANT2 (D10) -> "Nächster Titel" (Wahoo blättert Seite vor)
  if (digitalRead(ANT2) == LOW) {
    blehid.consumerKeyPress(HID_USAGE_CONSUMER_SCAN_NEXT);
    delay(50);
    blehid.consumerKeyRelease();
    while (digitalRead(ANT2) == LOW) { delay(10); }
  }

  // ANT3 (D16) & ANT4 (D8) halten wir sauber im Hintergrund bereit
  if (digitalRead(ANT3) == LOW) {
    // Platzhalter für spätere Belegung
    while (digitalRead(ANT3) == LOW) { delay(10); }
  }

  if (digitalRead(ANT4) == LOW) {
    // Platzhalter für spätere Belegung
    while (digitalRead(ANT4) == LOW) { delay(10); }
  }

  delay(10); // Stromsparen
}
