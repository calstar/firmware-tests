/*
 * CalSTAR Avionics Test: Pinger
 *
 * file: pinger.cpp
 *
 * Sends out the string "wiuwlehfliaw" at 0.5 second intervals, and puts the
 *    char 'h' over UART when it does so.
 * Use to verify that the Ground Station can send properly.
 */

#include "lib/RFM69/RFM69.hpp"
#include "mbed.h"
#include "common_generated.h"

#define BAUDRATE (115200)

using namespace flatbuffers;
using namespace Calstar;

int run_test() {
  FlatBufferBuilder builder(1024);
  TPCState tpcState = TPCState_Pad;
  Offset<String> gpsString = builder.CreateString("Sample GPS String");
  float batteryVoltage = 14.8f;

  Offset<TPCData> tpcData = CreateTPCData(builder, tpcState, gpsString, batteryVoltage);
  builder.Finish(tpcData);

  uint8_t* buf = builder.GetBufferPointer();
  int size = builder.GetSize();

  UnbufferedSerial pc_dev(DEBUG_TX, DEBUG_RX, BAUDRATE);
  FILE* pc = fdopen(&pc_dev, "w");

  RFM69 radio(SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_SSEL, RADIO_RST, true);
  radio.reset();
  fprintf(pc, "radio reset\r\n");

  radio.init();
  fprintf(pc, "radio init'd\r\n");

  radio.setAESEncryption("sampleEncryptKey", strlen("sampleEncryptKey"));
  radio.sleep();

  radio.setPowerDBm(10);
  fprintf(pc, "radio high powered\r\n");

  radio.setCSMA(true);

  while (true) {
    radio.send(buf, size);
    radio.sleep();
    fprintf(pc, "sent flatbuffer string\r\n");
    wait(0.5);
  }
  return 0;
}
