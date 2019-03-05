#include "mbed.h"

void led_color(bool r, bool g, bool b) {
    DigitalOut led_red(STATE_LED_RED);
    DigitalOut led_green(STATE_LED_GREEN);
    DigitalOut led_blue(STATE_LED_BLUE);

    // Flip because common anode
    led_red.write(!r);
    led_green.write(!g);
    led_blue.write(!b);
}