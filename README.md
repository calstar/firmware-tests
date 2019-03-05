# How to build
Run `make board=FC test=LED`, replacing FC with the board and LED with the test to run.
If compilation succeeds, the output .bin file will be placed in out/test-$BOARD-$TEST.bin (e.g. test-FC-LED.bin).

## Why are all the files .h instead of cpp?
Because of the way mbed building works, changing all of them to headers seemed to be the easiest way to get the conditional compilation to work. If they're .cpp, the lack of defined symbols will throw errors when compiling.

## How do I compile with flatbuffers?
The schema is located in flatc/common.fbs. Simply edit that, and next time you build with the makefile it will automatically recompile flatc/common.fbs into common_generated.h.