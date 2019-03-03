#include "mbed.h"
#include "RFM69/RFM69.h"

// This file hasn't been unified with the pin definitions from the pins folder

#define NODE_ID (11)
#define NETWORK_ID (100)
#define FREQUENCY (RF69_433MHZ)
#define TRANSMIT_TO (255)
#define IS_RFM69HCW
#define ENCRYPT_KEY "sampleEncryptKey"
#define BAUDRATE (115200)

#define RADIO_INT (PC_0)
#define SPI1_MOSI (PA_7)
#define SPI1_MISO (PA_6)
#define SPI1_SCLK (PA_5)
#define SPI1_SSEL (PA_4)
#define RADIO_RST (PC_1)

#define UART_FC_RX (PC_7)
#define UART_FC_TX (PC_6)

#define UART_GPS_RX (PA_10)
#define UART_GPS_TX (PA_9)

#define UART_DEBUG_RX (PA_3)
#define UART_DEBUG_TX (PA_2)

#define FC_SWITCH (PB_13)
//#define EC_SWITCH (PB_12)

#define BATTERY_READ (PC2)

int run_test(){
    Serial pc(UART_DEBUG_TX, UART_DEBUG_RX);
    pc.baud(BAUDRATE);
    pc.printf("PC connected.\r\n");

    Serial fc(UART_FC_TX, UART_FC_RX);
    fc.baud(BAUDRATE);

    while(true){
        pc.printf("PC connected.\r\n");
        fc.printf("RS422 connected.\r\n");
    }
}
