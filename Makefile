all: toplevel_bmc/PASS

prog: build/top.bit
	djtgcfg prog -d Arty -i 0 -f $<

build/top.bit: base.py
	python3 $<

toplevel.il: adder.py
	python3 $< generate -t il >$@

toplevel_bmc/PASS: toplevel.il
	sby -f toplevel.sby