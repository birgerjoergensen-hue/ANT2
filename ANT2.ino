// =================================================================
// PROJEKT: Birger DIY 56 (Buchstaben-Test)
// =================================================================
#include <bluefruit.h>
#include <hal/nrf_gpio.h>

BLEDis bledis;
BLEHidAdafruit blehid;

#define PIN_D8_PHYSICAL  NRF_GPIO_PIN_MAP(1, 4)
#define PIN_D9_PHYSICAL  NRF_GPIO_PIN_MAP(1, 6)
#define RED_LED          NRF_GPIO_PIN_MAP(0, 15)

void setup() {
  Bluefruit.begin();
  Bluefruit.setAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  bledis.begin();
  blehid.begin();
  
  Bluefruit.setName("Birger DIY 56");
  
  nrf_gpio_cfg_input(PIN_D9_PHYSICAL, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(PIN_D8_PHYSICAL, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_output(RED_LED);
  nrf_gpio_pin_write(RED_LED, 0); 

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  // D9 sendet 'A'
  if (nrf_gpio_pin_read(PIN_D9_PHYSICAL) == 0) {
    nrf_gpio_pin_write(RED_LED, 1);
    blehid.keyPress(HID_KEY_A);
    delay(50);
    blehid.keyRelease();
    while (nrf_gpio_pin_read(PIN_D9_PHYSICAL) == 0) { delay(10); }
    nrf_gpio_pin_write(RED_LED, 0);
  }

  // D8 sendet 'B' (statt Pfeiltaste runter)
  if (nrf_gpio_pin_read(PIN_D8_PHYSICAL) == 0) {
    nrf_gpio_pin_write(RED_LED, 1);
    blehid.keyPress(HID_KEY_B);
    delay(50);
    blehid.keyRelease();
    while (nrf_gpio_pin_read(PIN_D8_PHYSICAL) == 0) { delay(10); }
    nrf_gpio_pin_write(RED_LED, 0);
  }
  delay(10);
}
