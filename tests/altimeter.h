#include "mbed.h"
#include "lib/MPL3115A2/MPL3115A2.h"
#include "util.h"

#define BAUDRATE 9600
I2C i2c_sensors(I2C_SENSOR_SDA, I2C_SENSOR_SCL);
Serial debug_talk(DEBUG_TX, DEBUG_RX);

Altitude altitude;
MPL3115A2 altimeter(&i2c_sensors, &debug_talk);

int run_test() {
    led_color(0, 0, 1);
    altimeter.init();
    debug_talk.baud(BAUDRATE);
    debug_talk.printf("\nBegin altimeter test\n");
    uint8_t whoami = altimeter.whoAmI();
    debug_talk.printf("Whoami: 0x%x\n", whoami);
    if (whoami == 0xC4) {
        debug_talk.printf("Successfully connected\n");
        Altitude a;
        Temperature t;
        Pressure p;
        altimeter.setOffsetAltitude(83);
        altimeter.setOffsetTemperature(20);
        altimeter.setOffsetPressure(-32);
        while (true) {


        altimeter.readAltitude(&a);
        altimeter.readTemperature(&t);
        
        altimeter.setModeStandby();
        altimeter.setModeBarometer();
        altimeter.setModeActive();
        altimeter.readPressure(&p);
        
        debug_talk.printf("Altitude: %sft, Temp: %sºF, Pressure: %sPa\r\n", a.print(), t.print(), p.print());
        debug_talk.printf("OFF_H: 0x%X, OFF_T: 0x%X, OFF_P: 0x%X\r\n", altimeter.offsetAltitude(), altimeter.offsetTemperature(), altimeter.offsetPressure());
    
        altimeter.setModeStandby();
        altimeter.setModeAltimeter();
        altimeter.setModeActive();
        }
    } else {
        while (true) {
            debug_talk.printf("Failed to connect to altimeter, whoami: 0x%x\n", whoami);
        }
    }
}
