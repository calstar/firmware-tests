// Kinda annoying, didn't see an mbed option for -include though
#ifdef BLACKBOX
#include "pins/blackbox.h"
#endif
#ifdef FC
#include "pins/fc.h"
#endif

#ifdef ALTIMETER
#include "tests/altimeter.h"
#endif
#ifdef BP
#include "tests/bp.h"
#endif
#ifdef IMU
#include "tests/imu.h"
#endif
#ifdef LED
#include "tests/led.h"
#endif
#ifdef RS422_RECEIVER
#include "tests/RS422_RECEIVER.h"
#endif
#ifdef RS422
#include "tests/rs422.h"
#endif

int main() {
    run_test();
}
