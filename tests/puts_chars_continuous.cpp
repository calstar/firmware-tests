
/*
 * CalSTAR Avionics Test: Puts Chars Continuous
 *
 * file: puts_chars_continuous.cpp
 *
 * Continuously puts the character 'h' over UART.
 * Use to verify UART tx from board works.
 */
#include "mbed.h"

#define BAUDRATE (115200)

int run_test() {
  Serial pc(DEBUG_TX, DEBUG_RX);
  pc.baud(BAUDRATE);
  pc.set_blocking(false);

  while (true) {
    pc.putc('h');
  }
}
