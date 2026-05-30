#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// Definition deiner 4 Knöpfe laut Plan
const int ANT1 = 9;  // Pin D9  (unten links)
const int ANT2 = 10; // Pin D10 (unten rechts)
const int ANT3 = 16; // Pin D16 (über ANT2, rechts)
const int ANT4 = 8;  // Pin D8  (über ANT1, links)

// LED-Pins auf dem nice!nano v2
const int LED_RED  = 15; 
const int LED_BLUE = 17;

// Timer-Variablen für das LED-Blinken (ohne den Code zu blockieren)
unsigned long previousMillis = 0;
const long blinkInterval = 300; // Blink-Geschwindigkeit in Millisekunden (alle 0,3 Sek.)
bool ledState = HIGH;           // HIGH ist bei den nice!nano LEDs meistens "AUS", LOW ist "AN"

void setup() {
  // Knöpfe einrichten
  pinMode(ANT1, INPUT_PULLUP);
  pinMode(ANT2, INPUT_PULLUP);
  pinMode(ANT3, INPUT_PULLUP);
  pinMode(ANT4, INPUT_PULLUP);

  // LEDs als Ausgang definieren
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  
  // Am Anfang beide LEDs ausschalten (beim nice!nano schaltet HIGH die LED aus)
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, HIGH);

  Bluefruit.begin();
  Bluefruit.setTxPower(4); 

  Bluefruit.setName("Birgers DIY");

  bledis.setManufacturer("GEMMI Tech");
  bledis.setModel("Blipbox v4");
  bledis.begin();

  blehid.begin();

  // Advertising einrichten (Tastatur-Tarnung für Wahoo/Coros)
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); 

  // Startet den 120-Sekunden-Timer für das Koppeln
  Bluefruit.Advertising.start(120); 
}

void loop() {
  unsigned long currentMillis = millis();

  // --- LED BLINK-LOGIK ---
  // Wenn das Board aktiv im Kopplungsmodus (Advertising) ist und kein Gerät verbunden ist:
  if (Bluefruit.Advertising.isRunning() && !Bluefruit.connected()) {
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      ledState = !ledState; // Zustand umkehren
      digitalWrite(LED_RED, ledState); // Rote LED blinkt
    }
  } else {
    // Wenn die 2 Minuten um sind ODER ein Tacho verbunden ist -> Rote LED dauerhaft AUS
    digitalWrite(LED_RED, HIGH); 
  }

  // --- KNOPF-ABFRAGEN ---

  // ANT1 (D9) -> "Vorheriger Titel" (Seite zurück)
  if (digitalRead(ANT1) == LOW) {
    if (!Bluefruit.Advertising.isRunning()) { Bluefruit.Advertising.start(5); } 
    blehid.consumerKeyPress(HID_USAGE_CONSUMER_SCAN_PREVIOUS);
    delay(50); // Entprellen
    blehid.consumerKeyRelease();
    while (digitalRead(ANT1) == LOW) { delay(10); } 
  }

  // ANT2 (D10) -> "Nächster Titel" (Seite vor)
  if (digitalRead(ANT2) == LOW) {
    if (!Bluefruit.Advertising.isRunning()) { Bluefruit.Advertising.start(5); }
    blehid.consumerKeyPress(HID_USAGE_CONSUMER_SCAN_NEXT);
    delay(50);
    blehid.consumerKeyRelease();
    while (digitalRead(ANT2) == LOW) { delay(10); }
  }

  // ANT3 (D16) - Bereit gehalten
  if (digitalRead(ANT3) == LOW) {
    while (digitalRead(ANT3) == LOW) { delay(10); }
  }

  // ANT4 (D8) - Bereit gehalten
  if (digitalRead(ANT4) == LOW) {
    while (digitalRead(ANT4) == LOW) { delay(10); }
  }

  delay(10); // Leicht verkürzt für präziseres LED-Timing
}
