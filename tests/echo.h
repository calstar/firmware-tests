/*
 * CalSTAR Avionics Test: Echo
 *
 * file: echo.cpp
 *
 * Reads from UART and responds with an 'r' and then the recieved character.
 * Upon recieve will also toggle LED_RX
 * Use to verify UART tx from board works.
 */

#include "mbed.h"

#define BAUDRATE (115200)

int main() {
  DigitalOut rx_led(LED_RX);
  rx_led = 0;

  UnbufferedSerial pc_dev(DEBUG_TX, DEBUG_RX, BAUDRATE);
  FILE* pc = fdopen(&pc_dev, "w");

  while (true) {
    if (pc.readable()) {
      pc.putc('r');
      pc.putc(pc.getc());
      if (rx_led.read() == 0) {
        rx_led = 1;
      } else {
        rx_led = 0;
      }
    }
  }
  return 0;
}
