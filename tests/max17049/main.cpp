#include "mbed.h"
#include "pins.h"
#include "util.h"
#include "MAX17049/MAX17048.h"

static BufferedSerial serial_port(DEBUG_TX, DEBUG_RX, 9600);
MAX17048 device(MAX17049_SDA, MAX17049_SCL, 100000); // 100kHz

const char* alert_message[] = {
    "reset",
    "voltage too high",
    "voltage too low",
    "voltage reset",
    "battery low",
    "SOC changed",
};

// Note: this test uses default setting for all alerts and hibernation/sleep voltage.
// To test other setting, see the header file (MAX17049/MAX17048.h) for functions to do so.
int main() {
    if (!device.open())
        while(1) printf("Fuel gauge initialization failed/not found\r\n");
    device.reset();

    while (1) {
        printf("Cell voltage: %f, SOC: %f, SOC change rate: %f\r\n", device.vcell(), device.soc(), device.crate());
        if (device.alerting()) {
            char alert = device.alertFlags();
            if (alert) {
                printf("\r\nALERT present:");
            }
            for (size_t i = 0; i < 6; i++) {
                if (alert & (1 << i)) {
                    printf("%s, ", alert_message[i]);
                }
            }
            if (alert) {
                printf("\r\n");
                device.clearAlert();
            }
        }
    }

    return 0;
}
