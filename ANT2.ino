// =================================================================
// PROJEKT: Birger DIY 61 (Stabile Basis für Eingabe)
// =================================================================
#include <bluefruit.h>
#include <hal/nrf_gpio.h>

BLEHidAdafruit blehid;

#define PIN_D8 NRF_GPIO_PIN_MAP(1, 4)
#define PIN_D9 NRF_GPIO_PIN_MAP(1, 6)

// Merker-Variablen, um Doppeleingaben zu verhindern
bool d8_gedrueckt = false;
bool d9_gedrueckt = false;

void setup() {
  Bluefruit.begin();
  blehid.begin();
  Bluefruit.setName("Birger DIY 61");

  nrf_gpio_cfg_input(PIN_D8, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(PIN_D9, NRF_GPIO_PIN_PULLUP);

  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  // D8 Eingabe-Logik
  if (nrf_gpio_pin_read(PIN_D8) == 0) {
    if (!d8_gedrueckt) {
      blehid.keyPress(HID_KEY_B); // Wir testen mit B
      delay(20);
      blehid.keyRelease();
      d8_gedrueckt = true;
    }
  } else {
    d8_gedrueckt = false;
  }

  // D9 Eingabe-Logik
  if (nrf_gpio_pin_read(PIN_D9) == 0) {
    if (!d9_gedrueckt) {
      blehid.keyPress(HID_KEY_A); // Wir testen mit A
      delay(20);
      blehid.keyRelease();
      d9_gedrueckt = true;
    }
  } else {
    d9_gedrueckt = false;
  }
  
  delay(10);
}
