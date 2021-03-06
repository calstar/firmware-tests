#include "mbed.h"
#include "lib/MPL3115A2/MPL3115A2.h"
#include "lib/MPL3115A2/Altitude.h"
#include "util.h"

#define BAUDRATE (115200)
I2C i2c_sensors(I2C_SENSOR_SDA, I2C_SENSOR_SCL);
BufferedSerial debug_talk_dev(DEBUG_TX, DEBUG_RX, BAUDRATE);

Altitude altitude;
MPL3115A2 mpl(&i2c_sensors, &debug_talk);

int run_test() {
    led_color(0, 0, 1);

    mpl.init();
    mpl.setOversampleRate(0b000);
    mpl.setModeStandby();
    mpl.setModeAltimeter();
    mpl.setModeActive();

    FILE* debug_talk = fdopen(&debug_talk_dev, "w");
    fprintf(debug_talk, "\r\nBegin mpl test\r\n");
    uint8_t whoami = mpl.whoAmI();
    fprintf(debug_talk, "Whoami: 0x%x\r\n", whoami);
    if (whoami == 0xC4) {
        fprintf(debug_talk, "Successfully connected\r\n");
        Altitude a;
        Temperature t;
        Pressure p;
        fprintf(debug_talk, "Altitude (meters)\r\n");
        while (true) {
            mpl.readAltitude(&a);
            fprintf(debug_talk, "%f\r\n", a.altitude(Altitude::METERS));
        }
    } else {
        while (true) {
            fprintf(debug_talk, "Failed to connect to mpl, whoami: 0x%x\r\n", whoami);
        }
    }
}