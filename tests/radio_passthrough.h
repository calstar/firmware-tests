#include "RFM69/RFM69.hpp"
#include "mbed.h"

#define ENCRYPT_KEY "CALSTARENCRYPTKE"

#define BAUDRATE (115200)

int run_test() {
  Serial pc(DEBUG_TX, DEBUG_RX);
  pc.baud(BAUDRATE);
  pc.set_blocking(false);
  RFM69 radio(SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_SSEL, RADIO_RST, true);

  radio.reset();
  pc.printf("radio reset\r\n");

  radio.init();
  pc.printf("radio init'd\r\n");

  radio.setAESEncryption(ENCRYPT_KEY, strlen(ENCRYPT_KEY));
  radio.sleep();

  radio.setPowerDBm(10);

  radio.setCSMA(true);

  int bytes_rxd = 0;
  char rx_buf[128];
  while (true) {
    if (pc.readable()) {
      char c = pc.getc();
      radio.send(&c, 1);
      radio.sleep();
    }
    bytes_rxd = radio.receive(rx_buf, sizeof(rx_buf));
    if (bytes_rxd > 1) {
      rx_buf[bytes_rxd] = '\0';
      pc.printf("%s", rx_buf + 1);
    }
  }
  return 0;
}
