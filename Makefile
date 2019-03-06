build: common_generated.h
	if time mbed compile --target NUCLEO_F401RE --toolchain GCC_ARM -D$(board) -D$(test) ; then mkdir -p out/ && cp BUILD/NUCLEO_F401RE/GCC_ARM/firmware-tests.bin out/test-$(board)-$(test).bin && echo "Copied output to out/test-$(board)-$(test).bin" ; fi

flash:
	st-flash write BUILD/NUCLEO_F401RE/GCC_ARM/flight_computer.bin 0x8000000

common_generated.h: flatc/common.fbs
	flatc/flatc --cpp flatc/common.fbs