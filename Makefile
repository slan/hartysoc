SRCS := top.py build/__init__.py $(wildcard riscv/*.py) $(wildcard kitchensink/*.py)
RISCV_FORMAL_CORE := /home/slan/src/riscv-formal/cores/HelloArty
PYTHONPATH := /home/slan/src/HelloArty
TESTS := \
	insn_addi_ch0 \
	# reg_ch0 \
	#insn_add_ch0 \

all:

formal: ${RISCV_FORMAL_CORE}/checks.cfg ${RISCV_FORMAL_CORE}/wrapper.sv ${SRCS}
	rm -rf $(foreach test,${TESTS}, ${RISCV_FORMAL_CORE}/checks/$(test))
	cd ${RISCV_FORMAL_CORE}&&PYTHONPATH=${PYTHONPATH} make -C checks ${TESTS}

build/%.elf: %.s
	mkdir -p build
	riscv64-unknown-elf-as $< -march=rv32i -mabi=ilp32 -mno-arch-attr -o $@
	riscv64-unknown-elf-objdump -D $@

build/__init__.py: build/bootcode.elf
	@riscv64-unknown-elf-objcopy --reverse-bytes=2 -O binary $< build/$*.tmp
	@echo "bootcode = [" > $@
	@dd if=build/$*.tmp conv=swab status=none|hexdump -v -e "\"\t0x\" \"%08x,\n\"" >>$@
	@echo "]" >> $@
	
sim: ${SRCS}
	python3 top.py sim

arty: build/arty/top.bit

build/arty/top.bit: ${SRCS} #build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci
	python3 top.py arty

prog: build/arty/top.bit
	djtgcfg prog -d Arty -i 0 -f $<

${RISCV_FORMAL_CORE}/checks.cfg ${RISCV_FORMAL_CORE}/wrapper.sv : checks.cfg wrapper.sv
	mkdir -p ${RISCV_FORMAL_CORE}
	cp $^ ${RISCV_FORMAL_CORE}
	cd ${RISCV_FORMAL_CORE}&&python ../../checks/genchecks.py
	
build/formal/top.il: ${SRCS}
	python3 top.py formal

clean:
	rm -rf build __pycache__ kitchensink/__pycache__ bootcode.py ${RISCV_FORMAL_CORE}

build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci: mig.tcl mig_a.prj
	mkdir -p build/vivado
	vivado -mode batch -source mig.tcl -nolog -nojournal

mig: build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci

.PHONY: all sim arty prog formal clean mig
.PRECIOUS: build/%.elf