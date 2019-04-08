/*
 * CalSTAR Avionics Test: Receiver
 *
 * file: receiver.cpp
 *
 * Prints anything it receives to UART.
 * Use to verify receive functionality of radio is working
 */

#include "msg_downlink_generated.h"
#include "msg_fc_update_generated.h"
#include "msg_uplink_generated.h"

#include "RFM69/RFM69.hpp"
// #include "common_generated.h"
#include "USBSerial.h"
#include "mbed.h"
#include <inttypes.h>

#define BAUDRATE (115200)

#define ENCRYPT_KEY "CALSTARENCRYPTKE"

using namespace flatbuffers;
using namespace Calstar;

int run_test() {

  DigitalOut rx_led(LED_RX);
  rx_led = 0;

  USBSerial pc;
  // Serial pc(DEBUG_TX, DEBUG_RX);
  // pc.baud(BAUDRATE);
  // pc.set_blocking(false);

  RFM69 radio(SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_SSEL, RADIO_RST, true);
  radio.reset();
  pc.printf("radio reset\r\n");

  radio.init();
  pc.printf("radio init'd\r\n");

  radio.setAESEncryption(ENCRYPT_KEY, strlen(ENCRYPT_KEY));
  // radio.sleep();

  radio.setHighPowerSettings(true);
  radio.setPowerDBm(20);
  pc.printf("radio high powered\r\n");

  // radio.setCSMA(true);

  char rx[512]; /* NOTE: This may be too low for strings we will be receiving.
                  Perhaps make decently larger */
  while (true) {
    // pc.putc('h');
    // rx_led = 0;

    int bytes_rxd = radio.receive(rx, sizeof(rx));
    if (bytes_rxd > 1) {
      if (rx_led.read() == 1) {
        rx_led = 0;
      } else {
        rx_led = 1;
      }
      pc.printf("R\r\n");
      rx[bytes_rxd] = '\0';
      char *data = &rx[1];

      pc.printf("[%s BYTES %d]", data, bytes_rxd - 1);
      bool found_s = false;
      int i = 0;
      for (i = 0; i < bytes_rxd - 1; ++i) {
        if (data[i] == 's') {
          found_s = true;
          break;
        }
      }
      if (found_s) {
        pc.printf("found s: %c %c %c %c\r\n", data[i], data[i + 1], data[i + 2],
                  data[i + 3]);
      }
      pc.printf("%d\r\n", *((int *)&data[i + 4]));
      // Verifier v((uint8_t *)&data[8], bytes_rxd - 1-12);
      // if (VerifyDownlinkMsgBuffer(v)) {
      // const DownlinkMsg *msg = GetDownlinkMsg(&data[i + 8]);
      // const uint8_t expectedBytes = msg->Bytes();
      // pc.printf("Expected: %d\r\n", expectedBytes);
      //   if (bytes_rxd - 1 > expectedBytes) {
      //     Verifier v2((uint8_t *)data, expectedBytes);
      //     if (VerifyDownlinkMsgBuffer(v2)) {

      // pc.printf("tstamp: %" PRIu64 ", bytes: %d, state: %d, fc.pwr: %d, "
      //           "gps string: %s, bat.v: %u, ",
      //           msg->TimeStamp(), (int)msg->Bytes(), (int)msg->State(),
      //           (int)msg->FCPowered(), msg->GPSString()->str().c_str(),
      //           (uint32_t)msg->BattVoltage());
      // if (msg->FCMsg()) {
      //   pc.printf(
      //       "bps: %d %d, %d %d, %d %d, %d %d, %d %d, %d %d, %d %d\r\n",
      //       (int)msg->FCMsg()->BP1Continuity(),
      //       (int)msg->FCMsg()->BP1Ignited(),
      //       (int)msg->FCMsg()->BP2Continuity(),
      //       (int)msg->FCMsg()->BP2Ignited(),
      //       (int)msg->FCMsg()->BP3Continuity(),
      //       (int)msg->FCMsg()->BP3Ignited(),
      //       (int)msg->FCMsg()->BP4Continuity(),
      //       (int)msg->FCMsg()->BP4Ignited(),
      //       (int)msg->FCMsg()->BP5Continuity(),
      //       (int)msg->FCMsg()->BP5Ignited(),
      //       (int)msg->FCMsg()->BP6Continuity(),
      //       (int)msg->FCMsg()->BP6Ignited(),
      //       (int)msg->FCMsg()->BP7Continuity(),
      //       (int)msg->FCMsg()->BP7Ignited());
      // }
      //       pc.printf("\r\n");
      //     } else {
      //       pc.printf("Failed expected bytes buffer verifier\r\n");
      //     }
      //   }
      // } else {
      //   pc.printf("Failed verify\r\n");
      // }
    }
  }
  return 0;
}
