from nmigen import *
from nmigen.hdl.rec import *

from riscv.enums import *

from .alu import *
from .decoder import Decoder
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
    ("rs2_addr", 5, DIR_FANOUT),
    ("rs1_rdata", 32, DIR_FANOUT),
    ("rs2_rdata", 32, DIR_FANOUT),
    ("rd_addr", 5, DIR_FANOUT),
    ("rd_wdata", 32, DIR_FANOUT),
    ("pc_rdata", 32, DIR_FANOUT),
    ("pc_wdata", 32, DIR_FANOUT),
    ("mem_addr", 32, DIR_FANOUT),
    ("mem_rmask", 4, DIR_FANOUT),
    ("mem_wmask", 4, DIR_FANOUT),
    ("mem_rdata", 32, DIR_FANOUT),
    ("mem_wdata", 32, DIR_FANOUT),
]


class Hart(Elaboratable):
    def __init__(self, domain="sync"):
        self._domain = domain
        self.registers = Registers(domain)
        self.trap = Signal()
        self.imem_addr = Signal(32)
        self.imem_data = Signal(32)
        self.dmem_addr = Signal(32)
        self.dmem_rmask = Signal(4)
        self.dmem_rdata = Signal(32)
        self.dmem_wmask = Signal(4)
        self.dmem_wdata = Signal(32)
        self.rvfi = Record(rvfi_layout)

    def elaborate(self, platform):
        self.mcycle = Signal(64)
        self.minstret = Signal(64)
        self.mcause = Signal(32)

        m = Module()
        comb = m.d.comb
        sync = m.d[self._domain]

        m.submodules.registers = registers = self.registers
        m.submodules.alu = alu = ALU()
        m.submodules.decoder = decoder = Decoder()

        # Control
        pc = Signal(32)
        pc_plus_4 = Signal.like(pc)
        insn = Signal(32)
        imm = Signal(32)
        alu_src2_type = Signal(AluSrc2)
        reg_src_type = Signal(RegSrc)
        rd_addr = Signal(5)
        alu_out = Signal(32)
        branch_cond = Signal(BranchCond)
        branch_target = Signal.like(pc)
        mem_rmask = Signal(4)
        mem_wmask = Signal(4)

        sync += self.mcycle.eq(self.mcycle + 1)

        with m.FSM(domain=self._domain) as fsm:
            with m.State("RST"):
                m.next = "IF"
                m.d.comb += [
                    self.imem_addr.eq(pc),
                ]

            with m.State("IF"):
                m.next = "ID"
                sync += [
                    insn.eq(self.imem_data),
                    pc_plus_4.eq(pc + 4),
                ]
            with m.State("ID"):
                with m.If(decoder.mcause.any()):
                    comb += [self.trap.eq(1)]
                    m.next = "HALT"
                with m.Else():
                    m.next = "EX"
                comb += [
                    decoder.insn.eq(insn),
                    decoder.pc.eq(pc),
                ]
                sync += [
                    self.mcause.eq(decoder.mcause),
                    registers.rs1_addr.eq(decoder.rs1_addr),
                    registers.rs2_addr.eq(decoder.rs2_addr),
                    rd_addr.eq(decoder.rd_addr),
                    imm.eq(decoder.imm),
                    mem_rmask.eq(decoder.mem_rmask),
                    mem_wmask.eq(decoder.mem_wmask),
                    alu_src2_type.eq(decoder.alu_src2_type),
                    reg_src_type.eq(decoder.reg_src_type),
                    alu.func.eq(decoder.alu_func),
                    branch_target.eq(decoder.branch_target),
                    branch_cond.eq(decoder.branch_cond),
                ]

            with m.State("EX"):
                m.next = "MEM"

                comb += [
                    alu.op1.eq(registers.rs1_rdata),
                    alu.op2.eq(
                        Mux(
                            alu_src2_type == AluSrc2.IMM,
                            imm,
                            registers.rs2_rdata,
                        )
                    ),
                ]
                sync += [
                    alu_out.eq(alu.out),
                ]
            with m.State("MEM"):
                with m.If((self.dmem_addr & 0b11).any()):
                    comb += [self.trap.eq(1)]
                    m.next = "HALT"
                with m.Else():
                    m.next = "WB"

                with m.If(mem_rmask.any()):
                    comb += [
                        self.dmem_rmask.eq(mem_rmask),
                        self.dmem_addr.eq(alu_out),
                    ]
                with m.If(mem_wmask.any()):
                    comb += [
                        self.dmem_wmask.eq(mem_wmask),
                        self.dmem_addr.eq(alu_out),
                        self.dmem_wdata.eq(registers.rs2_rdata),
                    ]

                sync += [
                    pc.eq(pc_plus_4),
                ]
                with m.If(
                    (branch_cond == BranchCond.ALWAYS)
                    | ((branch_cond == BranchCond.NE) & (alu_out.any()))
                ):
                    sync += [
                        pc.eq(branch_target),
                    ]

                sync += [
                    self.rvfi.pc_rdata.eq(pc),
                    self.rvfi.mem_addr.eq(self.dmem_addr),
                ]
            with m.State("WB"):
                with m.If((self.imem_addr & 0b11).any()):
                    comb += [self.trap.eq(1)]
                    m.next = "HALT"
                with m.Else():
                    m.next = "IF"

                comb += [
                    registers.rd_addr.eq(rd_addr),
                ]
                with m.Switch(reg_src_type):
                    with m.Case(RegSrc.ALU):
                        comb += [
                            registers.rd_data.eq(alu_out),
                        ]
                    with m.Case(RegSrc.PC_INCR):
                        comb += [
                            registers.rd_data.eq(pc_plus_4),
                        ]
                    with m.Case(RegSrc.MEM):
                        with m.If(mem_rmask.any()):
                            comb += [
                                registers.rd_data.eq(self.dmem_rdata),
                            ]
                with m.If(rd_addr == 0):
                    comb += [
                        registers.rd_data.eq(0),
                    ]

                sync += [
                    self.minstret.eq(self.minstret + 1),
                ]

                comb += [
                    self.imem_addr.eq(pc),
                    self.rvfi.valid.eq(1),
                ]
            with m.State("HALT"):
                comb += [
                    self.trap.eq(1),
                    self.rvfi.halt.eq(1),
                ]
                pass

        comb += [
            self.rvfi.pc_wdata.eq(pc),
            self.rvfi.rd_wdata.eq(registers.rd_data),
            self.rvfi.order.eq(self.minstret),
            self.rvfi.insn.eq(insn),
            self.rvfi.trap.eq(self.trap),
            self.rvfi.intr.eq(0),
            self.rvfi.mode.eq(Const(3)),
            self.rvfi.ixl.eq(Const(1)),
            self.rvfi.rs1_addr.eq(registers.rs1_addr),
            self.rvfi.rs2_addr.eq(registers.rs2_addr),
            self.rvfi.rs1_rdata.eq(registers.rs1_rdata),
            self.rvfi.rs2_rdata.eq(registers.rs2_rdata),
            self.rvfi.rd_addr.eq(registers.rd_addr),
            self.rvfi.mem_rmask.eq(mem_rmask),
            self.rvfi.mem_wmask.eq(mem_wmask),
            self.rvfi.mem_rdata.eq(self.dmem_rdata),
            self.rvfi.mem_wdata.eq(self.dmem_wdata),
        ]

        return m
