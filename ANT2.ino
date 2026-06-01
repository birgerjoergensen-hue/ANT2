#include <bluefruit.h>

BLEService        hrms = BLEService(UUID16_SVC_HEART_RATE);
BLECharacteristic hrmc = BLECharacteristic(UUID16_CHR_HEART_RATE_MEASUREMENT);

// Das ist dein funktionierender Pin aus der Historie (Port 1, Pin 6)
#define BUTTON_PIN NRF_GPIO_PIN_MAP(1, 6) 

void setup() {
  // Wir nutzen wieder INPUT_PULLUP, damit der Pin sauber auf 3.3V gezogen wird,
  // solange du den Taster NICHT drückst.
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
    // Wenn der Taster gedrückt wird, schaltet er gegen Masse -> Zustand wird LOW.
    // Taster gedrückt (LOW) -> 100 BPM (0x64)
    // Taster offen (HIGH) -> 60 BPM (0x3C)
    uint8_t hrValue = (digitalRead(BUTTON_PIN) == LOW) ? 0x64 : 0x3C;
    
    uint8_t hrmData[] = {0x00, hrValue}; 
    hrmc.notify(hrmData, sizeof(hrmData));
  }
  delay(150); // Leicht beschleunigt für knackiges Feedback am Coros
}
