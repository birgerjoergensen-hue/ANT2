// =================================================================
// PROJEKT: Birger DIY 57 (Kontrolliertes Senden)
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
  
  Bluefruit.setName("Birger DIY 57");
  
  nrf_gpio_cfg_input(PIN_D9_PHYSICAL, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(PIN_D8_PHYSICAL, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_output(RED_LED);
  nrf_gpio_pin_write(RED_LED, 0); // Aus

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Pin D9 Senden
  if (nrf_gpio_pin_read(PIN_D9_PHYSICAL) == 0) {
    nrf_gpio_pin_write(RED_LED, 1); // LED An
    blehid.keyPress(HID_KEY_A);
    delay(50);
    blehid.keyRelease();
    delay(200); // Sicherheits-Pause für das Handy
    
    // Warten bis Pin losgelassen wird, aber ohne zu senden
    while (nrf_gpio_pin_read(PIN_D9_PHYSICAL) == 0) { delay(10); }
    nrf_gpio_pin_write(RED_LED, 0); // LED Aus
  }

  // Pin D8 Senden
  if (nrf_gpio_pin_read(PIN_D8_PHYSICAL) == 0) {
    nrf_gpio_pin_write(RED_LED, 1); // LED An
    blehid.keyPress(HID_KEY_B);
    delay(50);
    blehid.keyRelease();
    delay(200);
    
    while (nrf_gpio_pin_read(PIN_D8_PHYSICAL) == 0) { delay(10); }
    nrf_gpio_pin_write(RED_LED, 0); // LED Aus
  }
  delay(10);
}
