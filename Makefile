formal: toplevel_bmc/PASS toplevel_cover/PASS

prog: build/top.bit
	djtgcfg prog -d Arty -i 0 -f $<

build/top.bit: toplevel.py
	python3 $<

toplevel_bmc/PASS toplevel_cover/PASS: toplevel.il toplevel.sby
	sby -f toplevel.sby

toplevel.il: toplevel.py
	python3 $< generate -t il >$@
