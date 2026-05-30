#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

const int BUTTON_LEFT = 9;   // Pin D9 (unten links)
const int BUTTON_RIGHT = 10; // Pin D10 (unten rechts)

void setup() {
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);

  Bluefruit.begin();
  Bluefruit.setTxPower(4); // Maximale Sendeleistung

  // Dein neuer Wunschname im Bluetooth-Netzwerk
  Bluefruit.setName("Birgers DIY");

  bledis.setManufacturer("GEMMI Tech");
  bledis.setModel("Blipbox v4");
  bledis.begin();

  blehid.begin();

  // Advertising (Funkbarke) einrichten
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  
  // Wir nutzen die offizielle Fernbedienungs-Kennung (HID Remote), die Wahoos lieber mögen
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_REMOTE);
  Bluefruit.Advertising.addService(blehid);
  
  Bluefruit.Advertising.addName();
  
  // Verbindungseinstellungen optimieren
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); 
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0); 
}

void loop() {
  // Linker Knopf (D9) -> Simuliert "Pfeil nach links" (Seitenwechsel zurück)
  if (digitalRead(BUTTON_LEFT) == LOW) {
    blehid.keyPress(HID_KEY_ARROW_LEFT);
    delay(50); // Entprellen
    blehid.keyRelease();
    while (digitalRead(BUTTON_LEFT) == LOW) { delay(10); } // Warten bis losgelassen
  }

  // Rechter Knopf (D10) -> Simuliert "Pfeil nach rechts" (Seitenwechsel vor)
  if (digitalRead(BUTTON_RIGHT) == LOW) {
    blehid.keyPress(HID_KEY_ARROW_RIGHT);
    delay(50);
    blehid.keyRelease();
    while (digitalRead(BUTTON_RIGHT) == LOW) { delay(10); }
  }

  delay(10); // Stromsparen
}
