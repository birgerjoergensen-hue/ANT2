#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// Definition deiner 4 Knöpfe laut Plan
const int ANT1 = 9;  // Pin D9  (unten links)
const int ANT2 = 10; // Pin D10 (unten rechts)
const int ANT3 = 16; // Pin D16 (über ANT2, rechts)
const int ANT4 = 8;  // Pin D8  (über ANT1, links)

// Eigene Namen für die nice!nano v2 LEDs
const int MY_LED_RED  = 15; 
const int MY_LED_BLUE = 17;

// Timer-Variablen für das LED-Blinken
unsigned long previousMillis = 0;
const long blinkInterval = 200; // Etwas schnelleres Blinken für bessere Sichtbarkeit
bool ledState = HIGH;           

void setup() {
  pinMode(ANT1, INPUT_PULLUP);
  pinMode(ANT2, INPUT_PULLUP);
  pinMode(ANT3, INPUT_PULLUP);
  pinMode(ANT4, INPUT_PULLUP);

  pinMode(MY_LED_RED, OUTPUT);
  pinMode(MY_LED_BLUE, OUTPUT);
  
  // Rote LED DAUERHAFT EIN (LOW schaltet die LED beim nice!nano ein)
  digitalWrite(MY_LED_RED, LOW);
  // Blaue LED am Anfang AUS (HIGH ist aus)
  digitalWrite(MY_LED_BLUE, HIGH);

  Bluefruit.begin();
  Bluefruit.setTxPower(4); 

  Bluefruit.setName("Birgers DIY");

  bledis.setManufacturer("GEMMI Tech");
  bledis.setModel("Blipbox v4");
  bledis.begin();

  blehid.begin();

  // Ungeschützter Suchmodus für Wahoo/Coros
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.
