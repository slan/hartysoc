prog: build/top.bit
	djtgcfg prog -d Arty -i 0 -f $<

build/top.bit: blinky.py
	python3 $<

formal: toplevel_bmc/PASS

toplevel_bmc/PASS: toplevel.il toplevel.sby
	sby -f toplevel.sby

toplevel.il: blinky.py
	python3 $< generate -t il >$@
