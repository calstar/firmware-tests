#include "mbed.h"
#include "lib/MPU9250AHRS/MPU9250.h"
#include "util.h"

#define BAUDRATE (115200)
BufferedSerial debug_talk_dev(DEBUG_TX, DEBUG_RX, BAUDRATE);
MPU9250 mpu;

int run_test() {
    // Could just use:
    // https://os.mbed.com/users/onehorse/code/MPU9250AHRS/file/4e59a37182df/main.cpp/
    led_color(0, 1, 0);
    FILE* debug_talk = fdopen(&debug_talk_dev, "w");
    fprintf(debug_talk, "Begin imu test\r\n");
    mpu.initMPU9250();
    
    while(true) {
        uint8_t whoami = mpu.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
        fprintf(debug_talk, "Whoami: 0x%x\r\n", whoami);

        // uint8_t pwr_mgmt_1 = mpu.readByte(MPU9250_ADDRESS, PWR_MGMT_1);
        // fprintf(debug_talk, "PWR_MGMT_1: 0x%x\r\n", pwr_mgmt_1);

        // uint8_t gyro_cfg = mpu.readByte(MPU9250_ADDRESS, GYRO_CONFIG);
        // fprintf(debug_talk, "GYRO_CONFIG: 0x%x\r\n", gyro_cfg);

        if (whoami == 0x71) {
            fprintf(debug_talk, "Successfully connected\r\n");
        } else {
            fprintf(debug_talk, "Failed to connect to IMU\r\n");
        }
    }
}
