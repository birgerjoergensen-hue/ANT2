#include <bluefruit.h>

void setup() {
  // Initialisierung der BLE-Hardware als Basis
  // Wir konfigurieren das Gerät als Generic Remote (Appearance 0x0180)
  Bluefruit.begin();
  Bluefruit.setName("GEMMI_ANT");
  
  // Der nRF52 benötigt hier keine externe Bibliothek, 
  // das Adafruit-Core erledigt die Stack-Initialisierung intern.
}

void loop() {
  // Test-Logik bleibt stabil
  delay(1000);
}
