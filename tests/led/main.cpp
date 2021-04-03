/*
 * Test: LED
 * Blinks LED on for 1 second then off for 1 second.
 *
 * STAR Avionics
 */ 

#include "mbed.h"
#include "pins.h"

int main() {
  DigitalOut led(USER_LED);
  led = 0;
  while (true) {
    led = 1;
    ThisThread::sleep_for(1s);
    led = 0;
    ThisThread::sleep_for(1s);
  }
}
