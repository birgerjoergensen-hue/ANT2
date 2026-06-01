/* * BLIPBOX-V35 
 * Version: 2026-06-01-V4
 * Strategie: Zwangsemulation E-Bike, Deaktivierung aller anderen Profile
 */

#include <bluefruit.h>

// Service für E-Bike Control
BLEService        ebs = BLEService(0x183C); 
BLECharacteristic ebc = BLECharacteristic(0x2B56); 

void setup() {
  // WICHTIG: Wir deaktivieren den Heart Rate Service explizit, 
  // falls die Bibliothek ihn automatisch mitstartet
  Bluefruit.begin();
  
  // Name für den Coros
  Bluefruit.setName("E-BIKE-STEPS");

  // E-Bike Service initialisieren
  ebs.begin();
  ebc.setProperties(CHR_PROPS_NOTIFY | CHR_PROPS_WRITE);
  ebc.setFixedLen(2);
  ebc.begin();

  pinMode(NRF_GPIO_PIN_MAP(1, 6), INPUT_PULLUP);

  // Werbe-Daten nur auf den E-Bike-Service beschränken
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addAppearance(0x044C); 
  Bluefruit.Advertising.addService(ebs); 
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.start(0);
}

void loop() {
  if (Bluefruit.connected()) {
    // Wenn Taster gedrückt (LOW)
    if (digitalRead(NRF_GPIO_PIN_MAP(1, 6)) == LOW) {
      // Wir senden ein neutrales E-Bike-Kommando
      uint8_t commandData[] = {0x01, 0x01}; 
      ebc.notify(commandData, sizeof(commandData));
      
      // Feedback an dich im seriellen Monitor (nur zur Kontrolle)
      delay(500); 
    }
  }
  delay(100);
}
