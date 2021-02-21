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
    def __init__(self, domain="sync"):
        self._domain = domain
        self.registers = Registers(domain)
        self.trap = Signal()
        self.halt = Signal()
        self.imem_addr = Signal(32)
        self.imem_data = Signal(32)
        self.dmem_addr = Signal(32)
        self.dmem_rdata = Signal(32)
        self.dmem_wmask = Signal(4)
        self.dmem_wdata = Signal(32)
        self.rvfi = Record(rvfi_layout)

    def elaborate(self, platform):
        self.mcycle = Signal(64)
        self.minstret = Signal(64)
        self.mcause = Signal(32, decoder=lambda x: f"{TrapCause(x).name}/{x}")

        m = Module()
        comb = m.d.comb
        sync = m.d[self._domain]

        m.submodules.registers = registers = self.registers
        m.submodules.alu = alu = ALU()
        m.submodules.decoder = decoder = Decoder()


        pc = Signal(32)

        with m.FSM(domain=self._domain):
            with m.State("RUN"):
                ### ID
                comb += [
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
                with m.If(decoder.mem_wmask.any() | decoder.reg_src_type == RegSrc.MEM):
                    comb += [
                        self.dmem_addr.eq(alu.out),
                    ]
                with m.If(decoder.mem_wmask.any()):
                    comb += [
                        self.dmem_wmask.eq(decoder.mem_wmask),
                        self.dmem_wdata.eq(
                            registers.rs2_rdata
                            & Cat(
                                Repl(decoder.mem_wmask[0], 8),
                                Repl(decoder.mem_wmask[1], 8),
                                Repl(decoder.mem_wmask[2], 8),
                                Repl(decoder.mem_wmask[3], 8),
                            )
                        ),
                        self.dmem_addr.eq(alu.out),
                    ]

                ### WB
                rmask = Signal(4)
                comb += [
                    registers.rd_addr.eq(decoder.rd_addr),
                ]
                with m.Switch(decoder.reg_src_type):
                    with m.Case(RegSrc.ALU):
                        comb += [
                            registers.rd_data.eq(alu.out),
                        ]
                    with m.Case(RegSrc.PC_INCR):
                        comb += [
                            registers.rd_data.eq(pc + 4),
                        ]
                    with m.Case(RegSrc.MEM):
                        with m.Switch(decoder.load_func):
                            with m.Case(LoadFunc.LB, LoadFunc.LBU):
                                byte = self.dmem_rdata.word_select(
                                    self.dmem_addr[0:2], 8
                                )
                                comb += [
                                    rmask.eq(1 << self.dmem_addr[0:2]),
                                    registers.rd_data.eq(
                                        Mux(
                                            decoder.load_func[2], byte, byte.as_signed()
                                        )
                                    ),
                                ]
                            with m.Case(LoadFunc.LH, LoadFunc.LHU):
                                half = self.dmem_rdata.word_select(
                                    self.dmem_addr[0], 16
                                )
                                comb += [
                                    rmask.eq(0b11 << (self.dmem_addr[0] << 1)),
                                    registers.rd_data.eq(
                                        Mux(
                                            decoder.load_func[2], half, half.as_signed()
                                        )
                                    ),
                                ]
                            with m.Case(LoadFunc.LW):
                                comb += [
                                    rmask.eq(0b1111),
                                    registers.rd_data.eq(self.dmem_rdata),
                                ]
                with m.If(decoder.rd_addr == 0):
                    comb += [
                        registers.rd_data.eq(0),
                    ]

                bc_ne = (registers.rs1_rdata ^ registers.rs2_rdata).any()
                bc_lt = (
                    registers.rs1_rdata.as_signed() < registers.rs2_rdata.as_signed()
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

                comb += [
                    self.imem_addr.eq(
                        Mux(
                            branch_taken,
                            alu.out,
                            pc + 4,
                        )
                    ),
                ]

                with m.If(decoder.trap):
                    comb += [self.trap.eq(1), self.mcause.eq(decoder.mcause)]
                with m.Elif(self.imem_addr[0:2].any()):
                    comb += [self.trap.eq(1), self.mcause.eq(TrapCause.IADDR)]
                with m.Elif(self.dmem_addr[0:2].any()):
                    comb += [
                        self.trap.eq(1),
                        self.mcause.eq(
                            Mux(
                                decoder.mem_wmask.any(),
                                TrapCause.DADDR_S,
                                TrapCause.DADDR_L,
                            )
                        ),
                    ]

                with m.If(self.trap):
                    with m.If(self.mcause==TrapCause.M_ECALL):
                        pass
                    with m.Else():
                        comb += [
                            self.halt.eq(1)
                        ]
                        m.next = "HALT"
                        
                sync += [
                    self.mcycle.eq(self.mcycle + 1),
                    self.minstret.eq(self.minstret + 1),
                    pc.eq(self.imem_addr),
                ]

            with m.State("HALT"):
                comb += [
                    self.trap.eq(1),
                    self.halt.eq(1),
                ]

        comb += [
            self.rvfi.valid.eq(~self.halt),
            self.rvfi.pc_wdata.eq(self.imem_addr),
            self.rvfi.pc_rdata.eq(pc),
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
            self.rvfi.mem_rmask.eq(rmask),
            self.rvfi.mem_wmask.eq(decoder.mem_wmask),
            self.rvfi.mem_rdata.eq(self.dmem_rdata),
            self.rvfi.mem_wdata.eq(self.dmem_wdata),
        ]
        return m