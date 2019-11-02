#include "mbed.h"
#include "lib/MPU9250AHRS/MPU9250.h"
#include "util.h"

#define BAUDRATE (115200)
Serial debug_talk(DEBUG_TX, DEBUG_RX);
MPU9250 mpu;

int run_test() {
    // Could just use:
    // https://os.mbed.com/users/onehorse/code/MPU9250AHRS/file/4e59a37182df/main.cpp/
    led_color(0, 1, 0);
    debug_talk.baud(BAUDRATE);
    debug_talk.printf("Begin imu test\r\n");
    mpu.initMPU9250();
    
    while(true) {
        uint8_t whoami = mpu.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
        debug_talk.printf("Whoami: 0x%x\r\n", whoami);

        // uint8_t pwr_mgmt_1 = mpu.readByte(MPU9250_ADDRESS, PWR_MGMT_1);
        // debug_talk.printf("PWR_MGMT_1: 0x%x\r\n", pwr_mgmt_1);

        // uint8_t gyro_cfg = mpu.readByte(MPU9250_ADDRESS, GYRO_CONFIG);
        // debug_talk.printf("GYRO_CONFIG: 0x%x\r\n", gyro_cfg);

        if (whoami == 0x71) {
            debug_talk.printf("Successfully connected\r\n");
        } else {
            debug_talk.printf("Failed to connect to IMU\r\n");
        }
    }
}
