// ==========================================
// DEINE VERSIONIERUNG: 31v29 (ANT+ SHIFTING)
// ==========================================
#include <ANT.h> 

#define DEVICE_TYPE_SHIFTING 0x04 
#define CHANNEL_NUMBER 0

void setup() {
  // ANT Kanal für Shifting öffnen
  ANT.begin(CHANNEL_NUMBER, DEVICE_TYPE_SHIFTING, 0x1234, 1);
}

void loop() {
  // Page 1: 0x01 (Page ID), 0xFFs, 0x01 (Shift Up)
  uint8_t payload[8] = {0x01, 0xFF, 0xFF, 0xFF, 0x01, 0xFF, 0xFF, 0xFF};

  ANT.broadcast(CHANNEL_NUMBER, payload);
  
  delay(5000); // 5 Sekunden Abstand zum Testen
}
