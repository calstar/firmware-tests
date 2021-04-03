/*
 * Test: Radio Transmitter
 * Transmits strings at 1s intervals. Blinks an LED upon send, and writes "sent" over UART.
 * Use in combination with test 'Radio Receiver' to verify 
 * transmitting-receiving works between two boards.
 * 
 * STAR Avionics
 * https://star.berkeley.edu
 */

#include "mbed.h"
#include "pins.h"
#include "RFM69/RFM69.hpp"
#include <string>

#define BAUDRATE 115200
#define ENCRYPT_KEY "CALSTARENCRYPTKE"

int main() {
    BufferedSerial uart(DEBUG_TX, DEBUG_RX, BAUDRATE);
    
    char buf[] = "Starting Radio Transmitter test\n";
    uart.write(buf, sizeof(buf));

    const std::string strs[4] = {"hello", "what", "great how about this", "and this\r\n"};
    
    DigitalOut led(USER_LED);
    led = 0;

    RFM69 radio(SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_CS, RADIO_RST, true);
    radio.reset();
    radio.init();
    radio.setAESEncryption(ENCRYPT_KEY, strlen(ENCRYPT_KEY));
    radio.setHighPowerSettings(true);
    radio.setPowerDBm(20);
    
    uint8_t i = 0;
    while (true) {
        const std::string &str = strs[i%4];
        radio.send(str.c_str(), str.length());
        ++i;
        led = 1;
        ThisThread::sleep_for(500ms);
        led = 0;
        ThisThread::sleep_for(500ms);
        uart.write("sent\n", sizeof("sent\n"));
    }
}