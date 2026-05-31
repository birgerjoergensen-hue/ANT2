// ==========================================
// DEINE VERSIONIERUNG: 31v28 (ANT+ SHIFTING)
// ==========================================
#include <ANT.h>

// SRAM Shifting Device Type
#define DEVICE_TYPE_SHIFTING 0x04 
#define CHANNEL_NUMBER 0

void setup() {
  // ANT Kanal für Shifting öffnen
  // Wir emulieren ein Schaltwerk
  ANT.begin(CHANNEL_NUMBER, DEVICE_TYPE_SHIFTING, 0x1234, 1);
}

void loop() {
  // ANT+ Shifting Data Page 1
  // Byte 0: Data Page 1 (0x01)
  // Byte 4: 0x00=Nichts, 0x01=Hochschalten, 0x02=Runterschalten
  
  uint8_t payload[8] = {0x01, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF};

  // --- HIER DEINE TASTER-LOGIK ---
  // Wenn Taster 1 gedrückt:
  payload[4] = 0x01; // Schaltbefehl "Hoch"
  ANT.broadcast(CHANNEL_NUMBER, payload);
  
  delay(2000); // Testweise senden wir alle 2 Sekunden einen Befehl
}
