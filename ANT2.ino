#include <bluefruit.h>

// ANT+ Schaltungs-ID (Standard für Lev-Shifting / Shifter)
#define ANT_SHIFTER_PROFILE 115

// Definition der 4 Knöpfe laut deinem Plan
const int ANT1 = 9;  // Pin D9  (unten links)
const int ANT2 = 10; // Pin D10 (unten rechts)
const int ANT3 = 16; // Pin D16 (über ANT2, rechts)
const int ANT4 = 8;  // Pin D8  (über ANT1, links)

void setup() {
  pinMode(ANT1, INPUT_PULLUP);
  pinMode(ANT2, INPUT_PULLUP);
  pinMode(ANT3, INPUT_PULLUP);
  pinMode(ANT4, INPUT_PULLUP);

  // Wir starten das Board komplett ohne Bluetooth, damit der ANT-Kanal alle Rechte hat
  Bluefruit.begin(0, 1); // 0 BLE Verbindungen, aber 1 ANT-Kanal erlauben
  Bluefruit.setTxPower(4);

  // Name für die interne Zuordnung
  Bluefruit.setName("Birgers DIY");

  // Initialisiere den ANT+ Shifter Kanal
  // Hinweis: Wenn die IDE hier meckert, nutzen wir das rohe SoftDevice-Kommando
  sd_ant_channel_assign(0, 0x00, 0, 0); 
  sd_ant_channel_id_set(0, 12345, ANT_SHIFTER_PROFILE, 0); // Feste Sensor-ID 12345
  sd_ant_channel_period_set(0, 8192); // 4Hz Übertragungsrate (Standard für Schaltungen)
  sd_ant_channel_radio_freq_set(0, 57); // 2457 MHz (Offizielle ANT+ Frequenz)
  sd_ant_channel_open(0);
}

void loop() {
  // Puffer für die ANT+-Datenpakete (Simuliert Gangwechsel/Tastendruck)
  uint8_t ant_packet[8] = {0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

  // ANT1 (D9) -> Simuliert Di2 Befehl: Linke Taste (Seite zurück)
  if (digitalRead(ANT1) == LOW) {
    ant_packet[0] = 0x01; // Event: Taste gedrückt
    ant_packet[6] = 0x01; // Code für "Zurück"
    sd_ant_broadcast_message_tx(0, 8, ant_packet);
    delay(100);
    while (digitalRead(ANT1) == LOW) { delay(10); }
  }

  // ANT2 (D10) -> Simuliert Di2 Befehl: Rechte Taste (Seite vor)
  if (digitalRead(ANT2) == LOW) {
    ant_packet[0] = 0x01;
    ant_packet[6] = 0x02; // Code für "Vorwärts"
    sd_ant_broadcast_message_tx(0, 8, ant_packet);
    delay(100);
    while (digitalRead(ANT2) == LOW) { delay(10); }
  }

  // ANT3 (D16) & ANT4 (D8) halten wir hier bewusst noch frei (keine Tränenschaltung)
  if (digitalRead(ANT3) == LOW) {
    // Platzhalter für spätere Funktion
    while (digitalRead(ANT3) == LOW) { delay(10); }
  }
  if (digitalRead(ANT4) == LOW) {
    // Platzhalter für spätere Funktion
    while (digitalRead(ANT4) == LOW) { delay(10); }
  }

  delay(20);
}
