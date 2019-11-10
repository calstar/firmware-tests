#include "mbed.h"
#include "util.h"

Serial debug_uart(DEBUG_TX, DEBUG_RX, 9600);
SPI bmp388_spi(BMP388_MOSI, BMP388_MISO, BMP388_SCLK, BMP388_CS);

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
  uint8_t bmpchipid;

  debug_uart.printf("==========BMP388 Test===========\r\n");
  bmp388_spi.format(8,1);
  bmp388_spi.frequency(1000000 / 2);

  bmp388_spi.select();
  regwrite(&bmp388_spi, 0x1b, 0x30);
  bmp388_spi.deselect();
  //bmp388_spi.write(0x0);
  while(1) {
    bmp388_spi.select();
    bmpchipid = regread(&bmp388_spi, 0x00);
    bmp388_spi.deselect();
    debug_uart.printf("BMP388 CHIP_ID (0x50 expected): %d\r\n", bmpchipid);
    //bmp388_spi.write(0x0);
  }

  return 0;
};
