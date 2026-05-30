// =================================================================
// PROJEKT: Birger DIY 59 (Stabile Hardware-Basis)
// =================================================================
#include <bluefruit.h>
#include <hal/nrf_gpio.h>

BLEHidAdafruit blehid;

void setup() {
  Bluefruit.begin();
  
  // Setze HID-Profil
  blehid.begin();
  Bluefruit.setName("Birger DIY 59");
  
  // Pins als Eingang mit Pullup
  nrf_gpio_cfg_input(NRF_GPIO_PIN_MAP(1, 4), NRF_GPIO_PIN_PULLUP); // D8
  nrf_gpio_cfg_input(NRF_GPIO_PIN_MAP(1, 6), NRF_GPIO_PIN_PULLUP); // D9
  
  // Advertising so einstellen, dass es nach jedem Disconnect neu startet
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Wir lesen die Pins nur ganz selten aus, um den Chip nicht zu belasten
  if (nrf_gpio_pin_read(NRF_GPIO_PIN_MAP(1, 6)) == 0) { // D9
    blehid.keyPress(HID_KEY_A);
    delay(100);
    blehid.keyRelease();
    delay(500); 
  }
  
  if (nrf_gpio_pin_read(NRF_GPIO_PIN_MAP(1, 4)) == 0) { // D8
    blehid.keyPress(HID_KEY_B);
    delay(100);
    blehid.keyRelease();
    delay(500);
  }
  delay(100);
}
