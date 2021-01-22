SRCS := top.py pll.py vga.py

all: sim

sim: sim/top.vcd

sim/top.vcd: ${SRCS}
	python3 top.py sim

bitfile: build/top.bit

build/top.bit: ${SRCS}
	python3 top.py

prog: build/top.bit
	djtgcfg prog -d Arty -i 0 -f $<

formal: sim/top.il sim/top.sby
	sby -f top.sby

clean:
	rm -rf build sim

.PHONY: all sim bitfile prog formal clean

