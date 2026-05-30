// =================================================================
// PROJEKT: Birger DIY 52 (Universal Fix)
// =================================================================
#include <bluefruit.h>
#include <hal/nrf_gpio.h>

#define PIN_D8       NRF_GPIO_PIN_MAP(1, 4)
#define PIN_D9       NRF_GPIO_PIN_MAP(1, 6)
#define RED_LED      NRF_GPIO_PIN_MAP(0, 15)

// Setze dies auf 'true', wenn die LED bei deinem Board falschherum leuchtet
const bool INVERT_LED = true; 

void setLed(bool on) {
  nrf_gpio_pin_write(RED_LED, INVERT_LED ? !on : on);
}

void setup() {
  Bluefruit.begin();
  Bluefruit.setAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  bledis.begin();
  blehid.begin();
  Bluefruit.setName("Birger DIY 52");
  
  nrf_gpio_cfg_input(PIN_D9, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(PIN_D8, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_output(RED_LED);
  setLed(false); // LED aus

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Entprellung durch kurze Pausen
  if (nrf_gpio_pin_read(PIN_D9) == 0) {
    setLed(true);
    blehid.keyPress(HID_KEY_A);
    delay(100); // Längere Haltezeit für das Handy-HID
    blehid.keyRelease();
    while (nrf_gpio_pin_read(PIN_D9) == 0) { delay(50); }
    setLed(false);
  }

  if (nrf_gpio_pin_read(PIN_D8) == 0) {
    setLed(true);
    blehid.keyPress(HID_KEY_ARROW_DOWN);
    delay(100);
    blehid.keyRelease();
    while (nrf_gpio_pin_read(PIN_D8) == 0) { delay(50); }
    setLed(false);
  }
  delay(50);
}
