#include <bluefruit.h>

void setup() {
  // Wir unterdrücken die Initialisierung des BLE-Stacks
  // indem wir ihn nicht mit den Standard-Parametern starten.
  // Das sollte die blaue LED dauerhaft dunkel lassen.
  
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, LOW);
  
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_RED, HIGH); // Rote LED an = System bereit
  
  // Minimal-Setup ohne Advertising
  Bluefruit.begin(0, 0); 
  Bluefruit.Advertising.stop();
}

void loop() {
  // Leerlauf für den nächsten Schritt
  delay(1000);
}
