#include "mbed.h"
#include "lib/MPL3115A2/MPL3115A2.h"
#include "lib/MPL3115A2/Altitude.h"
#include "util.h"

#define BAUDRATE 9600
I2C i2c_sensors(I2C_SENSOR_SDA, I2C_SENSOR_SCL);
Serial debug_talk(DEBUG_TX, DEBUG_RX);

Altitude altitude;
MPL3115A2 mpl(&i2c_sensors, &debug_talk);

int run_test() {
    led_color(0, 0, 1);

    mpl.init();
    mpl.setOversampleRate(0b000);
    mpl.setModeStandby();
    mpl.setModeAltimeter();
    mpl.setModeActive();

    debug_talk.baud(BAUDRATE);
    debug_talk.printf("\nBegin mpl test\n");
    uint8_t whoami = mpl.whoAmI();
    debug_talk.printf("Whoami: 0x%x\n", whoami);
    if (whoami == 0xC4) {
        debug_talk.printf("Successfully connected\n");
        Altitude a;
        Temperature t;
        Pressure p;
        while (true) {
            mpl.readAltitude(&a);
            debug_talk.printf("%f\n", a.altitude(Altitude::METERS));
        }
    } else {
        while (true) {
            debug_talk.printf("Failed to connect to mpl, whoami: 0x%x\n", whoami);
        }
    }
}