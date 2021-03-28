from nmigen import *
from nmigen.hdl.rec import *

from .enums import *
from .alu import *
from .decoder import *
from .registers import *
from .bus import *

rvfi_layout = [
    ("valid", 1, DIR_FANOUT),
    ("order", 64, DIR_FANOUT),
    ("insn", 32, DIR_FANOUT),
    ("trap", 1, DIR_FANOUT),
    ("halt", 1, DIR_FANOUT),
    ("intr", 1, DIR_FANOUT),
    ("mode", 2, DIR_FANOUT),
    ("ixl", 2, DIR_FANOUT),
    ("rs1_addr", 5, DIR_FANOUT),
    ("rs1_rdata", 32, DIR_FANOUT),
    ("rs2_addr", 5, DIR_FANOUT),
    ("rs2_rdata", 32, DIR_FANOUT),
    ("rd_addr", 5, DIR_FANOUT),
    ("rd_wdata", 32, DIR_FANOUT),
    ("pc_rdata", 32, DIR_FANOUT),
    ("pc_wdata", 32, DIR_FANOUT),
    ("mem_addr", 32, DIR_FANOUT),
    ("mem_rmask", 4, DIR_FANOUT),
    ("mem_rdata", 32, DIR_FANOUT),
    ("mem_wmask", 4, DIR_FANOUT),
    ("mem_wdata", 32, DIR_FANOUT),
]


class Hart(Elaboratable):
    def __init__(self, domain, with_rvfi=False, reset_vector=0):
        self._domain = domain
        self._with_rvfi = with_rvfi
        self._reset_vector = reset_vector

        self.trap = Signal()
        self.mcause = Signal(32, decoder=lambda x: f"{TrapCause(x).name}/{x}")
        self.halt = Signal()
        self.ibus = Record(bus_layout)
        self.dbus = Record(bus_layout)
        self.mcycle = Signal(64)
        self.minstret = Signal(64)

        self.registers = Registers(domain)
        self.decoder = Decoder()

        if self._with_rvfi:
            self.rvfi = Record(rvfi_layout)

    def elaborate(self, platform):

        m = Module()
        comb = m.d.comb
        sync = m.d[self._domain]

        m.submodules.registers = registers = self.registers
        m.submodules.alu = alu = ALU()
        m.submodules.decoder = decoder = self.decoder

        pc = Signal(32, reset=self._reset_vector)
        pc_incr = Signal.like(pc)

        with m.If(decoder.trap):
            comb += self.trap.eq(1)
            sync += self.halt.eq(1)

        with m.If(~self.halt):
            sync += [
                self.mcycle.eq(self.mcycle + 1),
            ]

            ### IF

            comb += [
                self.ibus.rmask.eq(0b1111),
                self.ibus.addr.eq(pc),
            ]

            with m.If(self.ibus.ack):

               ### ID

                comb += [
                    decoder.insn.eq(self.ibus.rdata),
                    decoder.pc.eq(pc),
                    pc_incr.eq(pc + 4),
                ]

                ### EX

                comb += [
                    registers.rs1_addr.eq(decoder.rs1_addr),
                    registers.rs2_addr.eq(decoder.rs2_addr),
                    alu.func.eq(decoder.alu_func),
                    alu.func_ex.eq(decoder.alu_func_ex),
                    alu.op1.eq(
                        Mux(
                            decoder.alu_src1 == AluSrc1.PC,
                            pc,
                            registers.rs1_rdata,
                        )
                    ),
                    alu.op2.eq(
                        Mux(
                            decoder.alu_src2 == AluSrc2.IMM,
                            decoder.imm,
                            registers.rs2_rdata,
                        )
                    ),
                ]

                ### MEM

                with m.If(decoder.mem_func != MemFunc.NONE):
                    comb += self.dbus.addr[2:].eq(alu.out[2:])
                    with m.Switch(decoder.mem_func):

                        # LOAD
                        with m.Case(MemFunc.LB, MemFunc.LBU):
                            comb += self.dbus.rmask.eq(1 << alu.out[0:2])
                        with m.Case(MemFunc.LH, MemFunc.LHU):
                            comb += self.dbus.rmask.eq(
                                Mux(alu.out[1], 0b1100, 0b0011)
                            )
                        with m.Case(MemFunc.LW):
                            comb += self.dbus.rmask.eq(0b1111)

                        # STORE
                        with m.Case(MemFunc.SB):
                            comb += [
                                self.dbus.wmask.eq(0b1 << alu.out[0:2]),
                                self.dbus.wdata.word_select(alu.out[0:2], 8).eq(
                                    registers.rs2_rdata
                                ),
                            ]
                        with m.Case(MemFunc.SH):
                            comb += [
                                self.dbus.wmask.eq(Mux(alu.out[1], 0b1100, 0b0011)),
                                self.dbus.wdata.word_select(alu.out[1], 16).eq(
                                    registers.rs2_rdata
                                ),
                            ]
                        with m.Case(MemFunc.SW):
                            comb += [
                                self.dbus.wmask.eq(0b1111),
                                self.dbus.wdata.eq(registers.rs2_rdata),
                            ]

                ### WB
                # Gate: no memory access or dbus ready

                with m.If((decoder.mem_func == MemFunc.NONE) | self.dbus.ack):

                    with m.If(decoder.rd_addr == 0):
                        comb += registers.rd_wdata.eq(0)

                    with m.Else():
                        comb += registers.rd_addr.eq(decoder.rd_addr)

                        with m.Switch(decoder.mem_func):
                            with m.Case(MemFunc.LB, MemFunc.LBU):
                                comb += registers.rd_wdata.eq(
                                    Mux(
                                        decoder.mem_func == MemFunc.LBU,
                                        self.dbus.rdata.word_select(alu.out[0:2], 8),
                                        self.dbus.rdata.word_select(
                                            alu.out[0:2], 8
                                        ).as_signed(),
                                    )
                                )
                            with m.Case(MemFunc.LH, MemFunc.LHU):
                                comb += registers.rd_wdata.eq(
                                    Mux(
                                        decoder.mem_func == MemFunc.LHU,
                                        self.dbus.rdata.word_select(alu.out[1], 16),
                                        self.dbus.rdata.word_select(
                                            alu.out[1], 16
                                        ).as_signed(),
                                    )
                                )
                            with m.Case(MemFunc.LW):
                                comb += registers.rd_wdata.eq(self.dbus.rdata)

                            with m.Default():
                                with m.Switch(decoder.reg_src):
                                    with m.Case(RegSrc.ALU):
                                        comb += registers.rd_wdata.eq(alu.out)
                                    with m.Case(RegSrc.PC_INCR):
                                        comb += registers.rd_wdata.eq(pc_incr)
                                    with m.Case(RegSrc.M_CYCLE):
                                        comb += registers.rd_wdata.eq(self.mcycle)
                                    with m.Case(RegSrc.M_INSTRET):
                                        comb += registers.rd_wdata.eq(self.minstret)

                    pc_wdata = Signal.like(pc)
                    branch_target = Signal.like(pc)
                    branch_taken = Signal()
                    with m.Switch(decoder.branch_cond):
                        with m.Case(BranchCond.ALWAYS):
                            comb += [
                                branch_taken.eq(1),
                                branch_target.eq(alu.out),
                            ]
                        with m.Case(BranchCond.NEVER):
                            pass
                        with m.Case(BranchCond.EQ):
                            comb += [
                                branch_taken.eq(alu.eq),
                                branch_target.eq(decoder.branch_target),
                            ]
                        with m.Case(BranchCond.NE):
                            comb += [
                                branch_taken.eq(~alu.eq),
                                branch_target.eq(decoder.branch_target),
                            ]
                        with m.Case(BranchCond.LT, BranchCond.LTU):
                            comb += [
                                branch_taken.eq(alu.out.any()),
                                branch_target.eq(decoder.branch_target),
                            ]
                        with m.Case(BranchCond.GE, BranchCond.GEU):
                            comb += [
                                branch_taken.eq(~alu.out.any()),
                                branch_target.eq(decoder.branch_target),
                            ]

                    comb += pc_wdata.eq(Mux(branch_taken, branch_target, pc_incr))

                    sync += [
                        pc.eq(pc_wdata),
                        self.minstret.eq(self.minstret + 1),
                    ]
                    if self._with_rvfi:
                        comb += self.rvfi.valid.eq(~self.trap)

        if self._with_rvfi:
            comb += [
                self.rvfi.pc_wdata.eq(pc_wdata),
                self.rvfi.pc_rdata.eq(self.ibus.addr),
                self.rvfi.rd_wdata.eq(registers.rd_wdata),
                self.rvfi.order.eq(self.minstret),
                self.rvfi.insn.eq(self.ibus.rdata),
                self.rvfi.trap.eq(self.trap),
                self.rvfi.halt.eq(self.halt),
                self.rvfi.intr.eq(Const(0)),
                self.rvfi.mode.eq(Const(3)),
                self.rvfi.ixl.eq(Const(1)),
                self.rvfi.rs1_addr.eq(registers.rs1_addr),
                self.rvfi.rs2_addr.eq(registers.rs2_addr),
                self.rvfi.rs1_rdata.eq(registers.rs1_rdata),
                self.rvfi.rs2_rdata.eq(registers.rs2_rdata),
                self.rvfi.rd_addr.eq(registers.rd_addr),
                self.rvfi.rd_wdata.eq(registers.rd_wdata),
                self.rvfi.mem_addr.eq(self.dbus.addr),
                self.rvfi.mem_rmask.eq(self.dbus.rmask),
                self.rvfi.mem_wmask.eq(self.dbus.wmask),
                self.rvfi.mem_rdata.eq(self.dbus.rdata),
                self.rvfi.mem_wdata.eq(self.dbus.wdata),
            ]

        return m
