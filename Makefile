SRCS := $(wildcard riscv/*.py) $(wildcard kitchensink/*.py)
FORMAL_SRCS := checks.cfg wrapper.sv
RISCV_FORMAL_CORE := /home/slan/src/riscv-formal/cores/HelloArty
PYTHONPATH := /home/slan/src/HelloArty

INSNS := addi bne add jal lw

FORMAL_TGTS := $(foreach src,${FORMAL_SRCS},${RISCV_FORMAL_CORE}/$(src))
TESTS := $(foreach insn,${INSNS},insn_$(insn)_ch0)

all:
	make clean
	make formal -j$(nproc)

formal: $(foreach test, ${TESTS}, ${RISCV_FORMAL_CORE}/checks/$(test)/PASS)
	@rm -rf build/formal&&mkdir -p build/formal
	@cd build/formal && \
		files_pass="$(dir $(wildcard ${RISCV_FORMAL_CORE}/checks/*/PASS))" && \
		files_fail="$(dir $(wildcard ${RISCV_FORMAL_CORE}/checks/*/FAIL))" && \
		files_error="$(dir $(wildcard ${RISCV_FORMAL_CORE}/checks/*/ERROR))" && \
		for i in $$files_error; do \
			echo $$i; \
		done>>aserts.txt && \
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

build/%.elf: %.s
	mkdir -p build
	riscv64-unknown-elf-as $< -march=rv32i -mabi=ilp32 -mno-arch-attr -o $@
	riscv64-unknown-elf-objdump -D $@

build/__init__.py: build/bootcode.elf
	@riscv64-unknown-elf-objcopy --reverse-bytes=2 -O binary $< build/$*.tmp
	@echo "bootcode = [" > $@
	@dd if=build/$*.tmp conv=swab status=none|hexdump -v -e "\"\t0x\" \"%08x,\n\"" >>$@
	@echo "]" >> $@
	
sim: build/__init__.py
	python3 top.py sim

arty: build/arty/top.bit

build/arty/top.bit: build/__init__.py #build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci
	python3 top.py arty

prog: build/arty/top.bit
	djtgcfg prog -d Arty -i 0 -f $<

${FORMAL_TGTS}: ${FORMAL_SRCS} | ${RISCV_FORMAL_CORE}/checks
	touch ${FORMAL_TGTS}

${RISCV_FORMAL_CORE}/checks:
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
