ROOT_RISCV_FORMAL := ~/src/riscv-formal
ROOT_PROJECT := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

SRCS_FIRMWARE := crt0.s stdlib.c dhry1.c dhry2.c

SRCS_RTL := top.py $(shell find src/rtl -name \*.py)
SRCS_FORMAL := $(wildcard platform/formal/*)

SRCS_FIRMWARE := $(SRCS_FIRMWARE:%=src/firmware/%)
OBJS_FIRMWARE := $(SRCS_FIRMWARE:src/firmware/%=build/firmware/%.o)

TESTS_INSN := lui auipc jal jalr beq bne blt bge bltu bgeu lb lh lw lbu lhu sb sh sw addi slti sltiu xori ori andi slli srli srai add sub sll slt sltu xor srl sra or and
TESTS_XTRA := reg causal pc_fwd pc_bwd
TESTS_ALL := $(foreach test,${TESTS_XTRA},$(test)_ch0) $(foreach test,${TESTS_INSN},insn_$(test)_ch0)

CC=riscv64-unknown-elf-gcc
CFLAGS=-save-temps=obj -MD -O3 -DRISCV -DTIME -DUSE_MYSTDLIB -ffreestanding -mstrict-align -mno-riscv-attribute
TARGET_ARCH=-march=rv32i -mabi=ilp32
LDFLAGS=-nostdlib -mno-riscv-attribute -Wl,--strip-debug,-T,src/firmware/script.ld,-Map,build/firmware/firmware.map

all: cxxrtl

cxxrtl: sim
	mkdir -p build/cxxrtl
	yosys -p "read_rtlil build/sim/top.il; write_cxxrtl build/cxxrtl/top.cpp"
	clang++ -g -O3 -std=c++14 -I $(shell yosys-config --datdir)/include -I build/cxxrtl platform/cxxrtl/main.cpp -o build/cxxrtl/sim

sim: firmware
	python top.py sim

simwave: sim
	gtkwave build/sim/top.vcd platform/sim/sim.gtkw&

formal: $(foreach test, ${TESTS_ALL}, build/formal/checks/$(test)/PASS)
	@echo
	@files_fail="$(shell find build/formal -name FAIL -exec dirname {} \;)" && \
	files_pass="$(shell find build/formal -name PASS -exec dirname {} \;)" && \
	for i in $$files_fail; do \
		[ $$sep ] && echo && echo --------------------------------------------------------------------------------; \
		python platform/formal/disasm.py $$i/engine_0/trace.vcd build/formal/$$(basename $$i); \
		echo; \
		grep "Assert failed" $$i/logfile.txt; \
		sep=1; \
	done | tee build/formal/asserts.txt && \
	echo && echo -------------------------------------------------------------------------------- && \
	echo -n " PASS: " && echo -n "$$files_pass" | wc -w && \
	echo -n " FAIL: " && echo "$$files_fail" | wc -w && for i in $$files_fail; do echo $$i/engine_0/trace.vcd; done

firmware: build/firmware.bin

prog: build/arty/top.bit platform/arty/digilent_arty.cfg
	openocd -f platform/arty/digilent_arty.cfg -c "init;pld load 0 $<;shutdown"

clean:
	rm -rf build

mig: build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci

arty: ${RTL_SRCS} firmware
	python top.py arty

.PHONY: all sim simwave formal firmware arty prog clean mig arty

################################################################################

build/firmware/firmware.elf: ${OBJS_FIRMWARE} src/firmware/script.ld
	$(LINK.o) $(OUTPUT_OPTION) ${OBJS_FIRMWARE} -lgcc

build/firmware.bin: build/firmware/firmware.elf
	riscv64-unknown-elf-objcopy -O binary $< $@

build/firmware/%.c.o: src/firmware/%.c | build/firmware
	$(COMPILE.c) $(OUTPUT_OPTION) $<

build/firmware/%.s.o: src/firmware/%.s | build/firmware
	$(COMPILE.c) $(OUTPUT_OPTION) $<

build/firmware:
	mkdir -p $@

build/formal/checks/%/PASS: ${SRCS_RTL} ${SRCS_FORMAL} | build/formal/checks
	rm -rf $(dir $@)
	PYTHONPATH=${ROOT_PROJECT}/src/rtl make -C build/formal/checks $*

build/formal/checks: ${SRCS_RTL} ${SRCS_FORMAL} | build/formal
	cp ${SRCS_FORMAL} build/formal
	cd build/formal&&python ${ROOT_RISCV_FORMAL}/checks/genchecks.py checks ${ROOT_RISCV_FORMAL} ${ROOT_PROJECT}/platform/formal

build/formal:
	mkdir -p build/formal

build/arty/top.bit: ${RTL_SRCS} #build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci
	python top.py arty

build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci: mig.tcl mig_a.prj
	mkdir -p build/vivado
	vivado -mode batch -source mig.tcl -nolog -nojournal

