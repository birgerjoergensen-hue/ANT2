// =================================================================
// PROJEKT: Birger DIY 31v07 (Offene UART-Brücke)
// =================================================================
#include <bluefruit.h>

BLEUart bleuart; 

void setup() {
  Bluefruit.begin();
  Bluefruit.setName("Birger DIY 31v07");
  
  // UART-Service ist der "Türöffner" für fast alle Systeme
  bleuart.begin();
  
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Kein Code, wir wollen nur die stabile Verbindung
  delay(1000);
}
