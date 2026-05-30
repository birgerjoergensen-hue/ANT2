// =================================================================
// PROJEKT: Birger DIY 48 (Koppeln + Funktion)
// =================================================================
#include <bluefruit.h>
#include <hal/nrf_gpio.h>

BLEDis bledis;
BLEHidAdafruit blehid;

// Hardware-Pins wie besprochen
#define PIN_D9       NRF_GPIO_PIN_MAP(1, 6)
#define PIN_D8       NRF_GPIO_PIN_MAP(1, 4)
#define RED_LED      NRF_GPIO_PIN_MAP(0, 15)

void setup() {
  Bluefruit.begin();
  Bluefruit.setAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  bledis.setManufacturer("GEMMI");
  bledis.setModel("Blipbox");
  bledis.begin();

  blehid.begin();
  
  Bluefruit.setName("Birger DIY 48");
  
  // Hardware-Konfiguration
  nrf_gpio_cfg_input(PIN_D9, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_input(PIN_D8, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_output(RED_LED);
  nrf_gpio_pin_write(RED_LED, 1); // LED Aus

  // Advertising für HID
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.start(0);
}

void loop() {
  // Test D9: Rote LED + 'A' senden
  if (nrf_gpio_pin_read(PIN_D9) == 0) {
    nrf_gpio_pin_write(RED_LED, 0); // LED AN
    blehid.keyPress(HID_KEY_A);
    delay(50);
    blehid.keyRelease();
    delay(200);
    while (nrf_gpio_pin_read(PIN_D9) == 0) { delay(10); }
    nrf_gpio_pin_write(RED_LED, 1); // LED AUS
  }

  // Test D8: Rote LED + Scrollen
  if (nrf_gpio_pin_read(PIN_D8) == 0) {
    nrf_gpio_pin_write(RED_LED, 0); // LED AN
    blehid.keyPress(HID_KEY_ARROW_DOWN);
    delay(50);
    blehid.keyRelease();
    delay(200);
    while (nrf_gpio_pin_read(PIN_D8) == 0) { delay(10); }
    nrf_gpio_pin_write(RED_LED, 1); // LED AUS
  }
  delay(10);
}
