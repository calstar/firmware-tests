#include "mbed.h"
#include "util.h"

Serial debug_uart(DEBUG_TX, DEBUG_RX, 9600);
SPI kx222_spi(KX222_MOSI, KX222_MISO, KX222_SCLK);
DigitalOut kx222_cs(KX222_CS);

uint8_t regread(SPI *spi, uint8_t reg){
  uint8_t out;
  spi->write((reg | 0x80));
  out = spi->write((0x00));

  return out;
}

void regwrite(SPI *spi, uint8_t reg, uint8_t payload){
  spi->write(reg);
  spi->write(payload);
}


int run_test() {
  uint8_t kxwhoami;

  debug_uart.printf("==========KX222 Test===========\r\n");
  kx222_spi.format(8,1);
  kx222_spi.frequency(100000 / 4);

  kx222_cs = 0;
  regwrite(&kx222_spi, 0x18, 0x80);
  kx222_cs = 1;
  kx222_spi.write(0x0);
  while(1) {
    kx222_cs = 0;
    kxwhoami = regread(&kx222_spi, 0x0F);
    kx222_cs = 1;
    debug_uart.printf("kx222 whoami: %d\r\n", kxwhoami);
    kx222_spi.write(0x0);
  }

  return 0;
};
