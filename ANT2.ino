#include <bluefruit.h>

BLEService        hrms = BLEService(UUID16_SVC_HEART_RATE);
BLECharacteristic hrmc = BLECharacteristic(UUID16_CHR_HEART_RATE_MEASUREMENT);

// Wir nutzen die direkte Port-Referenz für das Feather Sense P1.06
// In der Adafruit-Bibliothek für nRF52840 ist Pin 9 oft als '9' definiert, 
// aber P1.06 ist spezifisch. Wir probieren '9' als direkte ID.
const int buttonPin = 9; 

void setup() {
  // Wir probieren INPUT statt INPUT_PULLUP, falls dein Taster extern gepullt ist
  pinMode(buttonPin, INPUT);
  
  Bluefruit.begin();
  Bluefruit.setName("BLIPBOX-V35");
  
  hrms.begin();
  hrmc.setProperties(CHR_PROPS_NOTIFY);
  hrmc.setFixedLen(2);
  hrmc.begin();

  Bluefruit.Advertising.addService(hrms);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  if (Bluefruit.connected()) {
    // Debug: Wir lesen den Zustand und setzen 100 bei HIGH oder LOW
    // Wenn er immer 60 bleibt, ändern wir den Vergleich
    int state = digitalRead(buttonPin);
    
    // Wenn state HIGH ist, sende 100, sonst 60 (oder umgekehrt)
    uint8_t hrValue = (state == HIGH) ? 0x64 : 0x3C; 
    uint8_t hrmData[] = {0x00, hrValue}; 
    hrmc.notify(hrmData, sizeof(hrmData));
  }
  delay(200);
}
