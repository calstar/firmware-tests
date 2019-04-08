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
#ifdef flatbuf_receiver
#include "tests/flatbuf_receiver.h"
#endif
#ifdef radio_passthrough
#include "tests/radio_passthrough.h"
#endif
#ifdef analog_in
#include "tests/analog_in.h"
#endif
#ifdef gps
#include "tests/gps.h"
#endif
#ifdef radio_pinger
#include "tests/radio_pinger.h"
#endif
#ifdef radio_bits_per_sec
#include "tests/radio_bits_per_sec.h"
#endif

int main() {
    return run_test();
}
