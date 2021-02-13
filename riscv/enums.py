from enum import Enum, unique


@unique
class AluSrc2(Enum):
    NONE = 0
    REG = 1
    IMM = 2


@unique
class RegSrc(Enum):
    NONE = 0
    COND = 1
    ALU = 2
    PC_INCR = 3
    MEM = 4


@unique
class TrapCause(Enum):
    ILLEGAL_INSTRUCTION = 2


@unique
class BranchCond(Enum):
    NONE = 0
    ALWAYS = 1
    NE = 2


@unique
class AluFunc(Enum):
    ADD = 0b0000
    SUB = 0b1000
    # SLL = 0b001
    # SLT = 0b010
    # SLTU = 0b011
    XOR = 0b0100
    # SRL_SLA = 0b101
    OR = 0b0110
    AND = 0b0111
