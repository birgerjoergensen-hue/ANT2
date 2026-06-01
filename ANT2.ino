#include <Arduino.h>

void setup() {
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_RED, HIGH);
  delay(1000);
  digitalWrite(LED_RED, LOW);
}

void loop() {
  __WFI(); 
}
#include <Arduino.h>

void setup() {
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  // Blaue LED (BLE-Status) hart auf LOW
  digitalWrite(LED_BLUE, LOW);
  
  // Rote LED kurz an, um Lebenszeichen zu geben
  digitalWrite(LED_RED, HIGH);
  delay(1000);
  digitalWrite(LED_RED, LOW);
}

void loop() {
  __WFI(); 
}
