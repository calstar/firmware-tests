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
#include "tests/altimeter.cpp"
#endif
#ifdef BP
#include "tests/bp.cpp"
#endif
#ifdef IMU
#include "tests/imu.cpp"
#endif
#ifdef LED
#include "tests/led.cpp"
#endif
#ifdef RS422_RECEIVER
#include "tests/RS422_RECEIVER.cpp"
#endif
#ifdef RS422
#include "tests/rs422.cpp"
#endif
#ifdef GS_DIO
#include "tests/groundstation_dio.cpp" 
#endif
#ifdef PUTS_CHARS_CONTINUOUS
#include "tests/puts_chars_continuous.cpp"
#endif
#ifdef ECHO
#include "tests/echo.cpp"
#endif
#ifdef PINGER
#include "tests/pinger.cpp"
#endif
#ifdef RECEIVER
#include "tests/receiver.cpp"
#endif

int main() {
    run_test();
}
