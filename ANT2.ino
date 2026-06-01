#include <bluefruit.h>

// Wir instanziieren den HID-Dienst korrekt als eigenes Objekt
BLEDis       bledis;
BLEHidAdafruit blehid;

void setup() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("BLIPBOX-V35");

  // Geräte-Informationen befüllen
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Blipbox V35");
  bledis.begin();

  // HID-Dienst initialisieren
  blehid.begin();

  // Deinen funktionierenden Hardware-Pin als Eingang deklarieren
  pinMode(NRF_GPIO_PIN_MAP(1, 6), INPUT_PULLUP);

  // Advertising für HID-Geräte aufbauen
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  // Hier binden wir den HID-Service korrekt ein
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Wenn verbunden und der Taster gedrückt wird (LOW)
  if (Bluefruit.connected() && (digitalRead(NRF_GPIO_PIN_MAP(1, 6)) == LOW)) {
    
    // Wir senden den Consumer-Key für "Lautstärke runter" (wird von vielen Systemen als Blätter-Befehl genutzt)
    blehid.consumerKeyPress(HID_USAGE_CONSUMER_VOLUME_DECREMENT);
    delay(50);
    blehid.consumerKeyRelease(); // Wichtig: Taste wieder loslassen
    
    // Entprellen, damit ein Klick nicht dauerhaft feuert
    delay(300); 
  }
}
