#include <bluefruit.h>

// Wir aktivieren den Human Interface Device (HID) Service für Tastaturen
BLEDis       bledis;
BLEHidGamepad bledgamepad; // Oder BLEHidAdafruit für Standard-Tasten

void setup() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("BLIPBOX-V35");

  // Geräte-Informationen setzen
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Blipbox V35");
  bledis.begin();

  // HID-Dienst starten
  Bluefruit.Hid.begin();

  // Wir nutzen die Pin-Map, die du vorhin gefunden hast
  pinMode(NRF_GPIO_PIN_MAP(1, 6), INPUT_PULLUP);

  // Advertising starten
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(Bluefruit.Hid);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Wenn die Verbindung steht und der Taster (P1.06) gedrückt wird
  if (Bluefruit.connected() && (digitalRead(NRF_GPIO_PIN_MAP(1, 6)) == LOW)) {
    
    // Wir simulieren den Druck der "Pfeil runter"-Taste, um durch das Coros-Menü zu blättern
    // 0x42 ist der Standard HID-Code für "Volume Down" oder Navigations-Tasten
    Bluefruit.Hid.consumerKeyPress(HID_USAGE_CONSUMER_VOLUME_DECREMENT); 
    delay(100);
    Bluefruit.Hid.consumerKeyRelease(); // Taste wieder loslassen
    
    // Entprellen, damit ein Klick nicht als 500 Klicks erkannt wird
    delay(300); 
  }
}
