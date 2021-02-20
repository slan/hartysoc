RISCV_FORMAL_ROOT := ~/src/riscv-formal
PROJECT_ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

SRCS := $(shell find src/rtl -name \*.py)
INSNS_TESTS := \
	lui \
	auipc \
	jal \
	jalr \
	beq \
	bne \
	blt \
	bge \
	bltu \
	bgeu \
	lb \
	lh \
	lw \
	lbu \
	lhu \
	sb \
	sh \
	sw \
	addi \
	slti \
	sltiu \
	xori \
	ori \
	andi \
	slli \
	srli \
	srai \
	add \
	sub \
	sll \
	slt \
	sltu \
	xor \
	srl \
	sra \
	or \
	and \

OTHER_TESTS := reg causal pc_fwd pc_bwd
FORMAL_SRCS := $(wildcard platform/formal/*)
TESTS := $(foreach test,${OTHER_TESTS},$(test)_ch0) $(foreach test,${INSNS_TESTS},insn_$(test)_ch0)

_dummy := $(shell mkdir -p build)

CC=riscv64-unknown-elf-gcc
CFLAGS=-save-temps=obj -O3
TARGET_ARCH=-march=rv32i -mabi=ilp32
LDFLAGS=-nostdlib

all:
	echo 

build/%.o: %.s
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	#riscv64-unknown-elf-objdump -d -t -r $@

build/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	#riscv64-unknown-elf-objdump -d -t -r $@

build/main.elf: build/main.o
	$(LINK.o) $(OUTPUT_OPTION) $<
	#riscv64-unknown-elf-objdump -d -S -t -r $@

build/bootcode.elf: build/bootcode.o script.ld
	$(LINK.o) $(OUTPUT_OPTION) -T script.ld $<

simwave: sim
	gtkwave build/sim/top.vcd gtk-sim.gtkw&

formal: $(foreach test, ${TESTS}, build/formal/checks/$(test)/PASS)
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

build/formal/checks/%/PASS: ${SRCS} ${FORMAL_SRCS} | build/formal/checks
	rm -rf $(dir $@)
	PYTHONPATH=${PROJECT_ROOT}/src/rtl make -C build/formal/checks $*

build/formal/checks: ${SRCS} ${FORMAL_SRCS} | build/formal
	cp ${FORMAL_SRCS} build/formal
	cd build/formal&&python ${RISCV_FORMAL_ROOT}/checks/genchecks.py checks ${RISCV_FORMAL_ROOT} ${PROJECT_ROOT}/platform/formal

build/formal:
	mkdir -p build/formal

build/__init__.py: build/bootcode.elf
	@riscv64-unknown-elf-objcopy -O binary $< build/$*.tmp
	@echo "bootcode = [" > $@
	@hexdump build/$*.tmp -v -e "\"\t0x\" \"%08x,\n\"" >>$@
	@echo "]" >> $@

sim: build/__init__.py
	python top.py sim

arty: build/arty/top.bit

build/arty/top.bit: build/__init__.py #build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci
	python top.py arty

prog: build/arty/top.bit digilent_arty.cfg
	openocd -f digilent_arty.cfg -c "init;pld load 0 $<;shutdown"

build/formal/top.il: ${SRCS}
	python top.py formal

clean:
	rm -rf build

build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci: mig.tcl mig_a.prj
	mkdir -p build/vivado
	vivado -mode batch -source mig.tcl -nolog -nojournal

mig: build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci

.PHONY: all formal sim arty prog clean mig
.PRECIOUS: build/%.elf
