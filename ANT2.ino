// =================================================================
// PROJEKT: Birger DIY 65 (Der unsichtbare F13-Befehl)
// =================================================================
#include <bluefruit.h>
#include <hal/nrf_gpio.h>

BLEDis bledis;
BLEHidAdafruit blehid;

#define PIN_D9       NRF_GPIO_PIN_MAP(1, 6)
#define PIN_D8       NRF_GPIO_PIN_MAP(1, 4)
#define RED_LED      NRF_GPIO_PIN_MAP(0, 15)

bool d8_aktiv = false;
bool d9_aktiv = false;

void setup() {
  Bluefruit.begin();
  // Standard-Tastatur-Profil für maximale Kompatibilität
  blehid.begin();
  
  Bluefruit.setName("Birger DIY 65");
  
  nrf_gpio_cfg_input(PIN_D9, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(PIN_D8, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_output(RED_LED);
  nrf_gpio_pin_write(RED_LED, 1); 
  
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  // D9 sendet F13 (unsichtbar, keine Buchstaben!)
  if (nrf_gpio_pin_read(PIN_D9) == 0 && !d9_aktiv) {
    nrf_gpio_pin_write(RED_LED, 0); 
    blehid.keyPress(HID_KEY_F13);
    delay(50);
    blehid.keyRelease();
    d9_aktiv = true;
  } else if (nrf_gpio_pin_read(PIN_D9) != 0) {
    d9_aktiv = false;
    nrf_gpio_pin_write(RED_LED, 1); 
  }

  // D8 sendet F14 (ebenfalls unsichtbar)
  if (nrf_gpio_pin_read(PIN_D8) == 0 && !d8_aktiv) {
    nrf_gpio_pin_write(RED_LED, 0); 
    blehid.keyPress(HID_KEY_F14);
    delay(50);
    blehid.keyRelease();
    d8_aktiv = true;
  } else if (nrf_gpio_pin_read(PIN_D8) != 0) {
    d8_aktiv = false;
    nrf_gpio_pin_write(RED_LED, 1);
  }
  delay(10);
}
