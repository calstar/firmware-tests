build_target = NUCLEO_F401RE
build_toolchain = GCC_ARM
project_name = firmware-tests

outdir = out/
outname = $(test)_$(board).bin
outpath = $(outdir)$(outname)
build_dir = BUILD/$(build_target)/$(build_toolchain)/

validate:
ifndef board
		$(error board is not set)
endif
ifndef test
		$(error test is not set)
endif

build: validate 
	time mbed compile --target $(build_target) --toolchain $(build_toolchain) --source mbed-os --source lib --source pins/$(board) --source $(test) \
		&& mkdir -p $(outdir) && cp $(build_dir)/mbed-os.bin $(outpath) \
	&& echo "Copied output to $(outpath)"

flash: build
	st-flash write $(outpath) 0x8000000

