#include "RFM69/RFM69.hpp"
#include "mbed.h"
#include <string>

#define ENCRYPT_KEY "CALSTARENCRYPTKE"

int run_test() {
  RFM69 radio(SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_SSEL, RADIO_RST, true);

  radio.reset();

  radio.init();

  radio.setAESEncryption(ENCRYPT_KEY, strlen(ENCRYPT_KEY));
  //radio.sleep();

  radio.setHighPowerSettings(true);
  radio.setPowerDBm(20);

  //radio.setCSMA(true);

  const std::string strs[3] = {"hello", "what", "great how about this\r\n"};
  uint8_t i = 0;
  while (true) {
    const std::string &str = strs[i%3];
    radio.send(str.c_str(), str.length());
    ++i;
    // wait_ms(200);
  }
  return 0;
}
