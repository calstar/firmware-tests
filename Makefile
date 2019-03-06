build_target = "NUCLEO_F401RE"
build_toolchain = "GCC_ARM"
build_dir = "BUILD"
project_name = "firmware-tests"

outdir = "out/"
outname = "test-$(board)-$(test).bin"
outpath = "$(outdir)$(outname)"

build: common_generated.h
	time mbed compile --target $(build_target) --toolchain $(build_toolchain) -D$(board) -D$(test) \
	&& mkdir -p $(outdir) && cp $(build_dir)/$(build_target)/$(build_toolchain)/$(project_name).bin $(outpath) \
	&& echo "Copied output to $(outpath)"

flash:
	st-flash write $(outpath) 0x8000000

common_generated.h: flatc/common.fbs
	flatc/flatc --cpp flatc/common.fbs