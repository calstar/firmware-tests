# How to build
Run `make build board=FC test=LED`, replacing FC with the board and LED with the test to run

## Why are all the files .h instead of cpp?
Because of the way mbed building works, changing all of them to headers seemed to be the easiest way to get the conditional compilation to work. If they're .cpp, the lack of defined symbols will throw errors when compiling.
