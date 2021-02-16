from enum import Enum, unique


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


@unique
class TrapCause(Enum):
    ILLEGAL_INSTRUCTION = 2


@unique
class BranchCond(Enum):
    NEVER = 0
    EQ = 1
    NE = 2
    LT = 3
    GE = 4
    LTU = 5
    GEU = 6
    ALWAYS = 7


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
