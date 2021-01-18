all: sim

vivado: build/top.bit

formal: toplevel.il toplevel.sby
	sby -f toplevel.sby

toplevel.il: toplevel.py
	python3 $< generate -t il >$@

sim: toplevel.py
	python3 $< simulate -c 100 -v toplevel.vcd

prog: build/top.bit
	djtgcfg prog -d Arty -i 0 -f $<

build/top.bit: toplevel.py pll.py mmcm.py
	python3 $<

clean:
	rm -rf toplevel.vcd build