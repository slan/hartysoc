from nmigen.hdl.rec import *


bus_layout = [
    ("addr", 32, DIR_FANOUT),
    ("rdata", 32, DIR_FANIN),
    ("wmask", 4, DIR_FANOUT),
    ("wdata", 32, DIR_FANOUT),
]
