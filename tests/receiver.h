/*
 * CalSTAR Avionics Test: Receiver
 *
 * file: receiver.cpp
 *
 * Prints anything it receives to UART.
 * Use to verify receive functionality of radio is working
 */

#include "RFM69/RFM69.hpp"
#include "mbed.h"
#include "common_generated.h"

#define BAUDRATE (115200)

using namespace flatbuffers;
using namespace Calstar;

int run_test() {

  DigitalOut rx_led(LED_RX);
  rx_led = 0;

  Serial pc(DEBUG_TX, DEBUG_RX);
  pc.baud(BAUDRATE);
  pc.set_blocking(false);

  RFM69 radio(SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_SSEL, RADIO_RST, true);
  radio.reset();
  pc.printf("radio reset\r\n");

  radio.init();
  pc.printf("radio init'd\r\n");

  radio.setAESEncryption("sampleEncryptKey", strlen("sampleEncryptKey"));
  radio.sleep();

  radio.setPowerDBm(10);
  pc.printf("radio high powered\r\n");

  radio.setCSMA(true);

  char rx[64]; /* NOTE: This may be too low for strings we will be receiving. Perhaps make decently larger */
  while (true) {
    rx_led = 0;

    int bytes_rxd = radio.receive(rx, sizeof(rx));
    if (bytes_rxd > 1) {
      rx_led = 1;
      rx[bytes_rxd] = '\0';
      char *data = &rx[1];
      const TPCData *tpc_data = GetTPCData(data);
      pc.printf("[rssi: %d, bytes received: %d] bat v: %f, gps string: %s, state: %d \r\n", radio.getRSSI(),
                bytes_rxd, tpc_data->BatteryVoltage(), tpc_data->GPSString()->str(), tpc_data->State());
    }
  }
  return 0;
}
