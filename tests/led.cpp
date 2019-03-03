#include "mbed.h"
#include "util.h"

int run_test() {
    while (true) {
        for (int r = 0; r < 2; r++) {
            for (int g = 0; g < 2; g++) {
                for (int b = 0; b < 2; b++) {
                    led_color(r, g, b);
                    wait(1);
                }
            }
        }
    }
    return 0;
}