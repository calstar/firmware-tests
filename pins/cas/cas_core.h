/*
Default definitions for Common Avionics System (CAS) Core module.
*/

#ifndef CAS_CORE_H

#define DEBUG_TX PB_6
#define DEBUG_RX PA_10

#define USER_LED PB_4

#define SPI3_SCK  PC_10
#define SPI3_MISO PC_11
#define SPI3_MOSI PC_12

#define I2C3_SDA PC_9
#define I2C3_SCL PA_8

#define INT1 PA_1
#define INT2 PA_2
#define INT3 PA_3
#define INT4 PC_5
#define INT5 PB_0
#define INT6 PB_1
#define INT7 PB_14
#define INT8 PB_15

// Component definition
#define BMP388_SDA I2C3_SDA
#define BMP388_SCL I2C3_SCL

#define SD_CARD_SCK SPI3_SCK
#define SD_CARD_MISO SPI3_MISO
#define SD_CARD_MOSI SPI3_MOSI
#define SD_CARD_nSS PA_4

#define CAS_CORE_H

#endif
