# firmware-tests
For firmware to test functionality of the boards

# How to build
* Run `make build board=$BOARD ` to compile flatbuffer schemas, build the `.bin` file, and copy it to `out/test-$BOARD-$TEST.bin`.
    * `$BOARD` must be one of: `bb` (Black Box), `fc` (Flight Computer), `gs` (Ground Station), `tpc` (Telemetry/Power Control).
    * `$TEST` must be the preprocessor directive corresponding to the test file you want to run (probably the file name without extension)

# How to add a new test
* Add a header file to tests/ and include it from main, surrounding it with #ifdefs for the filename

# Why are all the files .h instead of cpp?
* Because of the way mbed building works, changing all of them to headers seemed to be the easiest way to get the conditional compilation to work. If they're .cpp, the lack of defined symbols will throw errors when compiling.

# Relevant Folders
* The `pins` folder contains pin definitions for each board
* The `tests` folder contains test definitions
* The flatbuffer schemas are under `flatc/*.fbs` (more details below).
* `flatbuffers/` contains the necessary flatbuffer includes and should not be modified.
* After a build, `out/` will contain the output binary.

# Flatbuffers
* The schemas are under `flatc/*.fbs`. Edit them and the next time you run a `make build` command they will be recompiled by the `flatc` executable in `flatc/`.
