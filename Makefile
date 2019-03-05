build:
	time mbed compile --target NUCLEO_F401RE --toolchain GCC_ARM -D$(test) -D$(board)

flash:
	st-flash write BUILD/NUCLEO_F401RE/GCC_ARM/flight_computer.bin 0x8000000