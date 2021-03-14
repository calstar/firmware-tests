Firmware Tests
================

Unit testing specific functionality of each board.

# Setup

Clone the repo, run `mbed deploy` from the root of the repo to get the mbed files,
and then clone the submodules via `git submodule update --init --recursive`.

# How to build a test
* Run `make build board=$BOARD test=$TEST` to compile and copy the `.bin` to `out/$TEST_$BOARD.bin`.
    * `$BOARD` must be one of: 
      * `cas` (Common Avionics System)
      * `bb` (Black Box)
      * `gs` (Ground Station).
    * `$TEST` must be the directory name of the test to compile. One of:
      * `uart_echo`
      * `led`

Example: `make build board=cas test=uart_echo`

# How to add a new test
Create a directory with the test's name and place its source code in there.

**TODO**: implement the below.

If the test requires a certain board, specify this by placing the relevant of 
the following before including any headers in the main file: 
 `#define REQUIRE_$BOARD`, e.g. `#define REQUIRE_CAS`

For CAS tests, to include specific module pin definitions, add the following as needed:
* `#define REQUIRE_CAS_PYRO`
* `#define REQUIRE_CAS_RADIO`
* `#define REQUIRE_CAS_PROP`

# How to add a new board

Add a new subdirectory to the `pins` folder with the board's name.
If the board is a submodule of CAS, instead add a file titled `cas_<module name>.h`
in `pins/cas` and edit the `pins/cas/pins.h` file to include the new module file
when needed. 

# Relevant Folders
* `pins`: contains pin definitions by board.
* `lib`: Libraries submodule.