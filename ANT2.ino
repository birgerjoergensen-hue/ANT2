// ==========================================
// DEINE VERSIONIERUNG: 31v27 (ANT+ SHIFTING)
// ==========================================
#include <AntPlus.h>
#include <AntPlusShifting.h>

// Deine Geräte-ID (kannst du ändern, wenn er es nicht sofort findet)
#define DEVICE_ID 12345 

AntPlusShifting shifting(DEVICE_ID);

void setup() {
  // ANT+ Stack Initialisierung
  // Wir emulieren ein Shifting-Device (0x04)
  AntPlus_Init(); 
  shifting.begin();
}

void loop() {
  // Hier würde deine Logik für die Taster stehen.
  // Zum Testen senden wir alle 5 Sekunden einen "Schaltbefehl"
  
  // 1 = Hoch, 2 = Runter
  shifting.shift(1); 
  delay(1000);
  shifting.shift(2);
  
  delay(5000);
}
