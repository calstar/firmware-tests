#include "mbed.h"

#define UART_BAUDRATE (115200)
#define GPS_BAUDRATE (9600)

int run_test(){
    UnbufferedSerial pc_dev(DEBUG_TX, DEBUG_RX, UART_BAUDRATE);
    FILE* pc = fdopen(&pc_dev, "w");

    UnbufferedSerial gps_uart_dev(GPS_TX, GPS_RX, GPS_BAUDRATE);
    FILE* gps_uart = fdopen(&gps_uart_dev, "w");

    while (true) {
        // while (pc.readable()) {
        //     gps_uart.putc(pc.getc());
        // }
        while (gps_uart.readable()) {
            pc.putc(gps_uart.getc());
        }
    }

    return 0;
}
