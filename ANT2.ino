// ==========================================
// DEINE VERSIONIERUNG (Nur noch hier ändern!)
// ==========================================
String versionsNummer = "31v24"; 
// ==========================================

#include <bluefruit.h>
// HIER MÜSSTEN WIR DIE ANT-LIBRARY EINBINDEN, DIE DU SCHON FÜR DEINE BLIPBOX GENUTZT HAST
// #include <AntLib.h> 

BLEDis bledis;
BLEHidAdafruit blehid;

void setup() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  
  // Name für BT-Erkennung
  String kompletterName = "GEMMI_" + versionsNummer;
  Bluefruit.setName(kompletterName.c_str());
  
  bledis.setManufacturer("GEMMI DIY");
  bledis.setModel("ANT-Bridge");
  bledis.begin();

  blehid.begin();
  
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addAppearance(0x0180); // Remote Control
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.start(0);

  // HIER DEIN ANT+ INIT:
  // Initialisiere hier den Kanal, den du in deiner Version 18-20 
  // für die Blipbox-Steuerung verwendet hast.
}

void loop() {
  // 1. BT-HID-Test für Handy/PC
  if (Bluefruit.connected()) {
      // ... Tastendruck-Logik ...
  }
  
  // 2. ANT+ SENDUNG:
  // Hier muss dein Code rein, der die SRAM-Signale 
  // als ANT+ Fernbedienungs-Befehl an das Coros schickt.
}
