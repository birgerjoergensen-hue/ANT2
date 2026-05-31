// ==========================================
// DEINE VERSIONIERUNG (Nur noch hier ändern!)
// ==========================================
String versionsNummer = "31v21"; 
// ==========================================

#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

void setup() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4); // Volle Sendeleistung für maximale Stabilität
  
  // Name baut sich automatisch zusammen: GEMMI_31v21
  String kompletterName = "GEMMI_" + versionsNummer;
  Bluefruit.setName(kompletterName.c_str());
  
  // Identität setzen
  bledis.setManufacturer("GEMMI DIY");
  bledis.setModel("Blipbox");
  bledis.begin();

  // Tastatur- und Medientasten-Dienst starten
  blehid.begin();
  
  // Bluetooth-Sichtbarkeit als Fernbedienung/Tastatur
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD); 
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  
  // Aggressives Senden für schnelles und stabiles Koppeln
  Bluefruit.Advertising.setInterval(32, 244); 
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Wenn die Verbindung steht, testen wir das Signal
  if (Bluefruit.connected()) {
    
    // HIER IST DER FIX: Statt 'q' senden wir jetzt alle 5 Sekunden 
    // den universellen Befehl "Lautstärke erhöhen". 
    // Wenn die Verbindung steht, solltest du sehen, wie am Handy/Laptop der Lautstärkebalken hochgeht!
    blehid.consumerKeyPress(HID_USAGE_CONSUMER_VOLUME_INCREMENT);
    delay(100);
    blehid.consumerKeyRelease();
    
    delay(5000);
  }
}
