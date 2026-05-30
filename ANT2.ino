#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// Definition deiner 4 Knöpfe laut Plan
const int ANT1 = 9;  // Pin D9  (unten links)
const int ANT2 = 10; // Pin D10 (unten rechts)
const int ANT3 = 16; // Pin D16 (über ANT2, rechts)
const int ANT4 = 8;  // Pin D8  (über ANT1, links)

bool usbConnected = false;

void setup() {
  pinMode(ANT1, INPUT_PULLUP);
  pinMode(ANT2, INPUT_PULLUP);
  pinMode(ANT3, INPUT_PULLUP);
  pinMode(ANT4, INPUT_PULLUP);

  Bluefruit.begin();
  Bluefruit.setTxPower(4); 

  Bluefruit.setName("Birgers DIY");

  bledis.setManufacturer("GEMMI Tech");
  bledis.setModel("Blipbox v4");
  bledis.begin();

  blehid.begin();

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_GENERIC_HID);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); 

  // Saubere Abfrage über die TinyUSB-Bibliothek
  if (TinyUSBDevice.ready()) {
    usbConnected = true;
    Bluefruit.Advertising.start(0); // Dauer-Senden EIN am Kabel (Kein Brücken nötig!)
  } else {
    usbConnected = false; // Stromsparen EIN (Warten auf Tastendruck an Batterie)
  }
}

void loop() {
  // Überwachung der USB-Quelle im laufenden Betrieb
  if (usbConnected && !TinyUSBDevice.ready()) {
    usbConnected = false;
    Bluefruit.Advertising.stop(); // Kabel gezogen -> Stromsparen an
  }
  if (!usbConnected && TinyUSBDevice.ready()) {
    usbConnected = true;
    Bluefruit.Advertising.start(0); // Kabel eingesteckt -> Dauer-Funk an
  }

  // ANT1 (D9) -> Weckt Funk bei Batterie kurz auf und schickt "Seite zurück"
  if (digitalRead(ANT1) == LOW) {
    if (!usbConnected) { Bluefruit.Advertising.start(5); } 
    blehid.consumerKeyPress(HID_USAGE_CONSUMER_SCAN_PREVIOUS);
    delay(50);
    blehid.consumerKeyRelease();
    while (digitalRead(ANT1) == LOW) { delay(10); }
  }

  // ANT2 (D10) -> Weckt Funk bei Batterie kurz auf und schickt "Seite vor"
  if (digitalRead(ANT2) == LOW) {
    if (!usbConnected) { Bluefruit.Advertising.start(5); }
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

  // Taktung je nach Stromquelle
  if (!usbConnected) {
    delay(100); // Tiefschlaf auf Batterie (extrem stromsparend)
  } else {
    delay(10);  // Schnelle Reaktion am USB-Kabel
  }
}
