build:
	mbed compile -D $(test) -D $(board)

flash:
	st-flash write BUILD/NUCLEO_F401RE/GCC_ARM/flight_computer.bin 0x8000000