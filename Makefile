prog: build/top.bit
	djtgcfg prog -d Arty -i 0 -f $<

build/top.bit: base.py
	python3 $<
