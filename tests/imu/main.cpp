#include "mbed.h"
#include "MPU9250AHRS/MPU9250.h"
#include "util.h"
#include "pins.h"

#define BAUDRATE (115200)
BufferedSerial serial_port(DEBUG_TX, DEBUG_RX, BAUDRATE);
MPU9250 mpu;

int main() {
    // Could just use:
    // https://os.mbed.com/users/onehorse/code/MPU9250AHRS/file/4e59a37182df/main.cpp/
    printf("Begin imu test\r\n");
    mpu.initMPU9250();
    
    while(true) {
        uint8_t whoami = mpu.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
        printf("Whoami: 0x%x\r\n", whoami);

        // uint8_t pwr_mgmt_1 = mpu.readByte(MPU9250_ADDRESS, PWR_MGMT_1);
        // printf("PWR_MGMT_1: 0x%x\r\n", pwr_mgmt_1);

        // uint8_t gyro_cfg = mpu.readByte(MPU9250_ADDRESS, GYRO_CONFIG);
        // printf("GYRO_CONFIG: 0x%x\r\n", gyro_cfg);

        if (whoami == 0x71) {
            printf("Successfully connected\r\n");
        } else {
            printf("Failed to connect to IMU\r\n");
        }
    }
}