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
    EQ = 0b000
    NE = 0b001
    ALWAYS = 0b010
    NEVER = 0b011
    LT = 0b100
    GE = 0b101
    LTU = 0b110
    GEU = 0b111


@unique
class AluFunc(Enum): # top bit set => ~(~in1 op in2)
    ADD = 0b0000
    SUB = 0b1000
    # SLL = 0b001
    SLT = 0b0010
    SLTU = 0b011
    XOR = 0b0100
    # SRL_SLA = 0b101
    OR = 0b0110
    AND = 0b0111

@unique
class LoadFunc(Enum):
    LB = 0b000
    LH = 0b001
    LW = 0b010
    LBU = 0b100
    LHU = 0b101