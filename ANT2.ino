#ifdef SOFTDEVICE_PRESENT
extern "C" {
  #include "ant_interface.h"
  #include "ant_parameters.h"
}
#endif
#include <bluefruit.h> // Basis-Bibliothek für nRF52 Funkfunktionen

// Pins für die beiden SRAM Blips definieren
const int BLIP_LINKS  = 4;  // Pin D4 (Seite zurück)
const int BLIP_RECHTS = 5;  // Pin D5 (Seite vor)

// ANT+ Konstanten für das "Remote Control" Profil
const uint8_t ANT_CHANNEL = 0;
const uint8_t ANT_DEV_TYPE = 0x56; // 86 = ANT+ Remote Control
const uint8_t ANT_NET_KEY[] = {0xB9, 0xA5, 0x21, 0xFB, 0xBD, 0x72, 0xC3, 0x45}; // Offizieller ANT+ Public Key

// ANT+ Befehls-Bytes (Command Codes)
const uint8_t CMD_PAGE_FORWARD  = 0x30; // Seite vor
const uint8_t CMD_PAGE_BACKWARD = 0x31; // Seite zurück

// Variablen für das Entprellen (Debouncing) der Taster
unsigned long lastDebounceTimeLinks = 0;
unsigned long lastDebounceTimeRechts = 0;
const unsigned long debounceDelay = 50; // 50 Millisekunden Entprellzeit

void setup() {
  // Pins als Eingang mit internem Pull-up-Widerstand definieren
  // (Blip ungedrückt = HIGH, gedrückt = LOW)
  pinMode(BLIP_LINKS, INPUT_PULLUP);
  pinMode(BLIP_RECHTS, INPUT_PULLUP);

  // Energie sparen: Integrierte LEDs und ungenutzte Peripherie abschalten
  suspendLoop(); 
  
  // ANT+ Funkstack initialisieren
  #if defined(SOFTDEVICE_PRESENT)
    // Aktiviert das SoftDevice (Protokoll-Stack) im nRF52
    sd_softdevice_enable(NULL, NULL);
  #endif

  // ANT+ Kanal konfigurieren
  setupAntChannel();
}

void setupAntChannel() {
  // Hier wird der ANT+ Kanal im Hintergrund geöffnet und konfiguriert.
  // Das Board sendet als "Master" (Sensor/Fernbedienung).
  // (Pseudocode-Struktur für den nRF52 SoftDevice-Aufruf):
  // 1. Kanal zuweisen (Channel 0, Typ: Transmit)
  // 2. Netzwerk-Schlüssel (ANT_NET_KEY) setzen
  // 3. Device ID vergeben (z.B. eine zufällige Nummer passend zur Chip-ID)
  // 4. Device Type setzen (ANT_DEV_TYPE)
  // 5. Kanalfrequenz auf Sport-Netzwerk einstellen (2457 MHz)
}

void loop() {
  // Der nRF52 nutzt im echten Betrieb Interrupts, um Strom zu sparen. 
  // Für das Grundprinzip liest diese Schleife die Pins aus:

  int readingLinks  = digitalRead(BLIP_LINKS);
  int readingRechts = digitalRead(BLIP_RECHTS);

  // Blip Links gedrückt?
  if (readingLinks == LOW && (millis() - lastDebounceTimeLinks) > debounceDelay) {
    sendAntCommand(CMD_PAGE_BACKWARD);
    lastDebounceTimeLinks = millis();
    delay(200); // Verhindert Dauerfeuer bei gehaltenem Knopf
  }

  // Blip Rechts gedrückt?
  if (readingRechts == LOW && (millis() - lastDebounceTimeRechts) > debounceDelay) {
    sendAntCommand(CMD_PAGE_FORWARD);
    lastDebounceTimeRechts = millis();
    delay(200); // Verhindert Dauerfeuer bei gehaltenem Knopf
  }

  // Dem Prozessor erlauben, in den Schlafmodus zu gehen, wenn nichts passiert
  waitForEvent(); 
}

// Funktion zum Senden des ANT+-Pakets
void sendAntCommand(uint8_t commandCode) {
  uint8_t txBuffer[8];
  
  // ANT+ Data Page 1 (Standard für Fernbedienungen) aufbauen
  txBuffer[0] = 0x01;         // Data Page Number 1
  txBuffer[1] = 0xFF;         // Reserviert
  txBuffer[2] = 0xFF;         // Reserviert
  txBuffer[3] = commandCode;  // Unser Befehl (z.B. 0x30 oder 0x31)
  txBuffer[4] = 0x00;         // Befehls-Sequenznummer (wird normal hochgezählt)
  txBuffer[5] = 0xFF;         // Reserviert
  txBuffer[6] = 0xFF;         // Reserviert
  txBuffer[7] = 0xFF;         // Reserviert

  // Da ANT+ keine Empfangsbestätigung hat, senden wir das Paket 
  // zur Sicherheit direkt 3-mal hintereinander (Burst).
  for(int i = 0; i < 3; i++) {
    // Offizieller nRF52 SDK Befehl zum Senden über den ANT-Kanal
    sd_ant_broadcast_message_tx(ANT_CHANNEL, 8, txBuffer);
    delay(10); // Kurze Pause zwischen den Wiederholungen
  }
}
