#include <bluefruit.h>

BLEService        hrms = BLEService(UUID16_SVC_HEART_RATE);
BLECharacteristic hrmc = BLECharacteristic(UUID16_CHR_HEART_RATE_MEASUREMENT);

// P1.06 ist auf dem Feather Board oft als "D9" markiert. 
// Die sicherste Methode ist es, das Pin-Mapping über die Arduino-Konstante zu versuchen.
// Wenn das nicht geht, nutzen wir die direkte ID.
#define BUTTON_PIN 11 

void setup() {
  // Wir nutzen INPUT_PULLUP, damit der Taster gegen Masse schaltet
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
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
    // Falls der Taster nicht reagiert, ist er vielleicht "active high" statt "active low"
    // Wir testen hier: Wenn Pin LOW, dann 100 BPM
    int sensorState = digitalRead(BUTTON_PIN);
    
    uint8_t hrValue = (sensorState == LOW) ? 0x64 : 0x3C;
    uint8_t hrmData[] = {0x00, hrValue}; 
    hrmc.notify(hrmData, sizeof(hrmData));
  }
  delay(200);
}
