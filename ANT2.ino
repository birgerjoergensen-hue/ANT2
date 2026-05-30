// =================================================================
// PROJEKT: Birger DIY 45 (Letzter Hardware-Check)
// =================================================================
#include <bluefruit.h>
#include <hal/nrf_gpio.h>

#define TEST_PIN    NRF_GPIO_PIN_MAP(0, 9) // Pin D10
#define RED_LED     NRF_GPIO_PIN_MAP(0, 15)

void setup() {
  nrf_gpio_cfg_input(TEST_PIN, NRF_GPIO_PIN_PULLUP);
  nrf_gpio_cfg_output(RED_LED);
  nrf_gpio_pin_write(RED_LED, 1); // Aus
}

void loop() {
  // Wenn Pin gegen GND gedrückt wird, muss die LED angehen
  if (nrf_gpio_pin_read(TEST_PIN) == 0) {
    nrf_gpio_pin_write(RED_LED, 0); // AN
  } else {
    nrf_gpio_pin_write(RED_LED, 1); // AUS
  }
}
