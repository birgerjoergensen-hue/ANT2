#include <bluefruit.h>

BLEService        hrms = BLEService(UUID16_SVC_HEART_RATE);
BLECharacteristic hrmc = BLECharacteristic(UUID16_CHR_HEART_RATE_MEASUREMENT);

// P1.06 entspricht beim Feather nRF52840 Sense der Pin-Nummer 11
const int buttonPin = 11; 

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  
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
    // 100 BPM (0x64) bei Tastendruck, 60 BPM (0x3C) im Leerlauf
    uint8_t hrValue = (digitalRead(buttonPin) == LOW) ? 0x64 : 0x3C;
    uint8_t hrmData[] = {0x00, hrValue}; 
    hrmc.notify(hrmData, sizeof(hrmData));
  }
  delay(200);
}
