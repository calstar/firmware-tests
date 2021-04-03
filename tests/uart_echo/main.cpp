/*
 * Test: UART Echo
 * Reads from UART and responds with an 'r' and then the received character.
 * Use to verify UART RX and TX from board works.
 *
 * STAR Avionics
 * https://stars.berkeley.edu
 */ 

#include "mbed.h"
#include "pins.h"

#define BAUDRATE 115200

int main() {
  BufferedSerial uart(DEBUG_TX, DEBUG_RX, BAUDRATE);
  char buf[2] = {'r', 0};
  char read_buf;
  while (true) {
    if (uart.readable()) {
      buf[1] = uart.read(&read_buf, 1);
      uart.write(buf, 2);
    }
  }
}
