// =================================================================
// PROJEKT: Birger DIY 64 (System-Steuerungs-Modus)
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
  Bluefruit.setAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  bledis.begin();
  blehid.begin();
  Bluefruit.setName("Birger DIY 64");
  
  nrf_gpio_cfg_input(PIN_D9, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(PIN_D8, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_output(RED_LED);
  nrf_gpio_pin_write(RED_LED, 1); // Aus
  
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  // D9: Sende "Lauter" (System-Befehl)
  if (nrf_gpio_pin_read(PIN_D9) == 0 && !d9_aktiv) {
    nrf_gpio_pin_write(RED_LED, 0); // An
    blehid.consumerKeyPress(HID_USAGE_CONSUMER_VOLUME_INCREMENT);
    delay(50);
    blehid.consumerKeyRelease();
    d9_aktiv = true;
  } else if (nrf_gpio_pin_read(PIN_D9) != 0) {
    d9_aktiv = false;
    nrf_gpio_pin_write(RED_LED, 1); // Aus
  }

  // D8: Sende "Play/Pause" (System-Befehl)
  if (nrf_gpio_pin_read(PIN_D8) == 0 && !d8_aktiv) {
    nrf_gpio_pin_write(RED_LED, 0); // An
    blehid.consumerKeyPress(HID_USAGE_CONSUMER_PLAY_PAUSE);
    delay(50);
    blehid.consumerKeyRelease();
    d8_aktiv = true;
  } else if (nrf_gpio_pin_read(PIN_D8) != 0) {
    d8_aktiv = false;
    nrf_gpio_pin_write(RED_LED, 1); // Aus
  }
  delay(10);
}
