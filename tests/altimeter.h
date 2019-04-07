#include "mbed.h"
#include "lib/MPL3115A2/MPL3115A2.h"
#include "util.h"
#include <string>

using namespace std;

#define BAUDRATE 9600
I2C i2c_sensors(I2C_SENSOR_SDA, I2C_SENSOR_SCL);
Serial debug_talk(DEBUG_TX, DEBUG_RX);

//Altitude altitude;
//MPL3115A2 alt(&i2c_sensors, &debug_talk);

#define SLAVE_ADDRESS 0xC0

void I2C_WriteVerify(uint8_t data) {
    int result = i2c_sensors.write(data);
    if (result != 1) {
        debug_talk.printf("I2C write failed: 0x%x\n", data);
    }
}

void I2C_RegWrite(uint8_t reg, uint8_t data) {
    i2c_sensors.start();
    I2C_WriteVerify(SLAVE_ADDRESS);
    I2C_WriteVerify(reg);
    I2C_WriteVerify(data);
}

int8_t I2C_RegRead(uint8_t reg) {
    i2c_sensors.start();
    I2C_WriteVerify(SLAVE_ADDRESS);
    I2C_WriteVerify(reg);
    i2c_sensors.start();
    I2C_WriteVerify(SLAVE_ADDRESS | 0x01);
    return i2c_sensors.read(0);
}

int run_test() {
    led_color(1, 0, 0);
    debug_talk.baud(BAUDRATE);
    debug_talk.printf("\nBegin altimeter test\n");
    I2C_RegWrite(0x26, 0xB8);
    I2C_RegWrite(0x13, 0x07);
    I2C_RegWrite(0x26, 0xB9);
    uint8_t whoami = I2C_RegRead(0x0C);
    debug_talk.printf("Whoami: 0x%x\n", whoami);
    if (whoami == 0xC4) {
        debug_talk.printf("Successfully connected\n");
        while (true) {
            debug_talk.printf("\n");
            uint8_t status = I2C_RegRead(0x00);
            debug_talk.printf("Status: %d\n", status);
            if (status & 0x08) {
                int32_t p_msb = I2C_RegRead(0x01);
                int32_t p_csb = I2C_RegRead(0x02);
                int32_t p_lsb = I2C_RegRead(0x03);
                int32_t t_msb = I2C_RegRead(0x04);
                int32_t t_lsb = I2C_RegRead(0x05);
                debug_talk.printf("Data: %d %d %d %d %d\n", p_msb, p_csb, p_lsb, t_msb, t_lsb);
                //double altitude = ((p_msb << 24) + (p_csb << 16) + (p_lsb << 8)) / 65536;
                float tempcsb = (p_lsb>>4) / 16.0;
                float altitude = (float)((p_msb << 8) | p_csb) + tempcsb;
                debug_talk.printf("Altitude: %f\n", altitude);
            }
            wait(1);
        }
    } else {
        debug_talk.printf("Failed to connect to altimeter, whoami: 0x%x\n", whoami);
    }
}