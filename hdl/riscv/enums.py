from enum import Enum, unique


@unique
class MemAccessType(Enum):
    NONE = 0b111
    LB = 0b0000
    SB = 0b1000
    LH = 0b0001
    SH = 0b1001
    LW = 0b0010
    SW = 0b1010
    LBU = 0b0100
    LHU = 0b0101


@unique
class AluSrc1(Enum):
    REG = 0
    PC = 1


@unique
class AluSrc2(Enum):
    REG = 0
    IMM = 1


@unique
class RegSrc(Enum):
    NONE = 0
    COND = 1
    ALU = 2
    PC_INCR = 3
    MEM = 4
    M_CYCLE = 5
    M_INSTRET = 6


@unique
class TrapCause(Enum):
    IADDR = 0
    DADDR_L = 4
    DADDR_S = 6
    INSN = 2
    M_ECALL = 11
    M_EBREAK = 3


@unique
class BranchCond(Enum):
    EQ = 0b000
    NE = 0b001
    ALWAYS = 0b010
    NEVER = 0b011
    LT = 0b100
    GE = 0b101
    LTU = 0b110
    GEU = 0b111


@unique
class AluFunc(Enum):
    ADD_SUB = 0b000
    SLL = 0b001
    SLT = 0b010
    SLTU = 0b011
    XOR = 0b100
    SRL_SRA = 0b101
    OR = 0b110
    AND = 0b111
