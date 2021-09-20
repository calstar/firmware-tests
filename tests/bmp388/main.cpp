#include "mbed.h"
#include "pins.h"
#include "util.h"
#include "BMP3/bmp3.h"

// The name must be serial_port so that mbed can redirect correctly
static BufferedSerial serial_port(DEBUG_TX, DEBUG_RX, 9600);
#ifdef USING_SPI
SPI bmp388_spi(BMP388_MOSI, BMP388_MISO, BMP388_SCLK, BMP388_CS, use_gpio_ssel);
#else
I2C bmp388_i2c(BMP388_SDA, BMP388_SCL);
#endif

int8_t bmp3_regread(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len) {
#ifdef USING_SPI
  bmp388_spi.select();
  bmp388_spi.write(reg_addr);
  for (uint16_t i = 0; i < len; i++)
    data[i] = bmp388_spi.write(0x00);
  bmp388_spi.deselect();
  return BMP3_OK;
#else
  return bmp388_i2c.read(reg_addr, (char*) data, len);
#endif
}

int8_t bmp3_regwrite(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len) {
#ifdef USING_SPI
  bmp388_spi.select();
  for (uint16_t i = 0; i < len; i++) {
    bmp388_spi.write(reg_addr);
    bmp388_spi.write(data[i]);
  }
  bmp388_spi.deselect();
  return BMP3_OK;
#else
  return bmp388_i2c.write(reg_addr, (char*) data, len);
#endif
}

void bmp3_delay_ms(long unsigned int n) {
  thread_sleep_for(n);
}

int main() {
#ifdef USING_SPI
  bmp388_spi.format(8,0);
  bmp388_spi.frequency(1000000 / 2);
#else
  bmp388_i2c.frequency(100000); // 100khz
#endif

  struct bmp3_dev dev;
  int8_t rslt = BMP3_OK;

  /* Sensor_0 interface over SPI with native chip select line */
  dev.dev_id = 0;
  dev.intf = BMP3_SPI_INTF;
  dev.read = bmp3_regread;
  dev.write = bmp3_regwrite;
  dev.delay_ms = bmp3_delay_ms;

  rslt = bmp3_init(&dev);
  if (rslt != BMP3_OK)
    while(1) printf("bmp3_init failed\r\n");
  dev.settings.press_en = BMP3_ENABLE;
  dev.settings.temp_en = BMP3_ENABLE;
  rslt = bmp3_set_sensor_settings(BMP3_PRESS_EN_SEL | BMP3_TEMP_EN_SEL, &dev);
  if (rslt != BMP3_OK)
    while(1) printf("bmp3_set_sensor_settings failed\r\n");
  dev.settings.op_mode = BMP3_NORMAL_MODE;
  rslt = bmp3_set_op_mode(&dev);
  if (rslt != BMP3_OK)
    while(1) printf("bmp3_set_op_mode failed\r\n");

  struct bmp3_data data;
  while(1)
    if (bmp3_get_sensor_data(BMP3_ALL, &data, &dev) == BMP3_OK)
//      printf("pressure: %f, temperature: %f\r\n", data.pressure, data.temperature);
        printf("Altitude: %f\r\n", (1 - pow(data.pressure / 100 / 1013.25, 0.190284)) * 145366.45);
    else
      printf("reading failed\r\n");

  return 0;
}

