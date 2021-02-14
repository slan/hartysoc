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
        self.dmem_data = Signal(32)
        self.dmem_mask = Signal(4)
        self.dmem_wr_mask = Signal(4)
        self.dmem_wr_data = Signal(32)
        self.rvfi = Record(rvfi_layout)

    def elaborate(self, platform):
        self.mcycle = Signal(64)
        self.minstret = Signal(64)
        self.mcause = Signal(32)
        self.pc_rdata = Signal(32)
        self.instr = Signal(32)

        m = Module()
        comb = m.d.comb
        sync = m.d[self._domain]

        m.submodules.registers = registers = self.registers
        m.submodules.alu = alu = ALU()
        m.submodules.decoder = decoder = Decoder()

        pc = self.pc_rdata
        pc_plus_4 = Signal.like(pc)
        instr = self.instr
        imm = Signal(32)

        # Control
        alu_src2_type = Signal(AluSrc2)
        reg_src_type = Signal(RegSrc)

        branch_cond = Signal(BranchCond)
        branch_target = Signal.like(pc)

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
                    instr.eq(self.imem_data),
                    pc_plus_4.eq(pc + 4),
                ]
            with m.State("ID"):
                m.next = "EX"
                comb += [
                    decoder.insn.eq(instr),
                    decoder.pc.eq(pc),
                ]
                sync += [
                    self.mcause.eq(decoder.mcause),
                    registers.r1_idx.eq(decoder.rs1_addr),
                    registers.r2_idx.eq(decoder.rs2_addr),
                    registers.wr_idx.eq(decoder.rd_addr),
                    imm.eq(decoder.imm),
                    self.dmem_mask.eq(decoder.mem_rmask),
                    self.dmem_wr_mask.eq(decoder.mem_wmask),
                    alu_src2_type.eq(decoder.alu_src2_type),
                    reg_src_type.eq(decoder.reg_src_type),
                    alu.func.eq(decoder.alu_func),
                    branch_target.eq(decoder.branch_target),
                    branch_cond.eq(decoder.branch_cond),
                ]

            with m.State("EX"):
                with m.If(self.mcause.any()):
                    m.next = "HALT"
                with m.Else():
                    m.next = "MEM"
                
                sync += [
                    alu.op1.eq(registers.reg1),
                    alu.op2.eq(
                        Mux(
                            alu_src2_type == AluSrc2.IMM,
                            imm,
                            registers.reg2,
                        )
                    ),
                ]
            with m.State("MEM"):
                m.next = "WB"
                
                with m.If(self.dmem_mask.any()):
                    with m.If((alu.out & 0b11).any()):
                        m.next = "HALT"
                    comb += [
                        self.dmem_addr.eq(alu.out),
                    ]
                with m.If(self.dmem_wr_mask.any()):
                    with m.If((alu.out & 0b11).any()):
                        m.next = "HALT"
                    comb += [
                        self.dmem_addr.eq(alu.out),
                        self.dmem_wr_data.eq(registers.reg2),
                    ]

                sync += [
                    self.pc_rdata.eq(pc_plus_4),
                ]
                with m.If(
                    (branch_cond == BranchCond.ALWAYS)
                    | ((branch_cond == BranchCond.NE) & (alu.out.any()))
                ):
                    with m.If(branch_target[:2].any()):
                        m.next = "HALT"
                    with m.Else():
                        sync += [
                            self.pc_rdata.eq(branch_target),
                        ]

                sync += [
                    self.rvfi.pc_rdata.eq(pc),
                    self.rvfi.mem_addr.eq(self.dmem_addr),
                ]
            with m.State("WB"):
                with m.If((self.pc_rdata&0b11).any()):
                    m.next = "HALT"
                with m.Else():
                    m.next = "IF"
                
                with m.If(registers.wr_idx == 0):
                    comb += [
                        registers.wr_data.eq(0),
                    ]
                with m.Else():
                    with m.Switch(reg_src_type):
                        with m.Case(RegSrc.ALU):
                            comb += [
                                registers.wr_en.eq(1),
                                registers.wr_data.eq(alu.out),
                            ]
                        with m.Case(RegSrc.PC_INCR):
                            comb += [
                                registers.wr_en.eq(1),
                                registers.wr_data.eq(pc_plus_4),
                            ]
                        with m.Case(RegSrc.MEM):
                            with m.If(self.dmem_mask.any()):
                                comb += [
                                    registers.wr_en.eq(1),
                                    registers.wr_data.eq(self.dmem_data),
                                ]

                sync += [
                    self.minstret.eq(self.minstret + 1),
                ]

                comb += [
                    self.imem_addr.eq(pc),
                    self.rvfi.valid.eq(1),
                ]
            with m.State("HALT"):
                comb += [self.trap.eq(1), self.rvfi.halt.eq(1)]
                pass

        comb += [
            self.rvfi.pc_wdata.eq(pc),
            self.rvfi.rd_wdata.eq(registers.wr_data),
            self.rvfi.order.eq(self.minstret),
            self.rvfi.insn.eq(instr),
            self.rvfi.trap.eq(self.trap),
            self.rvfi.intr.eq(0),
            self.rvfi.mode.eq(Const(3)),
            self.rvfi.ixl.eq(Const(1)),
            self.rvfi.rs1_addr.eq(registers.r1_idx),
            self.rvfi.rs2_addr.eq(registers.r2_idx),
            self.rvfi.rs1_rdata.eq(registers.reg1),
            self.rvfi.rs2_rdata.eq(registers.reg2),
            self.rvfi.rd_addr.eq(registers.wr_idx),
            self.rvfi.mem_rmask.eq(self.dmem_mask),
            self.rvfi.mem_wmask.eq(self.dmem_wr_mask),
            self.rvfi.mem_rdata.eq(self.dmem_data),
            self.rvfi.mem_wdata.eq(self.dmem_wr_data),
        ]

        return m
