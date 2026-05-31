// ==========================================
// DEINE VERSIONIERUNG (Nur noch hier ändern!)
// ==========================================
String versionsNummer = "31v19"; 
// ==========================================

#include <bluefruit.h>

void setup() {
  Bluefruit.begin();
  
  // Sendeleistung auf Maximum (4 dBm), damit die Reichweite stimmt
  Bluefruit.setTxPower(4); 
  
  // Name baut sich automatisch zusammen: GEMMI_31v19
  String kompletterName = "GEMMI_" + versionsNummer;
  Bluefruit.setName(kompletterName.c_str());
  
  // Bluetooth-Sichtbarkeit einrichten
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower(); // Sendestärke mitsenden (hilft beim Finden)
  Bluefruit.Advertising.addName();
  
  // DER FIX: Aggressives und schnelles Senden im Suchmodus (alle 20 Millisekunden)
  Bluefruit.Advertising.setInterval(32, 244); 
  Bluefruit.Advertising.setFastTimeout(30);
  
  // Bluetooth-Feuer frei!
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Der Loop bleibt leer und stabil
  delay(1000);
}
