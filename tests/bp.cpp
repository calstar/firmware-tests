#include "mbed.h"

int run_test() {
    DigitalOut bp7_ig(BP7_IGNITE);
    bp7_ig = 0;

    while (true) {
        bp7_ig = 1;
        wait(0.5);
        bp7_ig = 0;
        wait(0.5);
    }
    return 0;
}