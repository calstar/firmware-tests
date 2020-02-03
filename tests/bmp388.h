#include "mbed.h"
#include "util.h"
#include "lib/BMP3/bmp3.h"
#include <thread>
#include <chrono>

Serial debug_uart(DEBUG_TX, DEBUG_RX, 9600);
SPI bmp388_spi(BMP388_MOSI, BMP388_MISO, BMP388_SCLK, BMP388_CS);

int8_t bmp388_spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len) {
  bmp388_spi.select();
  data[0] = bmp388_spi.write(reg_addr);
  for (uint16_t i = 1; i < len; ++i) {
    data[i] = bmp388_spi.write(0)
  }
  bmp388_spi.deselect();
}

int8_t bmp388_spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len) {
  bmp388_spi.select();
  bmp388_spi.write(reg_addr);
  for (uint16_t i = 0; i < len; ++i) {
    bmp388_spi.write(data[i]);
  }
  bmp388_spi.deselect();
}

// int8_t bmp388_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);

// int8_t bmp388_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);

void bmp388_delay_ms(uint32_t period) {
  // std::this_thread::sleep_for(std::chrono::milliseconds(period));

  // mbed appears to be deprecating wait in favor of std c++ thread, but above does not compile.
  wait_ms(period);
}

int run_test() {
  debug_uart.printf("==========BMP388 Test===========\r\n");
 
  struct bmp3_dev dev;
  int8_t res = BMP3_OK;

  dev.dev_id = 0;
  dev.intf = BMP3_SPI_INTF;
  dev.read = bmp388_spi_read;
  dev.write = bmp388_spi_write;
  dev.delay_ms = bmp388_delay_ms;

  res = bmp3_init(&dev);

  if (res != BMP3_OK) {
    debug_uart.printf("failed to initialize\r\n");
  }
  debug_uart.printf("initialized succesfully\r\n");
  return 0;
};
