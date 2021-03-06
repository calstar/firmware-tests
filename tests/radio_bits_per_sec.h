#include "RFM69/RFM69.hpp"
#include "mbed.h"
#include "USBSerial.h"

#define ENCRYPT_KEY "CALSTARENCRYPTKE"

#define BAUDRATE (115200)

#define MEASURE_INTERVAL_US (5000000)

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
  uint32_t num_bytes = 0;
  Timer t;
  t.start();
  us_timestamp_t t0 = t.read_high_resolution_us();

  while (true) {
    if (t.read_high_resolution_us() - t0 >= MEASURE_INTERVAL_US) {
      t0 = t.read_high_resolution_us();
      fprintf(pc, "bits per sec: %f\r\n", (num_bytes*8)/((float)MEASURE_INTERVAL_US/1000000.f));
      num_bytes = 0;
    }
    bytes_rxd = radio.receive(rx_buf, sizeof(rx_buf));
    if (bytes_rxd > 1) {
      rx_buf[bytes_rxd] = '\0';
      // fprintf(pc, "%s", rx_buf + 1);
      num_bytes += bytes_rxd - 1;
    }
  }
  return 0;
}
