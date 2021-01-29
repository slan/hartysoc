SRCS := top.py $(wildcard kitchensink/*.py)

all: sim

sim: build/sim/top.vcd

build/sim/top.vcd: ${SRCS}
	python3 top.py sim

arty: build/arty/top.bit

build/arty/top.bit: ${SRCS} build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci
	python3 top.py arty

prog: build/arty/top.bit
	djtgcfg prog -d Arty -i 0 -f $<

formal: build/sim/top.il build/sim/top.sby
	sby -f build/sim/top.sby

clean:
	rm -rf build __pycache__ kitchensink/__pycache__

build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci: mig.tcl mig_a.prj
	mkdir -p build/vivado
	vivado -mode batch -source mig.tcl -nolog -nojournal

mig: build/vivado/mig/mig.srcs/sources_1/ip/mig_7series_0/mig_7series_0.xci

.PHONY: all sim arty prog formal clean mig
