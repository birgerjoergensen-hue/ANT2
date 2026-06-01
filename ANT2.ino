#include <bluefruit.h>

BLEService        hrms = BLEService(UUID16_SVC_HEART_RATE);
BLECharacteristic hrmc = BLECharacteristic(UUID16_CHR_HEART_RATE_MEASUREMENT);

void setup() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("BLIPBOX-V35");

  // Herzfrequenz-Service aufsetzen
  hrms.begin();
  hrmc.setProperties(CHR_PROPS_NOTIFY);
  hrmc.setFixedLen(2);
  hrmc.begin();

  // Advertising-Daten für den Coros Dura
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addService(hrms);
  Bluefruit.Advertising.addName();
  
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244); // 20ms bis 150ms
  Bluefruit.Advertising.setFastTimeout(30);
  Bluefruit.Advertising.start(0); // Dauerhaftes Advertising
}

void loop() {
  if (Bluefruit.Connected()) {
    // Sende Dummy-Herzfrequenz (72 BPM) als Hex-Daten: 00 48
    uint8_t hrmData[] = {0x00, 0x48}; 
    hrmc.notify(hrmData, sizeof(hrmData));
  }
  delay(1000);
}
