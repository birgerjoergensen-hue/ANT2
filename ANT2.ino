// ==========================================
// DEINE VERSIONIERUNG (Nur noch hier ändern!)
// ==========================================
String versionsNummer = "31v14"; 
// ==========================================

#include <bluefruit.h>

void setup() {
  Bluefruit.begin();
  
  // Name baut sich automatisch zusammen: GEMMI_31v14
  String kompletterName = "GEMMI_" + versionsNummer;
  Bluefruit.setName(kompletterName.c_str());
  
  // Minimales, stabiles Advertising ohne fehleranfällige Profile
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  delay(1000);
}
