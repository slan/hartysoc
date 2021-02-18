SRCS := $(wildcard riscv/*.py) $(wildcard kitchensink/*.py)
FORMAL_SRCS := checks.cfg wrapper.sv
RISCV_FORMAL_CORE := ~/src/riscv-formal/cores/HelloArty
PYTHONPATH := ~/src/HelloArty

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
FORMAL_TGTS := $(foreach src,${FORMAL_SRCS},${RISCV_FORMAL_CORE}/$(src))
TESTS := $(foreach test,${OTHER_TESTS},$(test)_ch0) $(foreach test,${INSNS_TESTS},insn_$(test)_ch0)

_dummy := $(shell mkdir -p build)

CC=~/riscv64-unknown-elf-gcc-10.1.0-2020.08.2-x86_64-linux-ubuntu14/bin/riscv64-unknown-elf-gcc
TARGET_ARCH=-march=rv32i -mabi=ilp32
CFLAGS=-save-temps=obj
LDFLAGS=-nostdlib
OUTPUT_OPTION=-o $@

all: build/main.elf

build/%.o: %.c
	$(COMPILE.c) $(OUTPUT_OPTION) $<
	riscv64-unknown-elf-objdump -d -t -r $@

build/main.elf: build/main.o
	$(LINK.o) $(OUTPUT_OPTION) $<
	riscv64-unknown-elf-objdump -d -t -r $@

simwave: sim
	gtkwave build/sim/top.vcd gtk-sim.gtkw&

formal: $(foreach test, ${TESTS}, ${RISCV_FORMAL_CORE}/checks/$(test)/PASS)
	@rm -rf build/formal&&mkdir -p build/formal
	@cd build/formal && \
		files_pass="$(dir $(wildcard ${RISCV_FORMAL_CORE}/checks/*/PASS))" && \
		files_fail="$(dir $(wildcard ${RISCV_FORMAL_CORE}/checks/*/FAIL))" && \
		files_error="$(dir $(wildcard ${RISCV_FORMAL_CORE}/checks/*/ERROR))" && \
		for i in $$files_error; do \
			echo $$i; \
		done>>asserts.txt && \
		for i in $$files_fail; do \
			[ $$sep ] && echo && echo --------------------------------------------------------------------------------; \
			cp $$i/engine_0/trace.vcd $$(basename $$i).vcd; \
			cp $$i/engine_0/logfile.txt $$(basename $$i).txt; \
			python ${PYTHONPATH}/disasm.py $$i/engine_0/trace.vcd $$(basename $$i); \
			echo; \
			grep "Assert failed" $$i/logfile.txt; \
			sep=1; \
		done>>asserts.txt && \
		[ -s asserts.txt ] && \
			echo && echo -------------------------------------------------------------------------------- && \
			cat asserts.txt && \
			echo && \
			echo -n " PASS: " && echo "$$files_pass" | wc -w && \
			echo -n " FAIL: " && echo "$$files_fail" | wc -w && \
			echo -n "ERROR: " && echo "$$files_error" | wc -w \
		|| echo "All tests passed!"

${RISCV_FORMAL_CORE}/checks/%/PASS: ${SRCS} ${FORMAL_TGTS}
	rm -rf $(dir $@)
	cd ${RISCV_FORMAL_CORE}&&PYTHONPATH=${PYTHONPATH} make -C checks $*

build/__init__.py: build/bootcode.elf
	@riscv64-unknown-elf-objcopy -O binary $< build/$*.tmp
	@echo "bootcode = [" > $@
	@hexdump build/$*.tmp -v -e "\"\t0x\" \"%08x,\n\"" >>$@
	@echo "]" >> $@

sim: build/__init__.py
	python3 top.py sim

arty: build/arty/top.bit

build/arty/top.bit: build/__init__.py #build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci
	python3 top.py arty

prog: build/arty/top.bit
	djtgcfg prog -d Arty -i 0 -f $<

${FORMAL_TGTS}: ${FORMAL_SRCS} | ${RISCV_FORMAL_CORE}/checks

${RISCV_FORMAL_CORE}/checks: ${SRCS}
	mkdir -p ${RISCV_FORMAL_CORE}
	cp ${FORMAL_SRCS} ${RISCV_FORMAL_CORE}
	cd ${RISCV_FORMAL_CORE}&&python ../../checks/genchecks.py

build/formal/top.il: ${SRCS}
	python3 top.py formal

clean:
	rm -rf build ${RISCV_FORMAL_CORE}

build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci: mig.tcl mig_a.prj
	mkdir -p build/vivado
	vivado -mode batch -source mig.tcl -nolog -nojournal

mig: build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci

.PHONY: all formal sim arty prog clean mig
.PRECIOUS: build/%.elf
