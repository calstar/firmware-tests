#include "RFM69/RFM69.hpp"
#include "mbed.h"
#include "USBSerial.h"

#define ENCRYPT_KEY "CALSTARENCRYPTKE"

#define BAUDRATE (115200)

int run_test() {
  USBSerial pc;
  RFM69 radio(SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_SSEL, RADIO_RST, true);

  radio.reset();
  fprintf(pc, "radio reset\r\n");

  radio.init();
  fprintf(pc, "radio init'd\r\n");

  radio.setAESEncryption(ENCRYPT_KEY, strlen(ENCRYPT_KEY));
  //radio.sleep();

  radio.setHighPowerSettings(true);
  radio.setPowerDBm(20);

  //radio.setCSMA(true);

  int bytes_rxd = 0;
  char rx_buf[512];
  char tx_buf[512];
  uint8_t i = 0;
  while (true) {
    // if (pc.readable()) {
    //   tx_buf[i] = pc.getc();
    //   ++i;
    //   if (tx_buf[i - 1] == '\n' || i == 128) {
    //     radio.send(tx_buf, i);
    //     i = 0;
    // //    radio.sleep();
    //   }
    // }
    bytes_rxd = radio.receive(rx_buf, sizeof(rx_buf));
    if (bytes_rxd > 1) {
      rx_buf[bytes_rxd] = '\0';
      fprintf(pc, "%s", rx_buf + 1);
    }
  }
  return 0;
}
