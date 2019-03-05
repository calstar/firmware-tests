#include "mbed.h"
#include "lib/MPU9250AHRS/MPU9250.h"
#include "util.h"

#define BAUDRATE 9600
I2C i2c_sensors(I2C_SENSOR_SDA, I2C_SENSOR_SCL);
Serial debug_talk(DEBUG_TX, DEBUG_RX);
MPU9250 imu;

int run_test() {

    // Could just use:
    // https://os.mbed.com/users/onehorse/code/MPU9250AHRS/file/4e59a37182df/main.cpp/
    led_color(0, 1, 0);
    debug_talk.baud(BAUDRATE);
    debug_talk.printf("\nBegin imu test\n");
    uint8_t whoami = imu.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
    debug_talk.printf("Whoami: 0x%x\n", whoami);
    if (whoami == 0x71) {
        debug_talk.printf("Successfully connected\n");
    } else {
        debug_talk.printf("Failed to connect to IMU\n");
    }
}