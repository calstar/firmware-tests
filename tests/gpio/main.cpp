#include "mbed.h"
#include "pins.h"
#include "util.h"

// Core GPIO Test - test all interrupt pins from the bus

// Print Redirect 
static BufferedSerial serial_port(DEBUG_TX, DEBUG_RX, 9600);

// GPIO array
BusIn gpio(INT1, INT2, INT3, INT4, INT5, INT6, INT7, INT8);

int main() {
    printf("Port value:\n");
    printf("00000000");
    while (1) {
        int value = gpio.read();
        printf("\b\b\b\b\b\b\b\b");
        for (int i = 0; i < 8; i++) {
            printf("%d ", value & 0b1);
            value >>= 1;
        }
        wait_us(10000);
    }
    return 0;
}