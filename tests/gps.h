#include "mbed.h"

#define UART_BAUDRATE (115200)
#define GPS_BAUDRATE (9600)

int run_test(){
    Serial pc(DEBUG_TX, DEBUG_RX);
    pc.baud(UART_BAUDRATE);
    pc.set_blocking(false);

    Serial gps_uart(GPS_TX, GPS_RX);
    gps_uart.baud(GPS_BAUDRATE);
    gps_uart.set_blocking(false);

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
