// Kinda annoying, didn't see an mbed option for -include though
#ifdef bb
#include "pins/bb.h"
#endif
#ifdef fc
#include "pins/fc.h"
#endif
#ifdef gs
#include "pins/gs.h"
#endif
#ifdef tpc
#include "pins/tpc.h"
#endif

#ifdef altimeter
#include "tests/altimeter.h"
#endif
#ifdef bp
#include "tests/bp.h"
#endif
#ifdef imu
#include "tests/imu.h"
#endif
#ifdef led
#include "tests/led.h"
#endif
#ifdef rs422_receiver
#include "tests/RS422_RECEIVER.h"
#endif
#ifdef rs422
#include "tests/rs422.h"
#endif
#ifdef gs_dio
#include "tests/groundstation_dio.h"
#endif
#ifdef puts_chars_continuous
#include "tests/puts_chars_continuous.h"
#endif
#ifdef echo
#include "tests/echo.h"
#endif
#ifdef pinger
#include "tests/pinger.h"
#endif
#ifdef receiver
#include "tests/receiver.h"
#endif

int main() {
    return run_test();
}
