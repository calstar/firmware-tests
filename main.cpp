// Kinda annoying, didn't see an mbed option for -include though
#ifdef BLACKBOX
#include "pins/blackbox.h"
#endif
#ifdef FC
#include "pins/fc.h"
#endif
#ifdef GS
#include "pins/groundstation.h"
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
#ifdef GS_DIO
#include "tests/groundstation_dio.h" 
#endif
#ifdef PUTS_CHARS_CONTINUOUS
#include "tests/puts_chars_continuous.h"
#endif
#ifdef ECHO
#include "tests/echo.h"
#endif
#ifdef PINGER
#include "tests/pinger.h"
#endif
#ifdef RECEIVER
#include "tests/receiver.h"
#endif

int main() {
    return run_test();
}
