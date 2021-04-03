/*
 * Test: Radio Receiver
 * Receives over radio. On receive, blinks an led and writes the received string over UART.
 * Use in combination with test 'Radio Transmitter' to verify 
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
    
    char buf[] = "Starting Radio Receiver test\n";
    uart.write(buf, sizeof(buf));
    
    DigitalOut led(USER_LED);
    led = 0;

    RFM69 radio(SPI1_MOSI, SPI1_MISO, SPI1_SCLK, SPI1_CS, RADIO_RST, true);
    radio.reset();
    radio.init();
    radio.setAESEncryption(ENCRYPT_KEY, strlen(ENCRYPT_KEY));
    radio.setHighPowerSettings(true);
    radio.setPowerDBm(20);

    char rx_buf[512];
    int bytes_rxd = 0;
    
    while (true) {
        bytes_rxd = radio.receive(rx_buf, sizeof(rx_buf));
        if (bytes_rxd > 1)  {
            rx_buf[bytes_rxd] = '\0';
            led = 1;
            uart.write(rx_buf, bytes_rxd + 1);
            ThisThread::sleep_for(100ms);
            led = 0;
        }
    }
}