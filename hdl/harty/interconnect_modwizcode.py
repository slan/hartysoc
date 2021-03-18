from nmigen import *
from ..riscv.bus import bus_layout

# Stupid function to simplify connecting the busses
def connect_bus(upstream, downstream):
    stmts = []
    stmts.append(upstream.rdata.eq(downstream.rdata))
    stmts.append(downstream.wdata.eq(upstream.wdata))
    stmts.append(upstream.rdy.eq(downstream.rdy))
    stmts.append(downstream.rmask.eq(upstream.rmask))
    stmts.append(downstream.wmask.eq(upstream.wmask))
    stmts.append(downstream.addr.eq(upstream.addr))
    return stmts

class InterConnectModwizcode(Elaboratable):
    def __init__(self, *, domain, bus0, bus1):
        self._domain = domain
        # Connection for the upstream instruction bus
        self.instruction_bus = Record(bus_layout)
        # Connection for the upstream data bus
        self.data_bus = Record(bus_layout)
        # "Devices"
        # This sort of makes sense because you might want to load from rom if you're executing from it
        # likewise with memory and they might be on an internal and external bus respectively
        self._devices = Array([bus0, bus1])
    def elaborate(self, platform):
        # If instruction_bus and data_bus request the same target we need to delay one of the transactions
        # since we only have one path to downstream devices
        # To do this we keep track of the request, performing the instruction_bus first then the data_bus
        # This helps the module since it can decode and complete the instruction
        m = Module()
        # Use the top bit to select the device's bus
        data_bus_id = self.data_bus.addr[-1]
        instruction_bus_id = self.instruction_bus.addr[-1]

        data_device = self._devices[data_bus_id]
        instruction_device = self._devices[instruction_bus_id]
        # If this is the same device the transaction must be split between two cycles because
        # the bus isn't clocked
        # Devices are not identical (access is not stalled) if both rmask and wmask for device are unset
        # (no access is being performed. i.e. op not memory)
        same_device = (data_bus_id == instruction_bus_id) & (self.data_bus.wmask.any() | self.data_bus.rmask.any())

        # Cache the ibus request so that we can do a dbus request if there's a conflict (only happens
        # when you write to current pc's addr on the same device which is actually pretty unlikely
        # but if we don't handle this you can stall the hart by doing that which is bad)
        cached_ibus = Record(bus_layout)

        # cache_present indicates that a value is currently present in the cache, without any bearing on
        # current validity, it's just a register set when the cache is updated
        # it's possible that this could just be derived from the rmask being non-zero
        cache_present = Signal()

        # cache_valid is a combinatoral signal indicating that a value is present and the cached state
        # matches the current ibus request attributes
        cache_valid = cache_present & (cached_ibus.addr == self.instruction_bus.addr) & \
                  (cached_ibus.rmask == self.instruction_bus.rmask)		

        # If the cache is invalid the instruction bus is always connected directly. The only thing that is different
        # when uncached is the stall behavior for the data_bus
        with m.If(~cache_valid):
            # Cache isn't valid so connect the instruction bus directly
            m.d.comb += connect_bus(self.instruction_bus, instruction_device)
            # If the cache isn't currently valid then once the instruction device is ready we want
            # to cache that value in case the data_bus access requires us to stall

            # This is only safe to do here because we know that the uncached_state always means the
            # instruction_device is being driven by the instruction_bus's address and rmask
            with m.If(instruction_device.rdy):
                m.d[self._domain] += [
                    # We keep track of address to match until ibus changes it
                    cached_ibus.addr.eq(self.instruction_bus.addr),
                    # The data from the device because duh
                    cached_ibus.rdata.eq(instruction_device.rdata),
                    # The rmask from upstream to invalidate if it changes
                    cached_ibus.rmask.eq(self.instruction_bus.rmask),
                    # Mark as present
                    cache_present.eq(1)
                ]
        with m.Else():
            # If the cache is valid then we connect the instruction bus to the cache
            # this is done here in order to make it more obivous that it's either connected to
            # the device or the cache always, only depending on cache validity

            # In essence all the comb signals should always be muxes (which is a lot clearer in the generated HDL
            # since it leaves all the comb signals as wires and not reg's) but using a mux would mean we can't group
            # the cache update logic in above to show that driving the instruction device is inately coupled with
            # updating the cache
            m.d.comb += [
                # This is implied by being in the Else() of If(~cache_valid)
                self.instruction_bus.rdy.eq(1),
                # Actually report the data
                self.instruction_bus.rdata.eq(cached_ibus.rdata)
                # The rest are all upstream->device and so are unused (is there a better way to enforce this?)
            ]

        # The below logic is to handle the data bus behavior
        # We can only connect the data bus safely if it's to a seperate device or we know that the ibus is being
        # driven by the cache so it's not using that device's bus
        with m.If(~same_device | cache_valid):
            # Devices are independent (ibus is different device or cache which is essentially an internal device)
            m.d.comb += connect_bus(self.data_bus, data_device)
            # The original code would have cleared the cache validity once the data value is ready
            # this coupled with the specific design of the hart, handled exiting the cached value state
            # we don't need to do this ourselves (at least with this hart design) since our code automatically
            # recognizes the different addr after pc changes as an invalid state and switches back to the
            # direct connection
        with m.Else():
            # In this case we have to stall because the cache isn't ready yet and the device access would
            # interfere with the other access. To stall until something changes we manually override the
            # rdy signal for the data bus to tell the hart to stall at the writeback phase
            m.d.comb += self.data_bus.rdy.eq(0)
        # Initially the above logic was modeled in a state machine, but that makes the muxing between "connected" and
        # "not connected" more unclear because they're seperated by states, ideally we could use Mux directly which
        # would let all our combinatoral signals be wires, however this gets in the way of expressing the way that
        # other connections are dependent
        return m
