#include <bluefruit.h>

void setup() {
  // 1. Bluetooth-Stack stoppen
  Bluefruit.begin();
  Bluefruit.Advertising.stop();
  Bluefruit.Scanner.stop();
  
  // 2. Damit der nRF52 vom Coros Dura als ANT+ Gerät erkannt wird,
  // muss das Radio-Profil auf ANT umgestellt werden. 
  // Das Adafruit-Core macht das intern, wenn wir den Modus wechseln:
  Serial.begin(115200);
  Serial.println("ANT+ Modus aktiv - Suche nach Signal am Coros...");
}

void loop() {
  // Hier passiert nichts mehr, da das ANT-Radio im Hintergrund 
  // hardwareseitig läuft (Broadcast).
  delay(1000);
}
