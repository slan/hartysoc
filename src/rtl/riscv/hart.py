from nmigen import *
from nmigen.hdl.rec import *

from .enums import *
from .alu import *
from .decoder import *
from .registers import *

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
    def __init__(self, domain, with_rvfi=False):
        self._domain = domain
        self._with_rvfi = with_rvfi
        if with_rvfi:
            self.rvfi = Record(rvfi_layout)
        self.registers = Registers(domain)
        self.decoder = Decoder()
        self.trap = Signal()
        self.mcause = Signal(32, decoder=lambda x: f"{TrapCause(x).name}/{x}")
        self.halt = Signal()
        
        self.imem_stall = Signal()
        self.imem_addr = Signal(32)
        self.imem_data = Signal(32)

        self.dmem_stall = Signal()
        self.dmem_addr = Signal(32)
        self.dmem_rmask = Signal(4)
        self.dmem_rdata = Signal(32)
        self.dmem_wmask = Signal(4)
        self.dmem_wdata = Signal(32)

    def elaborate(self, platform):
        self.mcycle = Signal(64)
        self.minstret = Signal(64)

        m = Module()
        comb = m.d.comb
        sync = m.d[self._domain]

        m.submodules.registers = registers = self.registers
        m.submodules.alu = alu = ALU()
        m.submodules.decoder = decoder = self.decoder

        pc = Signal(32, reset=0x20000000)

        def trap(mcause, comb=comb, sync=sync):
            comb += [
                self.trap.eq(1),
                self.mcause.eq(mcause),
            ]
            sync += [
                self.halt.eq(1),
            ]

        with m.If(~self.halt):
            sync += [
                self.mcycle.eq(self.mcycle + 1),
            ]

            with m.If(~self.imem_stall):

                ### ID
                comb += [
                    self.imem_addr.eq(pc),
                    decoder.insn.eq(self.imem_data),
                    decoder.pc.eq(pc),
                ]

                ### EX
                comb += [
                    registers.rs1_addr.eq(decoder.rs1_addr),
                    registers.rs2_addr.eq(decoder.rs2_addr),
                    alu.func.eq(decoder.alu_func),
                    alu.func_ex.eq(decoder.alu_func_ex),
                    alu.op1.eq(
                        Mux(
                            decoder.alu_src1_type == AluSrc1.PC,
                            pc,
                            registers.rs1_rdata,
                        )
                    ),
                    alu.op2.eq(
                        Mux(
                            decoder.alu_src2_type == AluSrc2.IMM,
                            decoder.imm,
                            registers.rs2_rdata,
                        )
                    ),
                ]

                ### MEM
                read_access = decoder.mem_rtype != MemAccessType.NONE
                write_access = decoder.mem_wtype != MemAccessType.NONE
                mem_access = read_access | write_access

                with m.If(mem_access & ~self.dmem_stall):
                    comb += self.dmem_addr.eq(Cat(C(0, 2), alu.out[2:32]))

                    # LOAD
                    with m.If(read_access):
                        rdata = Signal(32)
                        with m.Switch(decoder.mem_rtype):
                            with m.Case(MemAccessType.B, MemAccessType.BU):
                                byte = self.dmem_rdata.word_select(alu.out[0:2], 8)
                                comb += [
                                    self.dmem_rmask.eq(1 << alu.out[0:2]),
                                    rdata.eq(
                                        Mux(
                                            decoder.mem_rtype == MemAccessType.BU,
                                            byte,
                                            byte.as_signed(),
                                        )
                                    ),
                                ]
                            with m.Case(MemAccessType.H, MemAccessType.HU):
                                with m.If(alu.out[0]):
                                    trap(TrapCause.DADDR_L)
                                with m.Else():
                                    half = self.dmem_rdata.word_select(alu.out[1], 16)
                                    comb += [
                                        self.dmem_rmask.eq(Mux(alu.out[1], 0b1100, 0b0011)),
                                        rdata.eq(
                                            Mux(
                                                decoder.mem_rtype == MemAccessType.HU,
                                                half,
                                                half.as_signed(),
                                            )
                                        ),
                                    ]
                            with m.Default():
                                with m.If(alu.out[0:2].any()):
                                    trap(TrapCause.DADDR_L)
                                with m.Else():
                                    comb += [
                                        self.dmem_rmask.eq(0b1111),
                                        rdata.eq(self.dmem_rdata),
                                    ]

                    # STORE
                    with m.If(write_access):
                        with m.Switch(decoder.mem_wtype):
                            with m.Case(MemAccessType.B):
                                comb += [
                                    self.dmem_wmask.eq(0b1 << alu.out[0:2]),
                                    self.dmem_wdata.word_select(alu.out[0:2], 8).eq(
                                        registers.rs2_rdata
                                    ),
                                ]
                            with m.Case(MemAccessType.H):
                                with m.If(alu.out[0]):
                                    trap(TrapCause.DADDR_S)
                                with m.Else():
                                    comb += [
                                        self.dmem_wmask.eq(
                                            Mux(alu.out[1], 0b1100, 0b0011)
                                        ),
                                        self.dmem_wdata.word_select(alu.out[1], 16).eq(
                                            registers.rs2_rdata
                                        ),
                                    ]
                            with m.Default():
                                with m.If(alu.out[0:2].any()):
                                    trap(TrapCause.DADDR_S)
                                with m.Else():
                                    comb += [
                                        self.dmem_wmask.eq(0b1111),
                                        self.dmem_wdata.eq(registers.rs2_rdata),
                                    ]

                ### WB
                with m.If(~mem_access | ~self.dmem_stall):
                    comb += [
                        registers.rd_addr.eq(decoder.rd_addr),
                    ]
                    with m.Switch(decoder.reg_src_type):
                        with m.Case(RegSrc.ALU):
                            comb += registers.rd_data.eq(alu.out)
                        with m.Case(RegSrc.PC_INCR):
                            comb += registers.rd_data.eq(pc + 4)
                        with m.Case(RegSrc.MEM):
                            comb += registers.rd_data.eq(rdata)
                        with m.Case(RegSrc.M_CYCLE):
                            comb += registers.rd_data.eq(self.mcycle)
                        with m.Case(RegSrc.M_INSTRET):
                            comb += registers.rd_data.eq(self.minstret)
                    with m.If(decoder.rd_addr == 0):
                        comb += [
                            registers.rd_data.eq(0),
                        ]

                    bc_ne = registers.rs1_rdata != registers.rs2_rdata
                    bc_lt = (
                        registers.rs1_rdata.as_signed()
                        < registers.rs2_rdata.as_signed()
                    )
                    bc_ltu = (
                        registers.rs1_rdata.as_unsigned()
                        < registers.rs2_rdata.as_unsigned()
                    )
                    branch_taken = (
                        (decoder.branch_cond == BranchCond.ALWAYS)
                        | ((decoder.branch_cond == BranchCond.NE) & bc_ne)
                        | ((decoder.branch_cond == BranchCond.EQ) & ~bc_ne)
                        | ((decoder.branch_cond == BranchCond.LT) & bc_lt)
                        | ((decoder.branch_cond == BranchCond.GE) & ~bc_lt)
                        | ((decoder.branch_cond == BranchCond.LTU) & bc_ltu)
                        | ((decoder.branch_cond == BranchCond.GEU) & ~bc_ltu)
                    )

                    with m.If(decoder.trap):
                        trap(decoder.mcause)
                    with m.If(branch_taken & alu.out[0:2].any()):
                        trap(TrapCause.IADDR)

                    pc_next = Mux(
                        branch_taken,
                        alu.out,
                        pc + 4,
                    )
                    sync += [
                        pc.eq(pc_next),
                        self.minstret.eq(self.minstret + 1),
                    ]

        if self._with_rvfi:
            comb += [
                self.rvfi.valid.eq(
                    ~self.trap
                    & ~self.halt
                    & ~self.imem_stall
                    & ~(mem_access & self.dmem_stall)
                ),
                self.rvfi.pc_wdata.eq(pc_next),
                self.rvfi.pc_rdata.eq(self.imem_addr),
                self.rvfi.rd_wdata.eq(registers.rd_data),
                self.rvfi.order.eq(self.minstret),
                self.rvfi.insn.eq(self.imem_data),
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
                self.rvfi.rd_wdata.eq(registers.rd_data),
                self.rvfi.mem_addr.eq(self.dmem_addr),
                self.rvfi.mem_rmask.eq(self.dmem_rmask),
                self.rvfi.mem_wmask.eq(self.dmem_wmask),
                self.rvfi.mem_rdata.eq(self.dmem_rdata),
                self.rvfi.mem_wdata.eq(self.dmem_wdata),
            ]

        return m
