// =================================================================
// PROJEKT: Birger DIY 67 (Der ultimative Handy-Kompatibilitäts-Test)
// =================================================================
#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

void setup() {
  Bluefruit.begin();
  
  // Setze den Namen neu
  Bluefruit.setName("Birger DIY 31.01");
  
  // HID-Profil initialisieren
  blehid.begin();
  
  // WICHTIG: Advertising so einstellen, dass es IMMER sichtbar bleibt
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Wir machen hier nichts, damit der Bluetooth-Stack 
  // alle Ressourcen für die Sichtbarkeit hat.
  delay(1000);
}
