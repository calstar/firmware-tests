build:
	mbed compile -D $(test) -D $(board)

flash:
	st-flash write BUILD/NUCLEO_F401RE/GCC_ARM/