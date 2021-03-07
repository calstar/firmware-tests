// CAS Core Module Pin Definition

// SPI High Speed Bus (SPI1)
#define SPIHS_SCK PA_5
#define SPIHS_MISO PA_6
#define SPIHS_MOSI PA_7

#define SPIHS_NSS1 PC_7
#define SPIHS_NSS2 PC_4

// SPI Bus (SPI2)
#define SPI_BUS_SCK PB_10
#define SPI_BUS_MISO PC_2
#define SPI_BUS_MOSI PC_3

#define SPI_BUS_NSS1 PB_9
#define SPI_BUS_NSS2 PC_13
#define SPI_BUS_NSS3 PC_14
#define SPI_BUS_NSS4 PC_15
#define SPI_BUS_NSS5 PH_0
#define SPI_BUS_NSS6 PH_1
#define SPI_BUS_NSS7 PC_0
#define SPI_BUS_NSS8 PC_1

// SD Card and I2C1 Bus through bridge (SPI3)
#define SPI_BRIDGE_SCK PC_10
#define SPI_BRIDGE_MISO PC_11
#define SPI_BRIDGE_MOSI PC_12

#define SPI_BRIDGE_SD_NSS PA_4
#define SPI_BRIDGE_I2C_NSS PC_8

// I2C0 Bus (I2C1)
#define I2C_BUS_SCL PB_8
#define I2C_BUS_SDA PB_7

// Core onboard sensors (I2C3)
#define I2C_SENSOR_SCL PA_8
#define I2C_SENSOR_SDA PC_9
