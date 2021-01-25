SRCS := top.py $(wildcard kitchensink/*.py)

all: sim

sim: build/sim/top.vcd

build/sim/top.vcd: ${SRCS}
	python3 top.py sim

arty: build/arty/top.bit

build/arty/top.bit: ${SRCS}
	python3 top.py arty

prog: build/arty/top.bit
	djtgcfg prog -d Arty -i 0 -f $<

formal: build/sim/top.il build/sim/top.sby
	sby -f build/sim/top.sby

clean:
	rm -rf build __pycache__

.PHONY: all sim arty prog formal clean
