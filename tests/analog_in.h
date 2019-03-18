
/*
 * CalSTAR Avionics Test: Analog In
 *
 * file: analog_in.cpp
 *
 * Continuously reads from the analog input pin
 * and writes the battery voltage to UART
 */
#include "mbed.h"
#include <cmath>

#define BAUDRATE (115200)

// analog in is 0-1 from gnd to VCC (3.3V)
// so multiply by 3.3V first, then multiply by inverse of resistive divider
// (92.2kOhm / 502.2kOhm)
// then we have a recalibration factor added at the end
#define AIN_TO_VOLTAGE (3.3f * 502.2f / 92.2f * 1.10201042442293f)

int run_test() {
  Serial pc(DEBUG_TX, DEBUG_RX);
  pc.baud(BAUDRATE);
  pc.set_blocking(false);

  AnalogIn battVoltage(BATT_VOLTAGE);

  while (true) {
    pc.printf("Reading %f = %f V\r\n", (float)battVoltage, round(((float)battVoltage) * AIN_TO_VOLTAGE * 100.0f)/100.0f);
  }

  return 0;
}
