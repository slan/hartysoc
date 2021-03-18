#include <backends/cxxrtl/cxxrtl.h>

#if defined(CXXRTL_INCLUDE_CAPI_IMPL) || \
    defined(CXXRTL_INCLUDE_VCD_CAPI_IMPL)
#include <backends/cxxrtl/cxxrtl_capi.cc>
#endif

#if defined(CXXRTL_INCLUDE_VCD_CAPI_IMPL)
#include <backends/cxxrtl/cxxrtl_vcd_capi.cc>
#endif

using namespace cxxrtl_yosys;

namespace cxxrtl_design {

// \nmigen.hierarchy: top
// \top: 1
// \generator: nMigen
struct p_top : public module {
	// \hdlname: interconnect cache_present
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:52
	wire<1> p_interconnect_2e_cache__present {0u};
	// \hdlname: interconnect cached_ibus__addr
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:47
	wire<32> p_interconnect_2e_cached__ibus____addr {0u};
	// \hdlname: interconnect cached_ibus__rmask
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:47
	wire<4> p_interconnect_2e_cached__ibus____rmask {0u};
	// \hdlname: interconnect cached_ibus__rdata
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:47
	wire<32> p_interconnect_2e_cached__ibus____rdata {0u};
	// \hdlname: console uart rx_ovf
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:29
	wire<1> p_console_2e_uart_2e_rx__ovf {0u};
	// \hdlname: console uart rx_phase
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:62
	wire<6> p_console_2e_uart_2e_rx__phase {0u};
	// \hdlname: console uart rx_rdy
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:30
	wire<1> p_console_2e_uart_2e_rx__rdy {0u};
	// \hdlname: console uart rx_count
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:64
	wire<4> p_console_2e_uart_2e_rx__count {0u};
	// \hdlname: console uart rx_shreg
	// \init: 1023
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:63
	wire<10> p_console_2e_uart_2e_rx__shreg {0x3ffu};
	// \hdlname: console uart tx_phase
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:39
	wire<6> p_console_2e_uart_2e_tx__phase {0u};
	// \hdlname: console uart tx_count
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:41
	wire<4> p_console_2e_uart_2e_tx__count {0u};
	// \hdlname: console uart tx_shreg
	// \init: 1023
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:40
	wire<10> p_console_2e_uart_2e_tx__shreg {0x3ffu};
	// \hdlname: hart alu_func
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:12
	// \enum_value_111: AND
	// \enum_value_110: OR
	// \enum_value_101: SRL_SRA
	// \enum_value_100: XOR
	// \enum_value_011: SLTU
	// \enum_value_010: SLT
	// \enum_value_001: SLL
	// \enum_value_000: ADD_SUB
	// \enum_base_type: AluFunc
	wire<3> p_hart_2e_alu__func;
	// \hdlname: hart alu_op1
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:8
	wire<32> p_hart_2e_alu__op1;
	// \hdlname: hart alu_op2
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:9
	wire<32> p_hart_2e_alu__op2;
	// \hdlname: hart decoder_insn
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:9
	wire<32> p_hart_2e_decoder__insn;
	// \hdlname: hart halt
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:43
	wire<1> p_hart_2e_halt {0u};
	// \hdlname: hart mcycle
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:46
	wire<64> p_hart_2e_mcycle {0u,0u};
	// \hdlname: hart pc
	// \init: -2147483648
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:65
	wire<32> p_hart_2e_pc {0x80000000u};
	// \hdlname: hart minstret
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:47
	wire<64> p_hart_2e_minstret {0u,0u};
	// \hdlname: hart alu out
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:10
	wire<32> p_hart_2e_alu_2e_out;
	// \hdlname: pll rs_hart_locked
	// \init: 0
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/pll.py:16
	wire<1> p_pll_2e_rs__hart__locked {0u};
	// \hdlname: pll rs_hart stage1
	// \init: 1
	// \src: /home/slan/src/nmigen/nmigen/lib/cdc.py:164
	wire<1> p_pll_2e_rs__hart_2e_stage1 {0x1u};
	// \hdlname: pll rs_hart stage0
	// \init: 1
	// \src: /home/slan/src/nmigen/nmigen/lib/cdc.py:164
	wire<1> p_pll_2e_rs__hart_2e_stage0 {0x1u};
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:21
	wire<4> p_interconnect__data__bus____wmask;
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:21
	wire<4> p_interconnect__data__bus____rmask;
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:21
	wire<32> p_interconnect__data__bus____addr;
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:31
	/*input*/ value<1> p_rx__ack;
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:21
	/*input*/ value<1> p_rx__i;
	// \src: /home/slan/src/hartysoc/hdl/harty/ram.py:20
	/*input*/ value<32> p_rp____data;
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/pll.py:26
	/*input*/ value<1> p_hart__clk;
	value<1> prev_p_hart__clk;
	bool posedge_p_hart__clk() const {
		return !prev_p_hart__clk.slice<0>().val() && p_hart__clk.slice<0>().val();
	}
	// \src: /home/slan/src/nmigen/nmigen/hdl/ir.py:526
	/*input*/ value<1> p_clk;
	value<1> prev_p_clk;
	bool posedge_p_clk() const {
		return !prev_p_clk.slice<0>().val() && p_clk.slice<0>().val();
	}
	// \src: /home/slan/src/nmigen/nmigen/hdl/ir.py:526
	/*input*/ value<1> p_rst;
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:44
	/*input*/ value<32> p_ibus____wdata;
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:44
	/*input*/ value<4> p_ibus____wmask;
	// \hdlname: interconnect instruction_bus__rdy
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:19
	/*outline*/ value<1> p_interconnect_2e_instruction__bus____rdy;
	// \hdlname: interconnect instruction_bus__rdata
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:19
	/*outline*/ value<32> p_interconnect_2e_instruction__bus____rdata;
	// \hdlname: interconnect data_bus__rdy
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:21
	/*outline*/ value<1> p_interconnect_2e_data__bus____rdy;
	// \hdlname: interconnect data_bus__rdata
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:21
	/*outline*/ value<32> p_interconnect_2e_data__bus____rdata;
	// \hdlname: interconnect ram__wmask
	// \src: /home/slan/src/hartysoc/hdl/harty/ram.py:12
	/*outline*/ value<4> p_interconnect_2e_ram____wmask;
	// \hdlname: interconnect ram__rmask
	// \src: /home/slan/src/hartysoc/hdl/harty/ram.py:12
	/*outline*/ value<4> p_interconnect_2e_ram____rmask;
	// \hdlname: interconnect console__wmask
	// \src: /home/slan/src/hartysoc/hdl/harty/console.py:14
	/*outline*/ value<4> p_interconnect_2e_console____wmask;
	// \hdlname: interconnect console__wdata
	// \src: /home/slan/src/hartysoc/hdl/harty/console.py:14
	/*outline*/ value<32> p_interconnect_2e_console____wdata;
	// \hdlname: console uart_tx_rdy
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:24
	/*outline*/ value<1> p_console_2e_uart__tx__rdy;
	// \hdlname: console uart_tx_data
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:23
	/*outline*/ value<8> p_console_2e_uart__tx__data;
	// \hdlname: ram ram__rdy
	// \src: /home/slan/src/hartysoc/hdl/harty/ram.py:12
	/*outline*/ value<1> p_ram_2e_ram____rdy;
	// \hdlname: ram ram__rdata
	// \src: /home/slan/src/hartysoc/hdl/harty/ram.py:12
	/*outline*/ value<32> p_ram_2e_ram____rdata;
	// \hdlname: hart ibus__addr
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:44
	/*outline*/ value<32> p_hart_2e_ibus____addr;
	// \hdlname: hart ibus__rmask
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:44
	/*outline*/ value<4> p_hart_2e_ibus____rmask;
	// \hdlname: hart dbus__addr
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:45
	/*outline*/ value<32> p_hart_2e_dbus____addr;
	// \hdlname: hart dbus__rmask
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:45
	/*outline*/ value<4> p_hart_2e_dbus____rmask;
	// \hdlname: hart dbus__wmask
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:45
	/*outline*/ value<4> p_hart_2e_dbus____wmask;
	// \hdlname: hart dbus__wdata
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:45
	/*outline*/ value<32> p_hart_2e_dbus____wdata;
	// \hdlname: hart registers_mem_r_addr
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:8
	/*outline*/ value<5> p_hart_2e_registers__mem__r__addr;
	// \hdlname: hart registers_mem_r_addr$1
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:9
	/*outline*/ value<5> p_hart_2e_registers__mem__r__addr_24_1;
	// \hdlname: hart registers_mem_w_data
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:10
	/*outline*/ value<32> p_hart_2e_registers__mem__w__data;
	// \hdlname: hart registers_mem_w_addr
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:10
	/*outline*/ value<5> p_hart_2e_registers__mem__w__addr;
	// \hdlname: hart alu_func_ex
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:13
	/*outline*/ value<1> p_hart_2e_alu__func__ex;
	// \hdlname: hart decoder_pc
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:10
	/*outline*/ value<32> p_hart_2e_decoder__pc;
	// \hdlname: hart pc_incr
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:66
	/*outline*/ value<32> p_hart_2e_pc__incr;
	// \hdlname: hart branch_taken
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:202
	/*outline*/ value<1> p_hart_2e_branch__taken;
	// \hdlname: hart branch_target
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:201
	/*outline*/ value<32> p_hart_2e_branch__target;
	// \hdlname: hart pc_wdata
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:200
	/*outline*/ value<32> p_hart_2e_pc__wdata;
	// \hdlname: hart registers mem_w_en
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:10
	/*outline*/ value<1> p_hart_2e_registers_2e_mem__w__en;
	// \hdlname: hart registers mem_r_data$2
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:9
	/*outline*/ value<32> p_hart_2e_registers_2e_mem__r__data_24_2;
	// \hdlname: hart registers mem_r_data
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:8
	/*outline*/ value<32> p_hart_2e_registers_2e_mem__r__data;
	// \hdlname: hart alu eq
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:11
	/*outline*/ value<1> p_hart_2e_alu_2e_eq;
	// \hdlname: hart decoder branch_target
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:27
	/*outline*/ value<32> p_hart_2e_decoder_2e_branch__target;
	// \hdlname: hart decoder branch_cond
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:26
	// \enum_value_111: GEU
	// \enum_value_110: LTU
	// \enum_value_101: GE
	// \enum_value_100: LT
	// \enum_value_011: NEVER
	// \enum_value_010: ALWAYS
	// \enum_value_001: NE
	// \enum_value_000: EQ
	// \enum_base_type: BranchCond
	/*outline*/ value<3> p_hart_2e_decoder_2e_branch__cond;
	// \hdlname: hart decoder reg_src
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:23
	// \enum_value_101: M_INSTRET
	// \enum_value_100: M_CYCLE
	// \enum_value_011: PC_INCR
	// \enum_value_010: ALU
	// \enum_value_000: NONE
	// \enum_base_type: RegSrc
	/*outline*/ value<3> p_hart_2e_decoder_2e_reg__src;
	// \hdlname: hart decoder rd_addr
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:17
	/*outline*/ value<5> p_hart_2e_decoder_2e_rd__addr;
	// \hdlname: hart decoder mem_func
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:19
	// \enum_value_0101: LHU
	// \enum_value_0100: LBU
	// \enum_value_1010: SW
	// \enum_value_0010: LW
	// \enum_value_1001: SH
	// \enum_value_0001: LH
	// \enum_value_1000: SB
	// \enum_value_0000: LB
	// \enum_value_1111: NONE
	// \enum_base_type: MemFunc
	/*outline*/ value<4> p_hart_2e_decoder_2e_mem__func;
	// \hdlname: hart decoder imm
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:18
	/*outline*/ value<32> p_hart_2e_decoder_2e_imm;
	// \hdlname: hart decoder alu_src2
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:22
	// \enum_value_1: IMM
	// \enum_value_0: REG
	// \enum_base_type: AluSrc2
	/*outline*/ value<1> p_hart_2e_decoder_2e_alu__src2;
	// \hdlname: hart decoder alu_src1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:21
	// \enum_value_1: PC
	// \enum_value_0: REG
	// \enum_base_type: AluSrc1
	/*outline*/ value<1> p_hart_2e_decoder_2e_alu__src1;
	// \hdlname: hart decoder alu_func_ex
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:25
	/*outline*/ value<1> p_hart_2e_decoder_2e_alu__func__ex;
	// \hdlname: hart decoder alu_func
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:24
	// \enum_value_111: AND
	// \enum_value_110: OR
	// \enum_value_101: SRL_SRA
	// \enum_value_100: XOR
	// \enum_value_011: SLTU
	// \enum_value_010: SLT
	// \enum_value_001: SLL
	// \enum_value_000: ADD_SUB
	// \enum_base_type: AluFunc
	/*outline*/ value<3> p_hart_2e_decoder_2e_alu__func;
	// \hdlname: hart decoder rs2_addr
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:16
	/*outline*/ value<5> p_hart_2e_decoder_2e_rs2__addr;
	// \hdlname: hart decoder rs1_addr
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:15
	/*outline*/ value<5> p_hart_2e_decoder_2e_rs1__addr;
	// \hdlname: hart decoder trap
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:13
	/*outline*/ value<1> p_hart_2e_decoder_2e_trap;
	// \hdlname: pll rs_hart async_ff_rst
	// \src: /home/slan/src/nmigen/nmigen/lib/cdc.py:163
	/*outline*/ value<1> p_pll_2e_rs__hart_2e_async__ff__rst;
	// \hdlname: hart registers mem
	memory<32> memory_p_hart_2e_registers_2e_mem { 32u,
		memory<32>::init<32> { 0, {
			value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u},
			value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u},
			value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u},
			value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u},
			value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u},
			value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u},
			value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u},
			value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u}, value<32>{0x00000000u},
		}},
	};

	p_top() {}
	p_top(adopt, p_top other) {}

	void reset() override {
		*this = p_top(adopt {}, std::move(*this));
	}

	bool eval() override;
	bool commit() override;

	void debug_eval();
	debug_outline debug_eval_outline { std::bind(&p_top::debug_eval, this) };

	void debug_info(debug_items &items, std::string path = "") override;
}; // struct p_top

bool p_top::eval() {
	bool converged = false;
	bool posedge_p_hart__clk = this->posedge_p_hart__clk();
	bool posedge_p_clk = this->posedge_p_clk();
	// \hdlname: interconnect instruction_bus__addr
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:19
	value<32> p_interconnect_2e_instruction__bus____addr;
	// \hdlname: interconnect instruction_bus__rmask
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:19
	value<4> p_interconnect_2e_instruction__bus____rmask;
	// \hdlname: interconnect instruction_bus__wmask
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:19
	value<4> p_interconnect_2e_instruction__bus____wmask;
	// \hdlname: interconnect data_bus__addr
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:21
	value<32> p_interconnect_2e_data__bus____addr;
	// \hdlname: interconnect data_bus__rmask
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:21
	value<4> p_interconnect_2e_data__bus____rmask;
	// \hdlname: interconnect data_bus__wmask
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:21
	value<4> p_interconnect_2e_data__bus____wmask;
	// \hdlname: interconnect hart_clk
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/pll.py:26
	value<1> p_interconnect_2e_hart__clk;
	// \hdlname: interconnect hart_rst
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/pll.py:26
	value<1> p_interconnect_2e_hart__rst;
	// \hdlname: interconnect ram__rdy
	// \src: /home/slan/src/hartysoc/hdl/harty/ram.py:12
	value<1> p_interconnect_2e_ram____rdy;
	// \hdlname: interconnect ram__rdata
	// \src: /home/slan/src/hartysoc/hdl/harty/ram.py:12
	value<32> p_interconnect_2e_ram____rdata;
	// \hdlname: interconnect console__rdy
	// \src: /home/slan/src/hartysoc/hdl/harty/console.py:14
	value<1> p_interconnect_2e_console____rdy;
	// \hdlname: interconnect console__rdata
	// \src: /home/slan/src/hartysoc/hdl/harty/console.py:14
	value<32> p_interconnect_2e_console____rdata;
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:61
	value<1> i_flatten_5c_interconnect_2e__24_85;
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:100
	value<1> i_flatten_5c_interconnect_2e__24_115;
	value<4> i_flatten_5c_interconnect_2e__24_procmux_24_88__Y;
	value<4> i_flatten_5c_interconnect_2e__24_procmux_24_99__Y;
	value<4> i_flatten_5c_interconnect_2e__24_procmux_24_110__Y;
	value<32> i_flatten_5c_interconnect_2e__24_procmux_24_150__Y;
	// \hdlname: console console__wmask
	// \src: /home/slan/src/hartysoc/hdl/harty/console.py:14
	value<4> p_console_2e_console____wmask;
	// \hdlname: console uart rx_ack
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:31
	value<1> p_console_2e_uart_2e_rx__ack;
	// \hdlname: console uart rx_i
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:21
	value<1> p_console_2e_uart_2e_rx__i;
	// \hdlname: console uart tx_rdy
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/uart.py:24
	value<1> p_console_2e_uart_2e_tx__rdy;
	// \hdlname: console uart hart_rst
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/pll.py:26
	value<1> p_console_2e_uart_2e_hart__rst;
	// \hdlname: console uart hart_clk
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/pll.py:26
	value<1> p_console_2e_uart_2e_hart__clk;
	// \hdlname: ram ram__wmask
	// \src: /home/slan/src/hartysoc/hdl/harty/ram.py:12
	value<4> p_ram_2e_ram____wmask;
	// \hdlname: ram ram__rmask
	// \src: /home/slan/src/hartysoc/hdl/harty/ram.py:12
	value<4> p_ram_2e_ram____rmask;
	// \hdlname: hart ibus__rdy
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:44
	value<1> p_hart_2e_ibus____rdy;
	// \hdlname: hart dbus__rdy
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:45
	value<1> p_hart_2e_dbus____rdy;
	// \hdlname: hart dbus__addr
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:45
	value<32> p_hart_2e_dbus____addr;
	// \hdlname: hart dbus__rdata
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:45
	value<32> p_hart_2e_dbus____rdata;
	// \hdlname: hart dbus__wdata
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:45
	value<32> p_hart_2e_dbus____wdata;
	// \hdlname: hart hart_clk
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/pll.py:26
	value<1> p_hart_2e_hart__clk;
	// \hdlname: hart hart_rst
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/pll.py:26
	value<1> p_hart_2e_hart__rst;
	// \hdlname: hart registers_mem_r_addr
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:8
	value<5> p_hart_2e_registers__mem__r__addr;
	// \hdlname: hart registers_mem_r_addr$1
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:9
	value<5> p_hart_2e_registers__mem__r__addr_24_1;
	// \hdlname: hart registers_mem_r_data$2
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:9
	value<32> p_hart_2e_registers__mem__r__data_24_2;
	// \hdlname: hart alu_out
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:10
	value<32> p_hart_2e_alu__out;
	// \hdlname: hart alu_eq
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:11
	value<1> p_hart_2e_alu__eq;
	// \hdlname: hart decoder_mem_func
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:19
	// \enum_value_0101: LHU
	// \enum_value_0100: LBU
	// \enum_value_1010: SW
	// \enum_value_0010: LW
	// \enum_value_1001: SH
	// \enum_value_0001: LH
	// \enum_value_1000: SB
	// \enum_value_0000: LB
	// \enum_value_1111: NONE
	// \enum_base_type: MemFunc
	value<4> p_hart_2e_decoder__mem__func;
	// \hdlname: hart decoder_rd_addr
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:17
	value<5> p_hart_2e_decoder__rd__addr;
	// \hdlname: hart decoder_reg_src
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:23
	// \enum_value_101: M_INSTRET
	// \enum_value_100: M_CYCLE
	// \enum_value_011: PC_INCR
	// \enum_value_010: ALU
	// \enum_value_000: NONE
	// \enum_base_type: RegSrc
	value<3> p_hart_2e_decoder__reg__src;
	// \hdlname: hart decoder_branch_cond
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:26
	// \enum_value_111: GEU
	// \enum_value_110: LTU
	// \enum_value_101: GE
	// \enum_value_100: LT
	// \enum_value_011: NEVER
	// \enum_value_010: ALWAYS
	// \enum_value_001: NE
	// \enum_value_000: EQ
	// \enum_base_type: BranchCond
	value<3> p_hart_2e_decoder__branch__cond;
	// \hdlname: hart decoder_branch_target
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:27
	value<32> p_hart_2e_decoder__branch__target;
	// \hdlname: hart pc_incr
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:66
	value<32> p_hart_2e_pc__incr;
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:72
	value<1> i_flatten_5c_hart_2e__24_69;
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:119
	value<1> i_flatten_5c_hart_2e__24_71;
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:14
	value<32> i_flatten_5c_hart_2e__24_103;
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:14
	value<32> i_flatten_5c_hart_2e__24_108;
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:14
	value<32> i_flatten_5c_hart_2e__24_113;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_300__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_301__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_312__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_313__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_340__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_341__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_435__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_436__CMP;
	// \hdlname: hart registers mem_w_en
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:10
	value<1> p_hart_2e_registers_2e_mem__w__en;
	// \hdlname: hart registers mem_w_addr
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:10
	value<5> p_hart_2e_registers_2e_mem__w__addr;
	// \hdlname: hart registers mem_r_data$2
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:9
	value<32> p_hart_2e_registers_2e_mem__r__data_24_2;
	// \hdlname: hart registers mem_r_data
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:8
	value<32> p_hart_2e_registers_2e_mem__r__data;
	// \hdlname: hart alu op2
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:9
	value<32> p_hart_2e_alu_2e_op2;
	// \hdlname: hart alu op1
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:8
	value<32> p_hart_2e_alu_2e_op1;
	// \hdlname: hart alu func_ex
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:13
	value<1> p_hart_2e_alu_2e_func__ex;
	// \hdlname: hart alu func
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:12
	// \enum_value_111: AND
	// \enum_value_110: OR
	// \enum_value_101: SRL_SRA
	// \enum_value_100: XOR
	// \enum_value_011: SLTU
	// \enum_value_010: SLT
	// \enum_value_001: SLL
	// \enum_value_000: ADD_SUB
	// \enum_base_type: AluFunc
	value<3> p_hart_2e_alu_2e_func;
	value<5> i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP;
	value<3> i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_633__CMP;
	value<6> i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP;
	value<6> i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP;
	value<6> i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP;
	value<2> i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_503__CMP;
	// \src: /home/slan/src/nmigen/nmigen/hdl/ast.py:269
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_25;
	// \src: /home/slan/src/nmigen/nmigen/hdl/ast.py:269
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_23;
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:174
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_21;
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:143
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_19;
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:128
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_17;
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:92
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_15;
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:74
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_13;
	// \hdlname: hart decoder branch_cond
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:26
	// \enum_value_111: GEU
	// \enum_value_110: LTU
	// \enum_value_101: GE
	// \enum_value_100: LT
	// \enum_value_011: NEVER
	// \enum_value_010: ALWAYS
	// \enum_value_001: NE
	// \enum_value_000: EQ
	// \enum_base_type: BranchCond
	value<3> p_hart_2e_decoder_2e_branch__cond;
	// \hdlname: hart decoder imm
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:18
	value<32> p_hart_2e_decoder_2e_imm;
	// \hdlname: hart decoder insn
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:9
	value<32> p_hart_2e_decoder_2e_insn;
	// \hdlname: pll rst
	// \src: /home/slan/src/nmigen/nmigen/hdl/ir.py:526
	value<1> p_pll_2e_rst;
	// \hdlname: pll rs_hart async_ff_rst
	// \src: /home/slan/src/nmigen/nmigen/lib/cdc.py:163
	value<1> p_pll_2e_rs__hart_2e_async__ff__rst;
	// \hdlname: pll rs_hart async_ff_clk
	// \src: /home/slan/src/nmigen/nmigen/lib/cdc.py:163
	value<1> p_pll_2e_rs__hart_2e_async__ff__clk;
	// \src: /home/slan/src/hartysoc/hdl/kitchensink/pll.py:26
	value<1> p_pll__hart__rst;
	// connection
	p_hart_2e_dbus____addr.slice<1,0>() = value<2>{0u};
	// connection
	p_interconnect_2e_instruction__bus____wmask = p_ibus____wmask;
	// connection
	p_interconnect_2e_console____rdata = value<32>{0x1u};
	// connection
	p_interconnect_2e_console____rdy = value<1>{0x1u};
	// cells $flatten\hart.$procmux$487 $flatten\hart.$9
	p_interconnect_2e_instruction__bus____rmask = (not_u<1>(p_hart_2e_halt.curr) ? value<4>{0xfu} : value<4>{0u});
	// cells $flatten\hart.$procmux$485 $flatten\hart.$11
	p_interconnect_2e_instruction__bus____addr = (not_u<1>(p_hart_2e_halt.curr) ? p_hart_2e_pc.curr : value<32>{0u});
	// cells $flatten\interconnect.$94 $flatten\interconnect.$93 $flatten\interconnect.$91 $flatten\interconnect.$89 $flatten\interconnect.$87
	i_flatten_5c_interconnect_2e__24_85 = not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask)));
	// cells $flatten\interconnect.$procmux$88 $flatten\interconnect.$procmux$86 $flatten\interconnect.$procmux$87_CMP0
	i_flatten_5c_interconnect_2e__24_procmux_24_88__Y = (i_flatten_5c_interconnect_2e__24_85 ? (eq_uu<1>(p_interconnect_2e_instruction__bus____addr.slice<31>().val(), value<1>{0u}) ? value<4>{0u} : p_interconnect_2e_instruction__bus____wmask) : value<4>{0u});
	// cells $flatten\interconnect.$procmux$110 $flatten\interconnect.$62 $flatten\interconnect.$61 $flatten\interconnect.$59 $flatten\interconnect.$57 $flatten\interconnect.$55 $flatten\interconnect.$procmux$108 $flatten\interconnect.$procmux$109_CMP0
	i_flatten_5c_interconnect_2e__24_procmux_24_110__Y = (not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask))) ? (eq_uu<1>(p_interconnect_2e_instruction__bus____addr.slice<31>().val(), value<1>{0u}) ? value<4>{0u} : p_interconnect_2e_instruction__bus____rmask) : value<4>{0u});
	// connection
	p_hart_2e_decoder_2e_insn = p_hart_2e_decoder__insn.curr;
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$544_CMP5
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP.slice<5>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x3u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$544_CMP4
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP.slice<4>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x7u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$544_CMP3
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP.slice<3>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x6u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$544_CMP2
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP.slice<2>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$544_CMP1
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x2u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$544_CMP0
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$532_CMP5
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP.slice<5>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x3u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$532_CMP4
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP.slice<4>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x7u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$532_CMP3
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP.slice<3>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x6u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$532_CMP2
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP.slice<2>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$532_CMP1
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x2u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$532_CMP0
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0u});
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:204|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$503_CMP1
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_503__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x5u});
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:204|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$503_CMP0
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_503__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0u});
	// \src: /home/slan/src/nmigen/nmigen/hdl/ast.py:269
	// cell $flatten\hart.\decoder.$26
	i_flatten_5c_hart_2e__5c_decoder_2e__24_25 = pos_u<32>(p_hart_2e_decoder_2e_insn.slice<24,20>().val());
	// \src: /home/slan/src/nmigen/nmigen/hdl/ast.py:269
	// cell $flatten\hart.\decoder.$24
	i_flatten_5c_hart_2e__5c_decoder_2e__24_23 = pos_u<32>(p_hart_2e_decoder_2e_insn.slice<24,20>().val());
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:174
	// cell $flatten\hart.\decoder.$22
	i_flatten_5c_hart_2e__5c_decoder_2e__24_21 = pos_s<32>(p_hart_2e_decoder_2e_insn.slice<31,20>().val());
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:143
	// cell $flatten\hart.\decoder.$20
	i_flatten_5c_hart_2e__5c_decoder_2e__24_19 = pos_s<32>(p_hart_2e_decoder_2e_insn.slice<31,25>().concat(p_hart_2e_decoder_2e_insn.slice<11,7>()).val());
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:128
	// cell $flatten\hart.\decoder.$18
	i_flatten_5c_hart_2e__5c_decoder_2e__24_17 = pos_s<32>(p_hart_2e_decoder_2e_insn.slice<31,20>().val());
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:92
	// cell $flatten\hart.\decoder.$16
	i_flatten_5c_hart_2e__5c_decoder_2e__24_15 = pos_s<32>(p_hart_2e_decoder_2e_insn.slice<31,20>().val());
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:74
	// cell $flatten\hart.\decoder.$14
	i_flatten_5c_hart_2e__5c_decoder_2e__24_13 = pos_s<32>(p_hart_2e_decoder_2e_insn.slice<31>().concat(p_hart_2e_decoder_2e_insn.slice<19,12>()).concat(p_hart_2e_decoder_2e_insn.slice<20>()).concat(p_hart_2e_decoder_2e_insn.slice<30,21>()).concat(value<1>{0u}).val());
	// cells $flatten\hart.\decoder.$procmux$499 $flatten\hart.\decoder.$procmux$500_CMP0 $flatten\hart.\decoder.$procmux$501_CMP0 $flatten\hart.\decoder.$35
	p_hart_2e_decoder__mem__func = (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x23u}) ? value<1>{0x1u}.concat(p_hart_2e_decoder_2e_insn.slice<14,12>()).val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x3u}) ? pos_u<4>(p_hart_2e_decoder_2e_insn.slice<14,12>().val()) : value<4>{0xfu}));
	// cells $flatten\hart.\decoder.$procmux$545 $flatten\hart.\decoder.$procmux$546_CMP0 $flatten\hart.\decoder.$procmux$547_CMP0 $flatten\hart.\decoder.$procmux$548_CMP0 $flatten\hart.\decoder.$procmux$549_CMP0 $flatten\hart.\decoder.$procmux$550_CMP0 $flatten\hart.\decoder.$procmux$541 $flatten\hart.\decoder.$procmux$542_CMP0 $flatten\hart.\decoder.$procmux$543_CMP0 $flatten\hart.\decoder.$procmux$544_ANY
	p_hart_2e_decoder_2e_imm.slice<11,0>() = (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x13u}) ? (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x5u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_25.slice<11,0>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x1u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_23.slice<11,0>().val() : (reduce_or<1>(i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_21.slice<11,0>().val() : value<12>{0u}))) : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x23u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_19.slice<11,0>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x3u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_17.slice<11,0>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<10>{0x67u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_15.slice<11,0>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x6fu}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_13.slice<11,0>().val() : value<12>{0u})))));
	// cells $flatten\hart.\decoder.$procmux$533 $flatten\hart.\decoder.$procmux$534_CMP0 $flatten\hart.\decoder.$procmux$535_CMP0 $flatten\hart.\decoder.$procmux$536_CMP0 $flatten\hart.\decoder.$procmux$537_CMP0 $flatten\hart.\decoder.$procmux$538_CMP0 $flatten\hart.\decoder.$procmux$539_CMP0 $flatten\hart.\decoder.$procmux$540_CMP0 $flatten\hart.\decoder.$procmux$529 $flatten\hart.\decoder.$procmux$530_CMP0 $flatten\hart.\decoder.$procmux$531_CMP0 $flatten\hart.\decoder.$procmux$532_ANY
	p_hart_2e_decoder_2e_imm.slice<31,12>() = (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x13u}) ? (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x5u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_25.slice<31,12>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x1u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_23.slice<31,12>().val() : (reduce_or<1>(i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_21.slice<31,12>().val() : value<20>{0u}))) : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x23u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_19.slice<31,12>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x3u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_17.slice<31,12>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<10>{0x67u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_15.slice<31,12>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x6fu}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_13.slice<31,12>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x17u}) ? p_hart_2e_decoder_2e_insn.slice<31,12>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x37u}) ? p_hart_2e_decoder_2e_insn.slice<31,12>().val() : value<20>{0u})))))));
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:121|/home/slan/src/hartysoc/hdl/riscv/hart.py:126
	// cell $flatten\hart.$procmux$435_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_435__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x1u});
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:121|/home/slan/src/hartysoc/hdl/riscv/hart.py:126
	// cell $flatten\hart.$procmux$435_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_435__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x5u});
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:121|/home/slan/src/hartysoc/hdl/riscv/hart.py:124
	// cell $flatten\hart.$procmux$436_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_436__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0u});
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:121|/home/slan/src/hartysoc/hdl/riscv/hart.py:124
	// cell $flatten\hart.$procmux$436_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_436__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x4u});
	// connection
	p_hart_2e_alu_2e_op1 = p_hart_2e_alu__op1.curr;
	// connection
	p_hart_2e_alu_2e_op2 = p_hart_2e_alu__op2.curr;
	// connection
	p_hart_2e_alu_2e_func = p_hart_2e_alu__func.curr;
	// connection
	p_hart_2e_alu__out = p_hart_2e_alu_2e_out.curr;
	// connection
	p_interconnect_2e_data__bus____addr = p_interconnect__data__bus____addr.curr;
	// connection
	p_interconnect_2e_data__bus____wmask = p_interconnect__data__bus____wmask.curr;
	// connection
	p_interconnect_2e_data__bus____rmask = p_interconnect__data__bus____rmask.curr;
	// cells $flatten\interconnect.$116 $flatten\interconnect.$114 $flatten\interconnect.$112 $flatten\interconnect.$110 $flatten\interconnect.$108 $flatten\interconnect.$106 $flatten\interconnect.$105 $flatten\interconnect.$103 $flatten\interconnect.$101 $flatten\interconnect.$99 $flatten\interconnect.$97
	i_flatten_5c_interconnect_2e__24_115 = or_uu<1>(not_u<1>(and_uu<1>(eq_uu<1>(p_interconnect_2e_data__bus____addr.slice<31>().val(), p_interconnect_2e_instruction__bus____addr.slice<31>().val()), or_uu<1>(reduce_or<1>(p_interconnect_2e_data__bus____wmask), reduce_or<1>(p_interconnect_2e_data__bus____rmask)))), and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask)));
	// cells $flatten\interconnect.$procmux$116 $flatten\interconnect.$84 $flatten\interconnect.$82 $flatten\interconnect.$80 $flatten\interconnect.$78 $flatten\interconnect.$76 $flatten\interconnect.$74 $flatten\interconnect.$73 $flatten\interconnect.$71 $flatten\interconnect.$69 $flatten\interconnect.$67 $flatten\interconnect.$65 $flatten\interconnect.$procmux$114 $flatten\interconnect.$procmux$115_CMP0
	p_ram_2e_ram____rmask = (or_uu<1>(not_u<1>(and_uu<1>(eq_uu<1>(p_interconnect_2e_data__bus____addr.slice<31>().val(), p_interconnect_2e_instruction__bus____addr.slice<31>().val()), or_uu<1>(reduce_or<1>(p_interconnect_2e_data__bus____wmask), reduce_or<1>(p_interconnect_2e_data__bus____rmask)))), and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask))) ? (eq_uu<1>(p_interconnect_2e_data__bus____addr.slice<31>().val(), value<1>{0u}) ? i_flatten_5c_interconnect_2e__24_procmux_24_110__Y : p_interconnect_2e_data__bus____rmask) : i_flatten_5c_interconnect_2e__24_procmux_24_110__Y);
	// cells $flatten\interconnect.$procmux$94 $flatten\interconnect.$procmux$92 $flatten\interconnect.$procmux$93_CMP0
	p_ram_2e_ram____wmask = (i_flatten_5c_interconnect_2e__24_115 ? (eq_uu<1>(p_interconnect_2e_data__bus____addr.slice<31>().val(), value<1>{0u}) ? i_flatten_5c_interconnect_2e__24_procmux_24_88__Y : p_interconnect_2e_data__bus____wmask) : i_flatten_5c_interconnect_2e__24_procmux_24_88__Y);
	// cells $flatten\ram.$procmux$269 $flatten\ram.$16 $flatten\ram.$procmux$267 $flatten\ram.$18
	p_interconnect_2e_ram____rdy = (reduce_or<1>(p_ram_2e_ram____wmask) ? value<1>{0x1u} : (reduce_or<1>(p_ram_2e_ram____rmask) ? value<1>{0x1u} : value<1>{0u}));
	// cells $flatten\interconnect.$procmux$133 $flatten\interconnect.$52 $flatten\interconnect.$51 $flatten\interconnect.$49 $flatten\interconnect.$47 $flatten\interconnect.$45 $flatten\interconnect.$procmux$131 $flatten\interconnect.$procmux$132_CMP0
	p_hart_2e_ibus____rdy = (not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask))) ? (eq_uu<1>(p_interconnect_2e_instruction__bus____addr.slice<31>().val(), value<1>{0u}) ? p_interconnect_2e_console____rdy : p_interconnect_2e_ram____rdy) : value<1>{0x1u});
	// cells $flatten\hart.$procmux$441 $flatten\hart.$54 $flatten\hart.$procmux$439 $flatten\hart.$procmux$437 $flatten\hart.$56 $flatten\hart.$procmux$433 $flatten\hart.$procmux$434_CMP0 $flatten\hart.$procmux$435_ANY $flatten\hart.$procmux$436_ANY $flatten\hart.$60 $flatten\hart.$58
	p_interconnect__data__bus____rmask.next = (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (ne_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xfu}) ? (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x2u}) ? value<4>{0xfu} : (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_435__CMP) ? (p_hart_2e_alu__out.slice<1>().val() ? value<4>{0xcu} : value<4>{0x3u}) : (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_436__CMP) ? sshl_uu<4>(value<1>{0x1u}, p_hart_2e_alu__out.slice<1,0>().val()) : value<4>{0u}))) : value<4>{0u}) : value<4>{0u}) : value<4>{0u});
	// cells $flatten\hart.$procmux$431 $flatten\hart.$62 $flatten\hart.$procmux$429 $flatten\hart.$procmux$427 $flatten\hart.$64 $flatten\hart.$procmux$423 $flatten\hart.$procmux$424_CMP0 $flatten\hart.$procmux$425_CMP0 $flatten\hart.$procmux$426_CMP0 $flatten\hart.$68 $flatten\hart.$66
	p_interconnect__data__bus____wmask.next = (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (ne_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xfu}) ? (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xau}) ? value<4>{0xfu} : (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x9u}) ? (p_hart_2e_alu__out.slice<1>().val() ? value<4>{0xcu} : value<4>{0x3u}) : (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x8u}) ? sshl_uu<4>(value<1>{0x1u}, p_hart_2e_alu__out.slice<1,0>().val()) : value<4>{0u}))) : value<4>{0u}) : value<4>{0u}) : value<4>{0u});
	// cells $flatten\hart.$procmux$447 $flatten\hart.$50 $flatten\hart.$procmux$445 $flatten\hart.$procmux$443 $flatten\hart.$52
	p_hart_2e_dbus____addr.slice<31,2>() = (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (ne_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xfu}) ? p_hart_2e_alu__out.slice<31,2>().val() : value<30>{0u}) : value<30>{0u}) : value<30>{0u});
	// connection
	p_interconnect__data__bus____addr.next = p_hart_2e_dbus____addr;
	// cells $flatten\hart.$procmux$459 $flatten\hart.$28 $flatten\hart.$procmux$457 $flatten\hart.\decoder.$procmux$504 $flatten\hart.\decoder.$procmux$505_CMP0 $flatten\hart.\decoder.$procmux$508_CMP0 $flatten\hart.\decoder.$procmux$509_CMP0 $flatten\hart.\decoder.$procmux$502 $flatten\hart.\decoder.$procmux$503_ANY $flatten\hart.\decoder.$procmux$506 $flatten\hart.\decoder.$procmux$507_CMP0
	p_hart_2e_alu_2e_func__ex = (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<31>().concat(p_hart_2e_decoder_2e_insn.slice<29,25>()).concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<13>{0x33u}) ? (reduce_or<1>(i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_503__CMP) ? p_hart_2e_decoder_2e_insn.slice<30>().val() : value<1>{0u}) : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x13u}) ? (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x5u}) ? p_hart_2e_decoder_2e_insn.slice<30>().val() : value<1>{0u}) : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x63u}) ? value<1>{0x1u} : value<1>{0u}))) : value<1>{0u}) : value<1>{0u});
	// cells $flatten\hart.\alu.$procmux$648 $flatten\hart.\alu.$procmux$649_CMP0 $flatten\hart.\alu.$procmux$650_CMP0 $flatten\hart.\alu.$procmux$651_CMP0 $flatten\hart.\alu.$procmux$652_CMP0 $flatten\hart.\alu.$procmux$653_CMP0 $flatten\hart.\alu.$procmux$654_CMP0 $flatten\hart.\alu.$procmux$655_CMP0 $flatten\hart.\alu.$procmux$656_CMP0 $flatten\hart.\alu.$39 $flatten\hart.\alu.$37 $flatten\hart.\alu.$33 $flatten\hart.\alu.$35 $flatten\hart.\alu.$30 $flatten\hart.\alu.$27 $flatten\hart.\alu.$26 $flatten\hart.\alu.$23 $flatten\hart.\alu.$22 $flatten\hart.\alu.$19 $flatten\hart.\alu.$17 $flatten\hart.\alu.$15 $flatten\hart.\alu.$13 $flatten\hart.\alu.$9 $flatten\hart.\alu.$8 $flatten\hart.\alu.$6 $flatten\hart.\alu.$11
	p_hart_2e_alu_2e_out.next = (eq_uu<1>(p_hart_2e_alu_2e_func, value<3>{0x5u}) ? sshr_su<33>((p_hart_2e_alu_2e_func__ex ? pos_s<33>(p_hart_2e_alu_2e_op1) : pos_u<33>(p_hart_2e_alu_2e_op1)), p_hart_2e_alu_2e_op2.slice<4,0>().val()).slice<31,0>().val() : (eq_uu<1>(p_hart_2e_alu_2e_func, value<3>{0x1u}) ? sshl_uu<63>(p_hart_2e_alu_2e_op1, p_hart_2e_alu_2e_op2.slice<4,0>().val()).slice<31,0>().val() : (eq_uu<1>(p_hart_2e_alu_2e_func, value<3>{0x3u}) ? pos_u<32>(lt_uu<1>(p_hart_2e_alu_2e_op1, p_hart_2e_alu_2e_op2)) : (eq_uu<1>(p_hart_2e_alu_2e_func, value<3>{0x2u}) ? pos_u<32>(lt_ss<1>(p_hart_2e_alu_2e_op1, p_hart_2e_alu_2e_op2)) : (eq_uu<1>(p_hart_2e_alu_2e_func, value<3>{0x7u}) ? and_uu<32>(p_hart_2e_alu_2e_op1, p_hart_2e_alu_2e_op2) : (eq_uu<1>(p_hart_2e_alu_2e_func, value<3>{0x6u}) ? or_uu<32>(p_hart_2e_alu_2e_op1, p_hart_2e_alu_2e_op2) : (eq_uu<1>(p_hart_2e_alu_2e_func, value<3>{0x4u}) ? xor_uu<32>(p_hart_2e_alu_2e_op1, p_hart_2e_alu_2e_op2) : (eq_uu<1>(p_hart_2e_alu_2e_func, value<3>{0u}) ? (p_hart_2e_alu_2e_func__ex ? not_u<33>(add_uu<33>(not_u<32>(p_hart_2e_alu_2e_op1), p_hart_2e_alu_2e_op2)) : add_uu<33>(p_hart_2e_alu_2e_op1, p_hart_2e_alu_2e_op2)).slice<31,0>().val() : value<32>{0u}))))))));
	// cells $flatten\hart.$procmux$463 $flatten\hart.$26 $flatten\hart.$procmux$461 $flatten\hart.\decoder.$procmux$525 $flatten\hart.\decoder.$procmux$526_CMP0 $flatten\hart.\decoder.$procmux$527_CMP0 $flatten\hart.\decoder.$procmux$528_CMP0 $flatten\hart.\decoder.$28
	p_hart_2e_alu__func.next = (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<31>().concat(p_hart_2e_decoder_2e_insn.slice<29,25>()).concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<13>{0x33u}) ? p_hart_2e_decoder_2e_insn.slice<14,12>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x13u}) ? p_hart_2e_decoder_2e_insn.slice<14,12>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x63u}) ? (p_hart_2e_decoder_2e_insn.slice<13>().val() ? value<3>{0x3u} : value<3>{0x2u}) : value<3>{0u}))) : value<3>{0u}) : value<3>{0u});
	// cells $flatten\hart.$procmux$467 $flatten\hart.$24 $flatten\hart.$procmux$465 $flatten\hart.\decoder.$procmux$510 $flatten\hart.\decoder.$procmux$511_CMP0 $flatten\hart.\decoder.$procmux$512_CMP0 $flatten\hart.\decoder.$procmux$513_CMP0
	p_hart_2e_registers__mem__r__addr_24_1 = (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<31>().concat(p_hart_2e_decoder_2e_insn.slice<29,25>()).concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<13>{0x33u}) ? p_hart_2e_decoder_2e_insn.slice<24,20>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x23u}) ? p_hart_2e_decoder_2e_insn.slice<24,20>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x63u}) ? p_hart_2e_decoder_2e_insn.slice<24,20>().val() : value<5>{0u}))) : value<5>{0u}) : value<5>{0u});
	// \hdlname: hart registers rp2
	// cell \hart.registers.rp2
	auto tmp_0 = memory_index(p_hart_2e_registers__mem__r__addr_24_1, 0, 32);
	CXXRTL_ASSERT(tmp_0.valid && "out of bounds read");
	if(tmp_0.valid) {
		value<32> tmp_1 = memory_p_hart_2e_registers_2e_mem[tmp_0.index];
		p_hart_2e_registers_2e_mem__r__data_24_2 = tmp_1;
	} else {
		p_hart_2e_registers_2e_mem__r__data_24_2 = value<32> {};
	}
	// connection
	p_hart_2e_registers__mem__r__data_24_2 = p_hart_2e_registers_2e_mem__r__data_24_2;
	// cells $flatten\hart.$procmux$451 $flatten\hart.$40 $flatten\hart.$procmux$449 $flatten\hart.$48 $flatten\hart.$47 $flatten\hart.\decoder.$procmux$552 $flatten\hart.\decoder.$procmux$553_CMP0 $flatten\hart.\decoder.$procmux$554_CMP0 $flatten\hart.\decoder.$procmux$555_CMP0 $flatten\hart.\decoder.$procmux$556_CMP0 $flatten\hart.\decoder.$procmux$557_CMP0 $flatten\hart.\decoder.$procmux$558_CMP0 $flatten\hart.\decoder.$procmux$559_CMP0 $flatten\hart.$44 $flatten\hart.$43
	p_hart_2e_alu__op2.next = (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (eq_uu<1>((eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x13u}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x23u}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x3u}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<10>{0x67u}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x6fu}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x17u}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x37u}) ? value<1>{0x1u} : value<1>{0u}))))))), value<1>{0x1u}) ? p_hart_2e_decoder_2e_imm : (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers__mem__r__data_24_2 : value<32>{0u})) : value<32>{0u}) : value<32>{0u});
	// cells $flatten\hart.$procmux$471 $flatten\hart.$22 $flatten\hart.$procmux$469 $flatten\hart.\decoder.$procmux$560 $flatten\hart.\decoder.$procmux$561_CMP0 $flatten\hart.\decoder.$procmux$562_CMP0 $flatten\hart.\decoder.$procmux$563_CMP0 $flatten\hart.\decoder.$procmux$564_CMP0 $flatten\hart.\decoder.$procmux$565_CMP0 $flatten\hart.\decoder.$procmux$566_CMP0
	p_hart_2e_registers__mem__r__addr = (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<31>().concat(p_hart_2e_decoder_2e_insn.slice<29,25>()).concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<13>{0x33u}) ? p_hart_2e_decoder_2e_insn.slice<19,15>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x13u}) ? p_hart_2e_decoder_2e_insn.slice<19,15>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x23u}) ? p_hart_2e_decoder_2e_insn.slice<19,15>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x3u}) ? p_hart_2e_decoder_2e_insn.slice<19,15>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x63u}) ? p_hart_2e_decoder_2e_insn.slice<19,15>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<10>{0x67u}) ? p_hart_2e_decoder_2e_insn.slice<19,15>().val() : value<5>{0u})))))) : value<5>{0u}) : value<5>{0u});
	// \hdlname: hart registers rp1
	// cell \hart.registers.rp1
	auto tmp_2 = memory_index(p_hart_2e_registers__mem__r__addr, 0, 32);
	CXXRTL_ASSERT(tmp_2.valid && "out of bounds read");
	if(tmp_2.valid) {
		value<32> tmp_3 = memory_p_hart_2e_registers_2e_mem[tmp_2.index];
		p_hart_2e_registers_2e_mem__r__data = tmp_3;
	} else {
		p_hart_2e_registers_2e_mem__r__data = value<32> {};
	}
	// cells $flatten\hart.$procmux$455 $flatten\hart.$30 $flatten\hart.$procmux$453 $flatten\hart.$38 $flatten\hart.$37 $flatten\hart.\decoder.$procmux$522 $flatten\hart.\decoder.$procmux$523_CMP0 $flatten\hart.\decoder.$procmux$524_CMP0 $flatten\hart.$34 $flatten\hart.$33
	p_hart_2e_alu__op1.next = (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (eq_uu<1>((eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x6fu}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x17u}) ? value<1>{0x1u} : value<1>{0u})), value<1>{0x1u}) ? p_hart_2e_pc.curr : (reduce_or<1>(p_hart_2e_registers__mem__r__addr) ? p_hart_2e_registers_2e_mem__r__data : value<32>{0u})) : value<32>{0u}) : value<32>{0u});
	// cells $flatten\ram.$procmux$261 $flatten\ram.$26 $flatten\ram.$procmux$259 $flatten\ram.$28
	p_interconnect_2e_ram____rdata = (reduce_or<1>(p_ram_2e_ram____wmask) ? value<32>{0u} : (reduce_or<1>(p_ram_2e_ram____rmask) ? p_rp____data : value<32>{0u}));
	// cells $flatten\hart.$procmux$483 $flatten\hart.$13 $flatten\hart.$procmux$481 $flatten\interconnect.$procmux$162 $flatten\interconnect.$10 $flatten\interconnect.$9 $flatten\interconnect.$7 $flatten\interconnect.$5 $flatten\interconnect.$3 $flatten\interconnect.$procmux$160 $flatten\interconnect.$procmux$161_CMP0
	p_hart_2e_decoder__insn.next = (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask))) ? (eq_uu<1>(p_interconnect_2e_instruction__bus____addr.slice<31>().val(), value<1>{0u}) ? p_interconnect_2e_console____rdata : p_interconnect_2e_ram____rdata) : p_interconnect_2e_cached__ibus____rdata.curr) : value<32>{0u}) : value<32>{0u});
	// cells $flatten\hart.$107 $flatten\hart.$106
	i_flatten_5c_hart_2e__24_103 = (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers__mem__r__data_24_2 : value<32>{0u});
	// cells $flatten\hart.$112 $flatten\hart.$111
	i_flatten_5c_hart_2e__24_108 = (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers__mem__r__data_24_2 : value<32>{0u});
	// cells $flatten\hart.$116 $flatten\hart.$115
	i_flatten_5c_hart_2e__24_113 = (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers__mem__r__data_24_2 : value<32>{0u});
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:119
	// cell $flatten\hart.$72
	i_flatten_5c_hart_2e__24_71 = ne_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xfu});
	// cells $flatten\hart.\decoder.$procmux$516 $flatten\hart.\decoder.$procmux$517_CMP0 $flatten\hart.\decoder.$procmux$518_CMP0 $flatten\hart.\decoder.$procmux$519_CMP0
	p_hart_2e_decoder_2e_branch__cond = (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x63u}) ? p_hart_2e_decoder_2e_insn.slice<14,12>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<10>{0x67u}) ? value<3>{0x2u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x6fu}) ? value<3>{0x2u} : value<3>{0x3u})));
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:72
	// cell $flatten\hart.$70
	i_flatten_5c_hart_2e__24_69 = not_u<1>(p_hart_2e_halt.curr);
	// connection
	p_hart_2e_decoder__branch__cond = p_hart_2e_decoder_2e_branch__cond;
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:221
	// cell $flatten\hart.$procmux$313_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_313__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0x6u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:221
	// cell $flatten\hart.$procmux$313_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_313__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:226
	// cell $flatten\hart.$procmux$312_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_312__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0x7u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:226
	// cell $flatten\hart.$procmux$312_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_312__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0x5u});
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:19
	// cell $flatten\hart.\alu.$2
	p_hart_2e_alu__eq = eq_uu<1>(p_hart_2e_alu_2e_op1, p_hart_2e_alu_2e_op2);
	// cells $flatten\interconnect.$procmux$6 $flatten\interconnect.$232 $flatten\interconnect.$230 $flatten\interconnect.$228 $flatten\interconnect.$226 $flatten\interconnect.$224 $flatten\interconnect.$222 $flatten\interconnect.$221 $flatten\interconnect.$219 $flatten\interconnect.$217 $flatten\interconnect.$215 $flatten\interconnect.$213 $flatten\interconnect.$procmux$4 $flatten\interconnect.$procmux$5_CMP0
	p_hart_2e_dbus____rdy = (or_uu<1>(not_u<1>(and_uu<1>(eq_uu<1>(p_interconnect_2e_data__bus____addr.slice<31>().val(), p_interconnect_2e_instruction__bus____addr.slice<31>().val()), or_uu<1>(reduce_or<1>(p_interconnect_2e_data__bus____wmask), reduce_or<1>(p_interconnect_2e_data__bus____rmask)))), and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask))) ? (eq_uu<1>(p_interconnect_2e_data__bus____addr.slice<31>().val(), value<1>{0u}) ? p_interconnect_2e_console____rdy : p_interconnect_2e_ram____rdy) : value<1>{0u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:221
	// cell $flatten\hart.$procmux$301_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_301__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0x6u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:221
	// cell $flatten\hart.$procmux$301_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_301__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:226
	// cell $flatten\hart.$procmux$300_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_300__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0x7u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:226
	// cell $flatten\hart.$procmux$300_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_300__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0x5u});
	// cells $flatten\hart.\decoder.$procmux$514 $flatten\hart.\decoder.$procmux$515_CMP0 $flatten\hart.\decoder.$33 $flatten\hart.\decoder.$31 $flatten\hart.$procmux$479 $flatten\hart.$15 $flatten\hart.$procmux$477
	p_hart_2e_decoder__branch__target = (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x63u}) ? add_ss<34>((not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? p_hart_2e_pc.curr : value<32>{0u}) : value<32>{0u}), pos_s<32>(p_hart_2e_decoder_2e_insn.slice<31>().concat(p_hart_2e_decoder_2e_insn.slice<7>()).concat(p_hart_2e_decoder_2e_insn.slice<30,25>()).concat(p_hart_2e_decoder_2e_insn.slice<11,8>()).concat(value<1>{0u}).val())).slice<31,0>().val() : value<32>{0u});
	// cells $flatten\interconnect.$procmux$99 $flatten\interconnect.$procmux$97 $flatten\interconnect.$procmux$98_CMP0
	i_flatten_5c_interconnect_2e__24_procmux_24_99__Y = (i_flatten_5c_interconnect_2e__24_85 ? (eq_uu<1>(p_interconnect_2e_instruction__bus____addr.slice<31>().val(), value<1>{0u}) ? p_interconnect_2e_instruction__bus____wmask : value<4>{0u}) : value<4>{0u});
	// cells $flatten\hart.$procmux$421 $flatten\hart.$procmux$419 $flatten\hart.$procmux$417 $flatten\hart.$procmux$406 $flatten\hart.$procmux$407_CMP0 $flatten\hart.$procmux$411_CMP0 $flatten\hart.$procmux$416_CMP0 $flatten\hart.$procmux$409 $flatten\hart.$procmux$410_CMP0 $flatten\hart.$procmux$414 $flatten\hart.$procmux$415_CMP0 $flatten\hart.$87 $flatten\hart.$86
	p_hart_2e_dbus____wdata.slice<15,8>() = (i_flatten_5c_hart_2e__24_69 ? (p_hart_2e_ibus____rdy ? (i_flatten_5c_hart_2e__24_71 ? (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xau}) ? i_flatten_5c_hart_2e__24_113.slice<15,8>().val() : (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x9u}) ? (eq_uu<1>(p_hart_2e_alu__out.slice<1>().val(), value<1>{0u}) ? i_flatten_5c_hart_2e__24_103.slice<15,8>().val() : value<8>{0u}) : (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x8u}) ? (eq_uu<1>(p_hart_2e_alu__out.slice<1,0>().val(), value<2>{0x1u}) ? (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers__mem__r__data_24_2 : value<32>{0u}).slice<7,0>().val() : value<8>{0u}) : value<8>{0u}))) : value<8>{0u}) : value<8>{0u}) : value<8>{0u});
	// cells $flatten\hart.$procmux$404 $flatten\hart.$procmux$402 $flatten\hart.$procmux$400 $flatten\hart.$procmux$389 $flatten\hart.$procmux$390_CMP0 $flatten\hart.$procmux$395_CMP0 $flatten\hart.$procmux$399_CMP0 $flatten\hart.$procmux$393 $flatten\hart.$procmux$394_CMP0 $flatten\hart.$procmux$397 $flatten\hart.$procmux$398_CMP0 $flatten\hart.$92 $flatten\hart.$91
	p_hart_2e_dbus____wdata.slice<23,16>() = (i_flatten_5c_hart_2e__24_69 ? (p_hart_2e_ibus____rdy ? (i_flatten_5c_hart_2e__24_71 ? (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xau}) ? i_flatten_5c_hart_2e__24_113.slice<23,16>().val() : (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x9u}) ? (eq_uu<1>(p_hart_2e_alu__out.slice<1>().val(), value<1>{0u}) ? value<8>{0u} : i_flatten_5c_hart_2e__24_108.slice<7,0>().val()) : (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x8u}) ? (eq_uu<1>(p_hart_2e_alu__out.slice<1,0>().val(), value<2>{0x2u}) ? (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers__mem__r__data_24_2 : value<32>{0u}).slice<7,0>().val() : value<8>{0u}) : value<8>{0u}))) : value<8>{0u}) : value<8>{0u}) : value<8>{0u});
	// cells $flatten\hart.$procmux$387 $flatten\hart.$procmux$385 $flatten\hart.$procmux$383 $flatten\hart.$procmux$371 $flatten\hart.$procmux$372_CMP0 $flatten\hart.$procmux$376_CMP0 $flatten\hart.$procmux$382_CMP0 $flatten\hart.$procmux$374 $flatten\hart.$procmux$375_CMP0 $flatten\hart.$procmux$380 $flatten\hart.$procmux$381_CMP0 $flatten\hart.$82 $flatten\hart.$81
	p_hart_2e_dbus____wdata.slice<7,0>() = (i_flatten_5c_hart_2e__24_69 ? (p_hart_2e_ibus____rdy ? (i_flatten_5c_hart_2e__24_71 ? (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xau}) ? i_flatten_5c_hart_2e__24_113.slice<7,0>().val() : (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x9u}) ? (eq_uu<1>(p_hart_2e_alu__out.slice<1>().val(), value<1>{0u}) ? i_flatten_5c_hart_2e__24_103.slice<7,0>().val() : value<8>{0u}) : (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x8u}) ? (eq_uu<1>(p_hart_2e_alu__out.slice<1,0>().val(), value<2>{0u}) ? (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers__mem__r__data_24_2 : value<32>{0u}).slice<7,0>().val() : value<8>{0u}) : value<8>{0u}))) : value<8>{0u}) : value<8>{0u}) : value<8>{0u});
	// cells $flatten\hart.$procmux$369 $flatten\hart.$procmux$367 $flatten\hart.$procmux$365 $flatten\hart.$procmux$351 $flatten\hart.$procmux$352_CMP0 $flatten\hart.$procmux$357_CMP0 $flatten\hart.$procmux$364_CMP0 $flatten\hart.$procmux$355 $flatten\hart.$procmux$356_CMP0 $flatten\hart.$procmux$360 $flatten\hart.$procmux$361_CMP0 $flatten\hart.$procmux$362_CMP0 $flatten\hart.$procmux$363_CMP0 $flatten\hart.$97 $flatten\hart.$96
	p_hart_2e_dbus____wdata.slice<31,24>() = (i_flatten_5c_hart_2e__24_69 ? (p_hart_2e_ibus____rdy ? (i_flatten_5c_hart_2e__24_71 ? (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xau}) ? i_flatten_5c_hart_2e__24_113.slice<31,24>().val() : (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x9u}) ? (eq_uu<1>(p_hart_2e_alu__out.slice<1>().val(), value<1>{0u}) ? value<8>{0u} : i_flatten_5c_hart_2e__24_108.slice<15,8>().val()) : (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x8u}) ? (eq_uu<1>(p_hart_2e_alu__out.slice<1,0>().val(), value<2>{0x2u}) ? value<8>{0u} : (eq_uu<1>(p_hart_2e_alu__out.slice<1,0>().val(), value<2>{0x1u}) ? value<8>{0u} : (eq_uu<1>(p_hart_2e_alu__out.slice<1,0>().val(), value<2>{0u}) ? value<8>{0u} : (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers__mem__r__data_24_2 : value<32>{0u}).slice<7,0>().val()))) : value<8>{0u}))) : value<8>{0u}) : value<8>{0u}) : value<8>{0u});
	// cells $flatten\interconnect.$procmux$12 $flatten\interconnect.$210 $flatten\interconnect.$208 $flatten\interconnect.$206 $flatten\interconnect.$204 $flatten\interconnect.$202 $flatten\interconnect.$200 $flatten\interconnect.$199 $flatten\interconnect.$197 $flatten\interconnect.$195 $flatten\interconnect.$193 $flatten\interconnect.$191 $flatten\interconnect.$procmux$10 $flatten\interconnect.$procmux$11_CMP0
	p_hart_2e_dbus____rdata = (or_uu<1>(not_u<1>(and_uu<1>(eq_uu<1>(p_interconnect_2e_data__bus____addr.slice<31>().val(), p_interconnect_2e_instruction__bus____addr.slice<31>().val()), or_uu<1>(reduce_or<1>(p_interconnect_2e_data__bus____wmask), reduce_or<1>(p_interconnect_2e_data__bus____rmask)))), and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask))) ? (eq_uu<1>(p_interconnect_2e_data__bus____addr.slice<31>().val(), value<1>{0u}) ? p_interconnect_2e_console____rdata : p_interconnect_2e_ram____rdata) : value<32>{0u});
	// cells $flatten\interconnect.$procmux$150 $flatten\interconnect.$20 $flatten\interconnect.$19 $flatten\interconnect.$17 $flatten\interconnect.$15 $flatten\interconnect.$13 $flatten\interconnect.$procmux$148 $flatten\interconnect.$procmux$149_CMP0
	i_flatten_5c_interconnect_2e__24_procmux_24_150__Y = (not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask))) ? (eq_uu<1>(p_interconnect_2e_instruction__bus____addr.slice<31>().val(), value<1>{0u}) ? p_ibus____wdata : value<32>{0u}) : value<32>{0u});
	// cells $flatten\hart.\decoder.$procmux$567 $flatten\hart.\decoder.$procmux$568_CMP0 $flatten\hart.\decoder.$procmux$569_CMP0 $flatten\hart.\decoder.$procmux$570_CMP0 $flatten\hart.\decoder.$procmux$571_CMP0 $flatten\hart.\decoder.$procmux$572_CMP0 $flatten\hart.\decoder.$procmux$573_CMP0 $flatten\hart.\decoder.$procmux$574_CMP0 $flatten\hart.\decoder.$procmux$575_CMP0 $flatten\hart.\decoder.$procmux$576_CMP0
	p_hart_2e_decoder__rd__addr = (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<31>().concat(p_hart_2e_decoder_2e_insn.slice<29,25>()).concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<13>{0x33u}) ? p_hart_2e_decoder_2e_insn.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x13u}) ? p_hart_2e_decoder_2e_insn.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x3u}) ? p_hart_2e_decoder_2e_insn.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<10>{0x67u}) ? p_hart_2e_decoder_2e_insn.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x6fu}) ? p_hart_2e_decoder_2e_insn.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x17u}) ? p_hart_2e_decoder_2e_insn.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x37u}) ? p_hart_2e_decoder_2e_insn.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<31,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<27>{0x6010173u}) ? p_hart_2e_decoder_2e_insn.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<31,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<27>{0x6000173u}) ? p_hart_2e_decoder_2e_insn.slice<11,7>().val() : value<5>{0u})))))))));
	// cells $flatten\hart.\decoder.$procmux$577 $flatten\hart.\decoder.$procmux$578_CMP0 $flatten\hart.\decoder.$procmux$579_CMP0 $flatten\hart.\decoder.$procmux$580_CMP0 $flatten\hart.\decoder.$procmux$581_CMP0 $flatten\hart.\decoder.$procmux$582_CMP0 $flatten\hart.\decoder.$procmux$583_CMP0 $flatten\hart.\decoder.$procmux$584_CMP0 $flatten\hart.\decoder.$procmux$585_CMP0
	p_hart_2e_decoder__reg__src = (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<31>().concat(p_hart_2e_decoder_2e_insn.slice<29,25>()).concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<13>{0x33u}) ? value<3>{0x2u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x13u}) ? value<3>{0x2u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<10>{0x67u}) ? value<3>{0x3u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x6fu}) ? value<3>{0x3u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x17u}) ? value<3>{0x2u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x37u}) ? value<3>{0x2u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<31,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<27>{0x6010173u}) ? value<3>{0x5u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<31,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<27>{0x6000173u}) ? value<3>{0x4u} : value<3>{0u}))))))));
	// cells $flatten\hart.$procmux$475 $flatten\hart.$17 $flatten\hart.$procmux$473 $flatten\hart.$20
	p_hart_2e_pc__incr = (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? add_uu<33>(p_hart_2e_pc.curr, value<3>{0x4u}).slice<31,0>().val() : value<32>{0x80000000u}) : value<32>{0x80000000u});
	// cells $flatten\interconnect.$procmux$104 $flatten\interconnect.$procmux$102 $flatten\interconnect.$procmux$103_CMP0
	p_console_2e_console____wmask = (i_flatten_5c_interconnect_2e__24_115 ? (eq_uu<1>(p_interconnect_2e_data__bus____addr.slice<31>().val(), value<1>{0u}) ? p_interconnect_2e_data__bus____wmask : i_flatten_5c_interconnect_2e__24_procmux_24_99__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_99__Y);
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:165|/home/slan/src/hartysoc/hdl/riscv/hart.py:166
	// cell $flatten\hart.$procmux$341_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_341__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:165|/home/slan/src/hartysoc/hdl/riscv/hart.py:166
	// cell $flatten\hart.$procmux$341_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_341__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:165|/home/slan/src/hartysoc/hdl/riscv/hart.py:176
	// cell $flatten\hart.$procmux$340_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_340__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x5u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:165|/home/slan/src/hartysoc/hdl/riscv/hart.py:176
	// cell $flatten\hart.$procmux$340_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_340__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x1u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:208|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$622_CMP0
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x1u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:208|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$622_CMP1
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x2u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:208|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$622_CMP2
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP.slice<2>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x3u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:208|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$622_CMP3
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP.slice<3>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:208|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$622_CMP4
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP.slice<4>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x6u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:208|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$622_CMP5
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP.slice<5>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x7u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:149|/home/slan/src/hartysoc/hdl/riscv/decoder.py:148
	// cell $flatten\hart.\decoder.$procmux$633_CMP0
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_633__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:149|/home/slan/src/hartysoc/hdl/riscv/decoder.py:148
	// cell $flatten\hart.\decoder.$procmux$633_CMP1
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_633__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x1u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:149|/home/slan/src/hartysoc/hdl/riscv/decoder.py:148
	// cell $flatten\hart.\decoder.$procmux$633_CMP2
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_633__CMP.slice<2>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x2u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:134|/home/slan/src/hartysoc/hdl/riscv/decoder.py:133
	// cell $flatten\hart.\decoder.$procmux$637_CMP0
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:134|/home/slan/src/hartysoc/hdl/riscv/decoder.py:133
	// cell $flatten\hart.\decoder.$procmux$637_CMP1
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x1u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:134|/home/slan/src/hartysoc/hdl/riscv/decoder.py:133
	// cell $flatten\hart.\decoder.$procmux$637_CMP2
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP.slice<2>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x2u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:134|/home/slan/src/hartysoc/hdl/riscv/decoder.py:133
	// cell $flatten\hart.\decoder.$procmux$637_CMP3
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP.slice<3>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:134|/home/slan/src/hartysoc/hdl/riscv/decoder.py:133
	// cell $flatten\hart.\decoder.$procmux$637_CMP4
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP.slice<4>() = eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x5u});
	// connection
	p_console_2e_uart_2e_rx__ack = p_rx__ack;
	// connection
	p_console_2e_uart_2e_rx__i = p_rx__i;
	// connection
	p_pll__hart__rst = p_pll_2e_rs__hart_2e_stage1.curr;
	// cells $flatten\console.$procmux$166 $flatten\console.$10
	p_console_2e_uart_2e_tx__rdy = (reduce_or<1>(p_console_2e_console____wmask) ? value<1>{0x1u} : value<1>{0u});
	// connection
	p_pll_2e_rst = p_rst;
	// cells $flatten\hart.$procmux$330 $flatten\hart.$162 $flatten\hart.$procmux$328 $flatten\hart.$procmux$326 $flatten\hart.$166 $flatten\hart.$164 $flatten\hart.$procmux$324 $flatten\hart.$168
	p_hart_2e_registers_2e_mem__w__addr = (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xfu}), p_hart_2e_dbus____rdy) ? (eq_uu<1>(p_hart_2e_decoder__rd__addr, value<1>{0u}) ? value<5>{0u} : p_hart_2e_decoder__rd__addr) : value<5>{0u}) : value<5>{0u}) : value<5>{0u});
	// connection
	p_hart_2e_hart__rst = p_pll__hart__rst;
	// connection
	p_console_2e_uart_2e_hart__rst = p_pll__hart__rst;
	// connection
	p_interconnect_2e_hart__rst = p_pll__hart__rst;
	// connection
	p_hart_2e_hart__clk = p_hart__clk;
	// cells $flatten\pll.\rs_hart.$4 $flatten\pll.\rs_hart.$2
	p_pll_2e_rs__hart_2e_async__ff__rst = or_uu<1>(not_u<1>(p_pll_2e_rs__hart__locked.curr), p_pll_2e_rst);
	// connection
	p_pll_2e_rs__hart_2e_async__ff__clk = p_hart__clk;
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:25
	// cell $flatten\hart.\registers.$5
	p_hart_2e_registers_2e_mem__w__en = reduce_or<1>(p_hart_2e_registers_2e_mem__w__addr);
	// connection
	p_console_2e_uart_2e_hart__clk = p_hart__clk;
	// connection
	p_interconnect_2e_hart__clk = p_hart__clk;
	// cell $flatten\pll.\rs_hart.$procdff$676
	if (posedge_p_hart__clk) {
		p_pll_2e_rs__hart_2e_stage1.next = p_pll_2e_rs__hart_2e_stage0.curr;
	}
	if (p_pll_2e_rs__hart_2e_async__ff__rst == value<1> {1u}) {
		p_pll_2e_rs__hart_2e_stage1.next = value<1>{0x1u};
	}
	// cell $flatten\pll.\rs_hart.$procdff$677
	if (posedge_p_hart__clk) {
		p_pll_2e_rs__hart_2e_stage0.next = value<1>{0u};
	}
	if (p_pll_2e_rs__hart_2e_async__ff__rst == value<1> {1u}) {
		p_pll_2e_rs__hart_2e_stage0.next = value<1>{0x1u};
	}
	// cells $flatten\pll.$procdff$675 $flatten\pll.$procmux$657
	if (posedge_p_clk) {
		p_pll_2e_rs__hart__locked.next = (p_pll_2e_rst ? value<1>{0u} : value<1>{0x1u});
	}
	// cells \hart.registers.wp $flatten\hart.$procmux$349 $flatten\hart.$118 $flatten\hart.$procmux$347 $flatten\hart.$procmux$345 $flatten\hart.$122 $flatten\hart.$120 $flatten\hart.$procmux$343 $flatten\hart.$124 $flatten\hart.$procmux$338 $flatten\hart.$procmux$339_CMP0 $flatten\hart.$procmux$340_ANY $flatten\hart.$procmux$341_ANY $flatten\hart.$160 $flatten\hart.$159 $flatten\hart.$158 $flatten\hart.$149 $flatten\hart.$148 $flatten\hart.$147 $flatten\hart.$155 $flatten\hart.$154 $flatten\hart.$153 $flatten\hart.$142 $flatten\hart.$141 $flatten\hart.$140 $flatten\hart.$131 $flatten\hart.$130 $flatten\hart.$129 $flatten\hart.$137 $flatten\hart.$136 $flatten\hart.$135 $flatten\hart.$procmux$332 $flatten\hart.$procmux$333_CMP0 $flatten\hart.$procmux$334_CMP0 $flatten\hart.$procmux$335_CMP0 $flatten\hart.$procmux$336_CMP0
	if (posedge_p_hart__clk) {
		auto tmp_4 = memory_index(p_hart_2e_registers_2e_mem__w__addr, 0, 32);
		CXXRTL_ASSERT(tmp_4.valid && "out of bounds write");
		if (tmp_4.valid) {
			memory_p_hart_2e_registers_2e_mem.update(tmp_4.index, (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xfu}), p_hart_2e_dbus____rdy) ? (eq_uu<1>(p_hart_2e_decoder__rd__addr, value<1>{0u}) ? value<32>{0u} : (eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x2u}) ? p_hart_2e_dbus____rdata : (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_340__CMP) ? pos_s<32>((eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x5u}) ? pos_u<17>(shift_uu<16>(p_hart_2e_dbus____rdata, mul_uu<6>(p_hart_2e_alu__out.slice<1>().val(), value<5>{0x10u}))) : pos_s<17>(shift_uu<16>(p_hart_2e_dbus____rdata, mul_uu<6>(p_hart_2e_alu__out.slice<1>().val(), value<5>{0x10u}))))) : (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_341__CMP) ? pos_s<32>((eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0x4u}) ? pos_u<9>(shift_uu<8>(p_hart_2e_dbus____rdata, mul_uu<6>(p_hart_2e_alu__out.slice<1,0>().val(), value<4>{0x8u}))) : pos_s<9>(shift_uu<8>(p_hart_2e_dbus____rdata, mul_uu<6>(p_hart_2e_alu__out.slice<1,0>().val(), value<4>{0x8u}))))) : (eq_uu<1>(p_hart_2e_decoder__reg__src, value<3>{0x5u}) ? p_hart_2e_minstret.curr.slice<31,0>().val() : (eq_uu<1>(p_hart_2e_decoder__reg__src, value<3>{0x4u}) ? p_hart_2e_mcycle.curr.slice<31,0>().val() : (eq_uu<1>(p_hart_2e_decoder__reg__src, value<3>{0x3u}) ? p_hart_2e_pc__incr : (eq_uu<1>(p_hart_2e_decoder__reg__src, value<3>{0x2u}) ? p_hart_2e_alu__out : value<32>{0u})))))))) : value<32>{0u}) : value<32>{0u}) : value<32>{0u}), p_hart_2e_registers_2e_mem__w__en.repeat<32>().val(), 0);
		}
	}
	// cells $flatten\hart.$procdff$674 $flatten\hart.$procmux$495 $flatten\hart.$procmux$493 $flatten\hart.\decoder.$procmux$623 $flatten\hart.\decoder.$procmux$624_CMP0 $flatten\hart.\decoder.$procmux$630_CMP0 $flatten\hart.\decoder.$procmux$634_CMP0 $flatten\hart.\decoder.$procmux$638_CMP0 $flatten\hart.\decoder.$procmux$641_CMP0 $flatten\hart.\decoder.$procmux$642_CMP0 $flatten\hart.\decoder.$procmux$643_CMP0 $flatten\hart.\decoder.$procmux$644_CMP0 $flatten\hart.\decoder.$procmux$645_CMP0 $flatten\hart.\decoder.$procmux$646_CMP0 $flatten\hart.\decoder.$procmux$647_CMP0 $flatten\hart.\decoder.$procmux$621 $flatten\hart.\decoder.$procmux$622_ANY $flatten\hart.\decoder.$procmux$619 $flatten\hart.\decoder.$procmux$628 $flatten\hart.\decoder.$procmux$629_CMP0 $flatten\hart.\decoder.$procmux$626 $flatten\hart.\decoder.$procmux$632 $flatten\hart.\decoder.$procmux$633_ANY $flatten\hart.\decoder.$procmux$636 $flatten\hart.\decoder.$procmux$637_ANY $flatten\hart.\decoder.$procmux$639 $flatten\hart.\decoder.$6 $flatten\hart.\decoder.$4 $flatten\hart.\decoder.$2
	if (posedge_p_hart__clk) {
		p_hart_2e_halt.next = (p_hart_2e_hart__rst ? value<1>{0u} : ((eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<31>().concat(p_hart_2e_decoder_2e_insn.slice<29,25>()).concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<13>{0x33u}) ? (reduce_or<1>(i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP) ? (p_hart_2e_decoder_2e_insn.slice<30>().val() ? value<1>{0x1u} : value<1>{0u}) : value<1>{0u}) : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x13u}) ? (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().val(), value<3>{0x1u}) ? (p_hart_2e_decoder_2e_insn.slice<30>().val() ? value<1>{0x1u} : value<1>{0u}) : value<1>{0u}) : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x23u}) ? (reduce_or<1>(i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_633__CMP) ? value<1>{0u} : value<1>{0x1u}) : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x3u}) ? (reduce_or<1>(i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP) ? value<1>{0u} : value<1>{0x1u}) : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x63u}) ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x2u}), eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x3u})) ? value<1>{0x1u} : value<1>{0u}) : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<14,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<10>{0x67u}) ? value<1>{0u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x6fu}) ? value<1>{0u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x17u}) ? value<1>{0u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<6,0>().val(), value<7>{0x37u}) ? value<1>{0u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<31,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<27>{0x6010173u}) ? value<1>{0u} : (eq_uu<1>(p_hart_2e_decoder_2e_insn.slice<31,12>().concat(p_hart_2e_decoder_2e_insn.slice<6,0>()).val(), value<27>{0x6000173u}) ? value<1>{0u} : value<1>{0x1u}))))))))))) ? value<1>{0x1u} : p_hart_2e_halt.curr));
	}
	// cells $flatten\hart.$procdff$673 $flatten\hart.$procmux$491 $flatten\hart.$procmux$489 $flatten\hart.$4 $flatten\hart.$7
	if (posedge_p_hart__clk) {
		p_hart_2e_mcycle.next = (p_hart_2e_hart__rst ? value<64>{0u,0u} : (not_u<1>(p_hart_2e_halt.curr) ? add_uu<65>(p_hart_2e_mcycle.curr, value<1>{0x1u}).slice<63,0>().val() : p_hart_2e_mcycle.curr));
	}
	// cells $flatten\hart.$procdff$672 $flatten\hart.$procmux$291 $flatten\hart.$procmux$289 $flatten\hart.$198 $flatten\hart.$procmux$287 $flatten\hart.$procmux$285 $flatten\hart.$202 $flatten\hart.$200 $flatten\hart.$procmux$297 $flatten\hart.$190 $flatten\hart.$procmux$295 $flatten\hart.$procmux$293 $flatten\hart.$194 $flatten\hart.$192 $flatten\hart.$196 $flatten\hart.$procmux$321 $flatten\hart.$170 $flatten\hart.$procmux$319 $flatten\hart.$procmux$317 $flatten\hart.$174 $flatten\hart.$172 $flatten\hart.$procmux$311 $flatten\hart.$procmux$312_ANY $flatten\hart.$procmux$313_ANY $flatten\hart.$procmux$314_CMP0 $flatten\hart.$procmux$315_CMP0 $flatten\hart.$procmux$316_CMP0 $flatten\hart.$182 $flatten\hart.$181 $flatten\hart.$178 $flatten\hart.$176 $flatten\hart.$procmux$309 $flatten\hart.$184 $flatten\hart.$procmux$307 $flatten\hart.$procmux$305 $flatten\hart.$188 $flatten\hart.$186 $flatten\hart.$procmux$299 $flatten\hart.$procmux$300_ANY $flatten\hart.$procmux$301_ANY $flatten\hart.$procmux$302_CMP0 $flatten\hart.$procmux$303_CMP0 $flatten\hart.$procmux$304_CMP0
	if (posedge_p_hart__clk) {
		p_hart_2e_pc.next = (p_hart_2e_hart__rst ? value<32>{0x80000000u} : (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xfu}), p_hart_2e_dbus____rdy) ? (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xfu}), p_hart_2e_dbus____rdy) ? ((not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xfu}), p_hart_2e_dbus____rdy) ? (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_312__CMP) ? not_u<1>(reduce_or<1>(p_hart_2e_alu__out)) : (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_313__CMP) ? reduce_or<1>(p_hart_2e_alu__out) : (eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0x1u}) ? not_u<1>(p_hart_2e_alu__eq) : (eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0u}) ? p_hart_2e_alu__eq : (eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0x2u}) ? value<1>{0x1u} : value<1>{0u}))))) : value<1>{0u}) : value<1>{0u}) : value<1>{0u}) ? (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xfu}), p_hart_2e_dbus____rdy) ? (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_300__CMP) ? p_hart_2e_decoder__branch__target : (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_301__CMP) ? p_hart_2e_decoder__branch__target : (eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0x1u}) ? p_hart_2e_decoder__branch__target : (eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0u}) ? p_hart_2e_decoder__branch__target : (eq_uu<1>(p_hart_2e_decoder__branch__cond, value<3>{0x2u}) ? p_hart_2e_alu__out : value<32>{0x80000000u}))))) : value<32>{0x80000000u}) : value<32>{0x80000000u}) : value<32>{0x80000000u}) : p_hart_2e_pc__incr) : value<32>{0x80000000u}) : value<32>{0x80000000u}) : value<32>{0x80000000u}) : p_hart_2e_pc.curr) : p_hart_2e_pc.curr) : p_hart_2e_pc.curr));
	}
	// cells $flatten\hart.$procdff$671 $flatten\hart.$procmux$283 $flatten\hart.$procmux$281 $flatten\hart.$204 $flatten\hart.$procmux$279 $flatten\hart.$procmux$277 $flatten\hart.$208 $flatten\hart.$206 $flatten\hart.$211
	if (posedge_p_hart__clk) {
		p_hart_2e_minstret.next = (p_hart_2e_hart__rst ? value<64>{0u,0u} : (not_u<1>(p_hart_2e_halt.curr) ? (p_hart_2e_ibus____rdy ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder__mem__func, value<4>{0xfu}), p_hart_2e_dbus____rdy) ? add_uu<65>(p_hart_2e_minstret.curr, value<1>{0x1u}).slice<63,0>().val() : p_hart_2e_minstret.curr) : p_hart_2e_minstret.curr) : p_hart_2e_minstret.curr));
	}
	// cells $flatten\console.\uart.$procdff$663 $flatten\console.\uart.$procmux$176 $flatten\console.\uart.$procmux$174 $flatten\console.\uart.$76 $flatten\console.\uart.$procmux$171 $flatten\console.\uart.$78
	if (posedge_p_hart__clk) {
		p_console_2e_uart_2e_rx__shreg.next = (p_console_2e_uart_2e_hart__rst ? value<10>{0x3ffu} : (eq_uu<1>(p_console_2e_uart_2e_rx__count.curr, value<1>{0u}) ? p_console_2e_uart_2e_rx__shreg.curr : (ne_uu<1>(p_console_2e_uart_2e_rx__phase.curr, value<1>{0u}) ? p_console_2e_uart_2e_rx__shreg.curr : p_console_2e_uart_2e_rx__i.concat(p_console_2e_uart_2e_rx__shreg.curr.slice<9,1>()).val())));
	}
	// cells $flatten\console.\uart.$procdff$664 $flatten\console.\uart.$procmux$188 $flatten\console.\uart.$procmux$186 $flatten\console.\uart.$63 $flatten\console.\uart.$procmux$184 $flatten\console.\uart.$65 $flatten\console.\uart.$procmux$182 $flatten\console.\uart.$69 $flatten\console.\uart.$67 $flatten\console.\uart.$procmux$179 $flatten\console.\uart.$71 $flatten\console.\uart.$74
	if (posedge_p_hart__clk) {
		p_console_2e_uart_2e_rx__phase.next = (p_console_2e_uart_2e_hart__rst ? value<6>{0u} : (eq_uu<1>(p_console_2e_uart_2e_rx__count.curr, value<1>{0u}) ? (not_u<1>(p_console_2e_uart_2e_rx__i) ? (or_uu<1>(p_console_2e_uart_2e_rx__ack, not_u<1>(p_console_2e_uart_2e_rx__rdy.curr)) ? value<6>{0x1bu} : p_console_2e_uart_2e_rx__phase.curr) : p_console_2e_uart_2e_rx__phase.curr) : (ne_uu<1>(p_console_2e_uart_2e_rx__phase.curr, value<1>{0u}) ? sub_uu<7>(p_console_2e_uart_2e_rx__phase.curr, value<1>{0x1u}).slice<5,0>().val() : value<6>{0x35u})));
	}
	// cells $flatten\console.\uart.$procdff$665 $flatten\console.\uart.$procmux$200 $flatten\console.\uart.$procmux$198 $flatten\console.\uart.$50 $flatten\console.\uart.$procmux$196 $flatten\console.\uart.$52 $flatten\console.\uart.$procmux$194 $flatten\console.\uart.$56 $flatten\console.\uart.$54 $flatten\console.\uart.$procmux$191 $flatten\console.\uart.$58 $flatten\console.\uart.$61
	if (posedge_p_hart__clk) {
		p_console_2e_uart_2e_rx__count.next = (p_console_2e_uart_2e_hart__rst ? value<4>{0u} : (eq_uu<1>(p_console_2e_uart_2e_rx__count.curr, value<1>{0u}) ? (not_u<1>(p_console_2e_uart_2e_rx__i) ? (or_uu<1>(p_console_2e_uart_2e_rx__ack, not_u<1>(p_console_2e_uart_2e_rx__rdy.curr)) ? value<4>{0xau} : p_console_2e_uart_2e_rx__count.curr) : p_console_2e_uart_2e_rx__count.curr) : (ne_uu<1>(p_console_2e_uart_2e_rx__phase.curr, value<1>{0u}) ? p_console_2e_uart_2e_rx__count.curr : sub_uu<5>(p_console_2e_uart_2e_rx__count.curr, value<1>{0x1u}).slice<3,0>().val())));
	}
	// cells $flatten\console.\uart.$procdff$666 $flatten\console.\uart.$procmux$209 $flatten\console.\uart.$procmux$207 $flatten\console.\uart.$42 $flatten\console.\uart.$procmux$205 $flatten\console.\uart.$44 $flatten\console.\uart.$procmux$203 $flatten\console.\uart.$48 $flatten\console.\uart.$46
	if (posedge_p_hart__clk) {
		p_console_2e_uart_2e_rx__ovf.next = (p_console_2e_uart_2e_hart__rst ? value<1>{0u} : (eq_uu<1>(p_console_2e_uart_2e_rx__count.curr, value<1>{0u}) ? (not_u<1>(p_console_2e_uart_2e_rx__i) ? (or_uu<1>(p_console_2e_uart_2e_rx__ack, not_u<1>(p_console_2e_uart_2e_rx__rdy.curr)) ? value<1>{0u} : value<1>{0x1u}) : p_console_2e_uart_2e_rx__ovf.curr) : p_console_2e_uart_2e_rx__ovf.curr));
	}
	// cells $flatten\console.\uart.$procdff$667 $flatten\console.\uart.$procmux$223 $flatten\console.\uart.$procmux$221 $flatten\console.\uart.$30 $flatten\console.\uart.$procmux$219 $flatten\console.\uart.$32 $flatten\console.\uart.$procmux$217 $flatten\console.\uart.$36 $flatten\console.\uart.$34 $flatten\console.\uart.$procmux$214 $flatten\console.\uart.$38 $flatten\console.\uart.$procmux$211 $flatten\console.\uart.$40
	if (posedge_p_hart__clk) {
		p_console_2e_uart_2e_rx__rdy.next = (p_console_2e_uart_2e_hart__rst ? value<1>{0u} : (eq_uu<1>(p_console_2e_uart_2e_rx__count.curr, value<1>{0u}) ? (not_u<1>(p_console_2e_uart_2e_rx__i) ? (or_uu<1>(p_console_2e_uart_2e_rx__ack, not_u<1>(p_console_2e_uart_2e_rx__rdy.curr)) ? value<1>{0u} : p_console_2e_uart_2e_rx__rdy.curr) : p_console_2e_uart_2e_rx__rdy.curr) : (ne_uu<1>(p_console_2e_uart_2e_rx__phase.curr, value<1>{0u}) ? p_console_2e_uart_2e_rx__rdy.curr : (eq_uu<1>(p_console_2e_uart_2e_rx__count.curr, value<1>{0x1u}) ? value<1>{0x1u} : p_console_2e_uart_2e_rx__rdy.curr))));
	}
	// cells $flatten\console.\uart.$procdff$668 $flatten\console.\uart.$procmux$235 $flatten\console.\uart.$procmux$233 $flatten\console.\uart.$15 $flatten\console.\uart.$procmux$231 $flatten\console.\uart.$procmux$228 $flatten\console.\uart.$17 $flatten\console.\uart.$20
	if (posedge_p_hart__clk) {
		p_console_2e_uart_2e_tx__phase.next = (p_console_2e_uart_2e_hart__rst ? value<6>{0u} : (eq_uu<1>(p_console_2e_uart_2e_tx__count.curr, value<1>{0u}) ? (p_console_2e_uart_2e_tx__rdy ? value<6>{0x35u} : p_console_2e_uart_2e_tx__phase.curr) : (ne_uu<1>(p_console_2e_uart_2e_tx__phase.curr, value<1>{0u}) ? sub_uu<7>(p_console_2e_uart_2e_tx__phase.curr, value<1>{0x1u}).slice<5,0>().val() : value<6>{0x35u})));
	}
	// cells $flatten\console.\uart.$procdff$669 $flatten\console.\uart.$procmux$245 $flatten\console.\uart.$procmux$243 $flatten\console.\uart.$8 $flatten\console.\uart.$procmux$241 $flatten\console.\uart.$procmux$238 $flatten\console.\uart.$10 $flatten\console.\uart.$13
	if (posedge_p_hart__clk) {
		p_console_2e_uart_2e_tx__count.next = (p_console_2e_uart_2e_hart__rst ? value<4>{0u} : (eq_uu<1>(p_console_2e_uart_2e_tx__count.curr, value<1>{0u}) ? (p_console_2e_uart_2e_tx__rdy ? value<4>{0xau} : p_console_2e_uart_2e_tx__count.curr) : (ne_uu<1>(p_console_2e_uart_2e_tx__phase.curr, value<1>{0u}) ? p_console_2e_uart_2e_tx__count.curr : sub_uu<5>(p_console_2e_uart_2e_tx__count.curr, value<1>{0x1u}).slice<3,0>().val())));
	}
	// cells $flatten\console.\uart.$procdff$670 $flatten\console.\uart.$procmux$255 $flatten\console.\uart.$procmux$253 $flatten\console.\uart.$4 $flatten\console.\uart.$procmux$251 $flatten\console.$procmux$164 $flatten\console.$12 $flatten\interconnect.$procmux$155 $flatten\interconnect.$42 $flatten\interconnect.$40 $flatten\interconnect.$38 $flatten\interconnect.$36 $flatten\interconnect.$34 $flatten\interconnect.$32 $flatten\interconnect.$31 $flatten\interconnect.$29 $flatten\interconnect.$27 $flatten\interconnect.$25 $flatten\interconnect.$23 $flatten\interconnect.$procmux$153 $flatten\interconnect.$procmux$154_CMP0 $flatten\console.\uart.$procmux$248 $flatten\console.\uart.$6
	if (posedge_p_hart__clk) {
		p_console_2e_uart_2e_tx__shreg.next = (p_console_2e_uart_2e_hart__rst ? value<10>{0x3ffu} : (eq_uu<1>(p_console_2e_uart_2e_tx__count.curr, value<1>{0u}) ? (p_console_2e_uart_2e_tx__rdy ? value<1>{0x1u}.concat((reduce_or<1>(p_console_2e_console____wmask) ? (or_uu<1>(not_u<1>(and_uu<1>(eq_uu<1>(p_interconnect_2e_data__bus____addr.slice<31>().val(), p_interconnect_2e_instruction__bus____addr.slice<31>().val()), or_uu<1>(reduce_or<1>(p_interconnect_2e_data__bus____wmask), reduce_or<1>(p_interconnect_2e_data__bus____rmask)))), and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask))) ? (eq_uu<1>(p_interconnect_2e_data__bus____addr.slice<31>().val(), value<1>{0u}) ? p_hart_2e_dbus____wdata : i_flatten_5c_interconnect_2e__24_procmux_24_150__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_150__Y).slice<7,0>().val() : value<8>{0u})).concat(value<1>{0u}).val() : p_console_2e_uart_2e_tx__shreg.curr) : (ne_uu<1>(p_console_2e_uart_2e_tx__phase.curr, value<1>{0u}) ? p_console_2e_uart_2e_tx__shreg.curr : value<1>{0x1u}.concat(p_console_2e_uart_2e_tx__shreg.curr.slice<9,1>()).val())));
	}
	// cells $flatten\interconnect.$procdff$662 $flatten\interconnect.$procmux$60 $flatten\interconnect.$procmux$58 $flatten\interconnect.$158 $flatten\interconnect.$157 $flatten\interconnect.$155 $flatten\interconnect.$153 $flatten\interconnect.$151 $flatten\interconnect.$procmux$56 $flatten\interconnect.$procmux$57_CMP0 $flatten\interconnect.$procmux$54 $flatten\interconnect.$procmux$50
	if (posedge_p_hart__clk) {
		p_interconnect_2e_cached__ibus____addr.next = (p_interconnect_2e_hart__rst ? value<32>{0u} : (not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask))) ? (eq_uu<1>(p_interconnect_2e_instruction__bus____addr.slice<31>().val(), value<1>{0u}) ? (p_interconnect_2e_console____rdy ? p_interconnect_2e_instruction__bus____addr : p_interconnect_2e_cached__ibus____addr.curr) : (p_interconnect_2e_ram____rdy ? p_interconnect_2e_instruction__bus____addr : p_interconnect_2e_cached__ibus____addr.curr)) : p_interconnect_2e_cached__ibus____addr.curr));
	}
	// cells $flatten\interconnect.$procdff$661 $flatten\interconnect.$procmux$48 $flatten\interconnect.$procmux$46 $flatten\interconnect.$168 $flatten\interconnect.$167 $flatten\interconnect.$165 $flatten\interconnect.$163 $flatten\interconnect.$161 $flatten\interconnect.$procmux$44 $flatten\interconnect.$procmux$45_CMP0 $flatten\interconnect.$procmux$42 $flatten\interconnect.$procmux$38
	if (posedge_p_hart__clk) {
		p_interconnect_2e_cached__ibus____rdata.next = (p_interconnect_2e_hart__rst ? value<32>{0u} : (not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask))) ? (eq_uu<1>(p_interconnect_2e_instruction__bus____addr.slice<31>().val(), value<1>{0u}) ? (p_interconnect_2e_console____rdy ? p_interconnect_2e_console____rdata : p_interconnect_2e_cached__ibus____rdata.curr) : (p_interconnect_2e_ram____rdy ? p_interconnect_2e_ram____rdata : p_interconnect_2e_cached__ibus____rdata.curr)) : p_interconnect_2e_cached__ibus____rdata.curr));
	}
	// cells $flatten\interconnect.$procdff$660 $flatten\interconnect.$procmux$36 $flatten\interconnect.$procmux$34 $flatten\interconnect.$178 $flatten\interconnect.$177 $flatten\interconnect.$175 $flatten\interconnect.$173 $flatten\interconnect.$171 $flatten\interconnect.$procmux$32 $flatten\interconnect.$procmux$33_CMP0 $flatten\interconnect.$procmux$30 $flatten\interconnect.$procmux$26
	if (posedge_p_hart__clk) {
		p_interconnect_2e_cached__ibus____rmask.next = (p_interconnect_2e_hart__rst ? value<4>{0u} : (not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask))) ? (eq_uu<1>(p_interconnect_2e_instruction__bus____addr.slice<31>().val(), value<1>{0u}) ? (p_interconnect_2e_console____rdy ? p_interconnect_2e_instruction__bus____rmask : p_interconnect_2e_cached__ibus____rmask.curr) : (p_interconnect_2e_ram____rdy ? p_interconnect_2e_instruction__bus____rmask : p_interconnect_2e_cached__ibus____rmask.curr)) : p_interconnect_2e_cached__ibus____rmask.curr));
	}
	// cells $flatten\interconnect.$procdff$659 $flatten\interconnect.$procmux$24 $flatten\interconnect.$procmux$22 $flatten\interconnect.$188 $flatten\interconnect.$187 $flatten\interconnect.$185 $flatten\interconnect.$183 $flatten\interconnect.$181 $flatten\interconnect.$procmux$20 $flatten\interconnect.$procmux$21_CMP0 $flatten\interconnect.$procmux$18 $flatten\interconnect.$procmux$14
	if (posedge_p_hart__clk) {
		p_interconnect_2e_cache__present.next = (p_interconnect_2e_hart__rst ? value<1>{0u} : (not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_interconnect_2e_instruction__bus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_interconnect_2e_instruction__bus____rmask))) ? (eq_uu<1>(p_interconnect_2e_instruction__bus____addr.slice<31>().val(), value<1>{0u}) ? (p_interconnect_2e_console____rdy ? value<1>{0x1u} : p_interconnect_2e_cache__present.curr) : (p_interconnect_2e_ram____rdy ? value<1>{0x1u} : p_interconnect_2e_cache__present.curr)) : p_interconnect_2e_cache__present.curr));
	}
	return converged;
}

bool p_top::commit() {
	bool changed = false;
	if (p_interconnect_2e_cache__present.commit()) changed = true;
	if (p_interconnect_2e_cached__ibus____addr.commit()) changed = true;
	if (p_interconnect_2e_cached__ibus____rmask.commit()) changed = true;
	if (p_interconnect_2e_cached__ibus____rdata.commit()) changed = true;
	if (p_console_2e_uart_2e_rx__ovf.commit()) changed = true;
	if (p_console_2e_uart_2e_rx__phase.commit()) changed = true;
	if (p_console_2e_uart_2e_rx__rdy.commit()) changed = true;
	if (p_console_2e_uart_2e_rx__count.commit()) changed = true;
	if (p_console_2e_uart_2e_rx__shreg.commit()) changed = true;
	if (p_console_2e_uart_2e_tx__phase.commit()) changed = true;
	if (p_console_2e_uart_2e_tx__count.commit()) changed = true;
	if (p_console_2e_uart_2e_tx__shreg.commit()) changed = true;
	if (p_hart_2e_alu__func.commit()) changed = true;
	if (p_hart_2e_alu__op1.commit()) changed = true;
	if (p_hart_2e_alu__op2.commit()) changed = true;
	if (p_hart_2e_decoder__insn.commit()) changed = true;
	if (p_hart_2e_halt.commit()) changed = true;
	if (p_hart_2e_mcycle.commit()) changed = true;
	if (p_hart_2e_pc.commit()) changed = true;
	if (p_hart_2e_minstret.commit()) changed = true;
	if (p_hart_2e_alu_2e_out.commit()) changed = true;
	if (p_pll_2e_rs__hart__locked.commit()) changed = true;
	if (p_pll_2e_rs__hart_2e_stage1.commit()) changed = true;
	if (p_pll_2e_rs__hart_2e_stage0.commit()) changed = true;
	if (p_interconnect__data__bus____wmask.commit()) changed = true;
	if (p_interconnect__data__bus____rmask.commit()) changed = true;
	if (p_interconnect__data__bus____addr.commit()) changed = true;
	prev_p_hart__clk = p_hart__clk;
	prev_p_clk = p_clk;
	if (memory_p_hart_2e_registers_2e_mem.commit()) changed = true;
	return changed;
}

void p_top::debug_eval() {
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:61
	value<1> i_flatten_5c_interconnect_2e__24_85;
	// \src: /home/slan/src/hartysoc/hdl/harty/interconnect_modwizcode.py:100
	value<1> i_flatten_5c_interconnect_2e__24_115;
	value<4> i_flatten_5c_interconnect_2e__24_procmux_24_88__Y;
	value<4> i_flatten_5c_interconnect_2e__24_procmux_24_99__Y;
	value<4> i_flatten_5c_interconnect_2e__24_procmux_24_110__Y;
	value<32> i_flatten_5c_interconnect_2e__24_procmux_24_150__Y;
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:72
	value<1> i_flatten_5c_hart_2e__24_69;
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:119
	value<1> i_flatten_5c_hart_2e__24_71;
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:14
	value<32> i_flatten_5c_hart_2e__24_103;
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:14
	value<32> i_flatten_5c_hart_2e__24_108;
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:14
	value<32> i_flatten_5c_hart_2e__24_113;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_300__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_301__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_312__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_313__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_340__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_341__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_435__CMP;
	value<2> i_flatten_5c_hart_2e__24_procmux_24_436__CMP;
	value<5> i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP;
	value<3> i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_633__CMP;
	value<6> i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP;
	value<6> i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP;
	value<6> i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP;
	value<2> i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_503__CMP;
	// \src: /home/slan/src/nmigen/nmigen/hdl/ast.py:269
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_25;
	// \src: /home/slan/src/nmigen/nmigen/hdl/ast.py:269
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_23;
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:174
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_21;
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:143
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_19;
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:128
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_17;
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:92
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_15;
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:74
	value<32> i_flatten_5c_hart_2e__5c_decoder_2e__24_13;
	// connection
	p_hart_2e_dbus____addr.slice<1,0>() = value<2>{0u};
	// cells $flatten\hart.$procmux$487 $flatten\hart.$9
	p_hart_2e_ibus____rmask = (not_u<1>(p_hart_2e_halt.curr) ? value<4>{0xfu} : value<4>{0u});
	// cells $flatten\hart.$procmux$485 $flatten\hart.$11
	p_hart_2e_ibus____addr = (not_u<1>(p_hart_2e_halt.curr) ? p_hart_2e_pc.curr : value<32>{0u});
	// cells $flatten\interconnect.$94 $flatten\interconnect.$93 $flatten\interconnect.$91 $flatten\interconnect.$89 $flatten\interconnect.$87
	i_flatten_5c_interconnect_2e__24_85 = not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_hart_2e_ibus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_hart_2e_ibus____rmask)));
	// cells $flatten\interconnect.$procmux$88 $flatten\interconnect.$procmux$86 $flatten\interconnect.$procmux$87_CMP0
	i_flatten_5c_interconnect_2e__24_procmux_24_88__Y = (i_flatten_5c_interconnect_2e__24_85 ? (eq_uu<1>(p_hart_2e_ibus____addr.slice<31>().val(), value<1>{0u}) ? value<4>{0u} : p_ibus____wmask) : value<4>{0u});
	// cells $flatten\interconnect.$procmux$110 $flatten\interconnect.$62 $flatten\interconnect.$61 $flatten\interconnect.$59 $flatten\interconnect.$57 $flatten\interconnect.$55 $flatten\interconnect.$procmux$108 $flatten\interconnect.$procmux$109_CMP0
	i_flatten_5c_interconnect_2e__24_procmux_24_110__Y = (not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_hart_2e_ibus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_hart_2e_ibus____rmask))) ? (eq_uu<1>(p_hart_2e_ibus____addr.slice<31>().val(), value<1>{0u}) ? value<4>{0u} : p_hart_2e_ibus____rmask) : value<4>{0u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$544_CMP5
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP.slice<5>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x3u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$544_CMP4
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP.slice<4>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x7u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$544_CMP3
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP.slice<3>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x6u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$544_CMP2
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP.slice<2>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$544_CMP1
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x2u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$544_CMP0
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$532_CMP5
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP.slice<5>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x3u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$532_CMP4
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP.slice<4>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x7u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$532_CMP3
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP.slice<3>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x6u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$532_CMP2
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP.slice<2>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$532_CMP1
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x2u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:164|/home/slan/src/hartysoc/hdl/riscv/decoder.py:163
	// cell $flatten\hart.\decoder.$procmux$532_CMP0
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0u});
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:204|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$503_CMP1
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_503__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x5u});
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:204|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$503_CMP0
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_503__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0u});
	// \src: /home/slan/src/nmigen/nmigen/hdl/ast.py:269
	// cell $flatten\hart.\decoder.$26
	i_flatten_5c_hart_2e__5c_decoder_2e__24_25 = pos_u<32>(p_hart_2e_decoder__insn.curr.slice<24,20>().val());
	// \src: /home/slan/src/nmigen/nmigen/hdl/ast.py:269
	// cell $flatten\hart.\decoder.$24
	i_flatten_5c_hart_2e__5c_decoder_2e__24_23 = pos_u<32>(p_hart_2e_decoder__insn.curr.slice<24,20>().val());
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:174
	// cell $flatten\hart.\decoder.$22
	i_flatten_5c_hart_2e__5c_decoder_2e__24_21 = pos_s<32>(p_hart_2e_decoder__insn.curr.slice<31,20>().val());
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:143
	// cell $flatten\hart.\decoder.$20
	i_flatten_5c_hart_2e__5c_decoder_2e__24_19 = pos_s<32>(p_hart_2e_decoder__insn.curr.slice<31,25>().concat(p_hart_2e_decoder__insn.curr.slice<11,7>()).val());
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:128
	// cell $flatten\hart.\decoder.$18
	i_flatten_5c_hart_2e__5c_decoder_2e__24_17 = pos_s<32>(p_hart_2e_decoder__insn.curr.slice<31,20>().val());
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:92
	// cell $flatten\hart.\decoder.$16
	i_flatten_5c_hart_2e__5c_decoder_2e__24_15 = pos_s<32>(p_hart_2e_decoder__insn.curr.slice<31,20>().val());
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:74
	// cell $flatten\hart.\decoder.$14
	i_flatten_5c_hart_2e__5c_decoder_2e__24_13 = pos_s<32>(p_hart_2e_decoder__insn.curr.slice<31>().concat(p_hart_2e_decoder__insn.curr.slice<19,12>()).concat(p_hart_2e_decoder__insn.curr.slice<20>()).concat(p_hart_2e_decoder__insn.curr.slice<30,21>()).concat(value<1>{0u}).val());
	// cells $flatten\hart.\decoder.$procmux$552 $flatten\hart.\decoder.$procmux$553_CMP0 $flatten\hart.\decoder.$procmux$554_CMP0 $flatten\hart.\decoder.$procmux$555_CMP0 $flatten\hart.\decoder.$procmux$556_CMP0 $flatten\hart.\decoder.$procmux$557_CMP0 $flatten\hart.\decoder.$procmux$558_CMP0 $flatten\hart.\decoder.$procmux$559_CMP0
	p_hart_2e_decoder_2e_alu__src2 = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x13u}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x23u}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x3u}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<10>{0x67u}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x6fu}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x17u}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x37u}) ? value<1>{0x1u} : value<1>{0u})))))));
	// cells $flatten\hart.\decoder.$procmux$522 $flatten\hart.\decoder.$procmux$523_CMP0 $flatten\hart.\decoder.$procmux$524_CMP0
	p_hart_2e_decoder_2e_alu__src1 = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x6fu}) ? value<1>{0x1u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x17u}) ? value<1>{0x1u} : value<1>{0u}));
	// cells $flatten\hart.\decoder.$procmux$510 $flatten\hart.\decoder.$procmux$511_CMP0 $flatten\hart.\decoder.$procmux$512_CMP0 $flatten\hart.\decoder.$procmux$513_CMP0
	p_hart_2e_decoder_2e_rs2__addr = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<31>().concat(p_hart_2e_decoder__insn.curr.slice<29,25>()).concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<13>{0x33u}) ? p_hart_2e_decoder__insn.curr.slice<24,20>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x23u}) ? p_hart_2e_decoder__insn.curr.slice<24,20>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x63u}) ? p_hart_2e_decoder__insn.curr.slice<24,20>().val() : value<5>{0u})));
	// cells $flatten\hart.\decoder.$procmux$499 $flatten\hart.\decoder.$procmux$500_CMP0 $flatten\hart.\decoder.$procmux$501_CMP0 $flatten\hart.\decoder.$35
	p_hart_2e_decoder_2e_mem__func = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x23u}) ? value<1>{0x1u}.concat(p_hart_2e_decoder__insn.curr.slice<14,12>()).val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x3u}) ? pos_u<4>(p_hart_2e_decoder__insn.curr.slice<14,12>().val()) : value<4>{0xfu}));
	// cells $flatten\hart.\decoder.$procmux$560 $flatten\hart.\decoder.$procmux$561_CMP0 $flatten\hart.\decoder.$procmux$562_CMP0 $flatten\hart.\decoder.$procmux$563_CMP0 $flatten\hart.\decoder.$procmux$564_CMP0 $flatten\hart.\decoder.$procmux$565_CMP0 $flatten\hart.\decoder.$procmux$566_CMP0
	p_hart_2e_decoder_2e_rs1__addr = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<31>().concat(p_hart_2e_decoder__insn.curr.slice<29,25>()).concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<13>{0x33u}) ? p_hart_2e_decoder__insn.curr.slice<19,15>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x13u}) ? p_hart_2e_decoder__insn.curr.slice<19,15>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x23u}) ? p_hart_2e_decoder__insn.curr.slice<19,15>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x3u}) ? p_hart_2e_decoder__insn.curr.slice<19,15>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x63u}) ? p_hart_2e_decoder__insn.curr.slice<19,15>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<10>{0x67u}) ? p_hart_2e_decoder__insn.curr.slice<19,15>().val() : value<5>{0u}))))));
	// cells $flatten\hart.\decoder.$procmux$525 $flatten\hart.\decoder.$procmux$526_CMP0 $flatten\hart.\decoder.$procmux$527_CMP0 $flatten\hart.\decoder.$procmux$528_CMP0 $flatten\hart.\decoder.$28
	p_hart_2e_decoder_2e_alu__func = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<31>().concat(p_hart_2e_decoder__insn.curr.slice<29,25>()).concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<13>{0x33u}) ? p_hart_2e_decoder__insn.curr.slice<14,12>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x13u}) ? p_hart_2e_decoder__insn.curr.slice<14,12>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x63u}) ? (p_hart_2e_decoder__insn.curr.slice<13>().val() ? value<3>{0x3u} : value<3>{0x2u}) : value<3>{0u})));
	// cells $flatten\hart.\decoder.$procmux$545 $flatten\hart.\decoder.$procmux$546_CMP0 $flatten\hart.\decoder.$procmux$547_CMP0 $flatten\hart.\decoder.$procmux$548_CMP0 $flatten\hart.\decoder.$procmux$549_CMP0 $flatten\hart.\decoder.$procmux$550_CMP0 $flatten\hart.\decoder.$procmux$541 $flatten\hart.\decoder.$procmux$542_CMP0 $flatten\hart.\decoder.$procmux$543_CMP0 $flatten\hart.\decoder.$procmux$544_ANY
	p_hart_2e_decoder_2e_imm.slice<11,0>() = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x13u}) ? (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x5u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_25.slice<11,0>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x1u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_23.slice<11,0>().val() : (reduce_or<1>(i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_544__CMP) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_21.slice<11,0>().val() : value<12>{0u}))) : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x23u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_19.slice<11,0>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x3u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_17.slice<11,0>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<10>{0x67u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_15.slice<11,0>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x6fu}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_13.slice<11,0>().val() : value<12>{0u})))));
	// cells $flatten\hart.\decoder.$procmux$533 $flatten\hart.\decoder.$procmux$534_CMP0 $flatten\hart.\decoder.$procmux$535_CMP0 $flatten\hart.\decoder.$procmux$536_CMP0 $flatten\hart.\decoder.$procmux$537_CMP0 $flatten\hart.\decoder.$procmux$538_CMP0 $flatten\hart.\decoder.$procmux$539_CMP0 $flatten\hart.\decoder.$procmux$540_CMP0 $flatten\hart.\decoder.$procmux$529 $flatten\hart.\decoder.$procmux$530_CMP0 $flatten\hart.\decoder.$procmux$531_CMP0 $flatten\hart.\decoder.$procmux$532_ANY
	p_hart_2e_decoder_2e_imm.slice<31,12>() = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x13u}) ? (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x5u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_25.slice<31,12>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x1u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_23.slice<31,12>().val() : (reduce_or<1>(i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_532__CMP) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_21.slice<31,12>().val() : value<20>{0u}))) : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x23u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_19.slice<31,12>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x3u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_17.slice<31,12>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<10>{0x67u}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_15.slice<31,12>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x6fu}) ? i_flatten_5c_hart_2e__5c_decoder_2e__24_13.slice<31,12>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x17u}) ? p_hart_2e_decoder__insn.curr.slice<31,12>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x37u}) ? p_hart_2e_decoder__insn.curr.slice<31,12>().val() : value<20>{0u})))))));
	// cells $flatten\hart.\decoder.$procmux$504 $flatten\hart.\decoder.$procmux$505_CMP0 $flatten\hart.\decoder.$procmux$508_CMP0 $flatten\hart.\decoder.$procmux$509_CMP0 $flatten\hart.\decoder.$procmux$502 $flatten\hart.\decoder.$procmux$503_ANY $flatten\hart.\decoder.$procmux$506 $flatten\hart.\decoder.$procmux$507_CMP0
	p_hart_2e_decoder_2e_alu__func__ex = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<31>().concat(p_hart_2e_decoder__insn.curr.slice<29,25>()).concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<13>{0x33u}) ? (reduce_or<1>(i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_503__CMP) ? p_hart_2e_decoder__insn.curr.slice<30>().val() : value<1>{0u}) : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x13u}) ? (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x5u}) ? p_hart_2e_decoder__insn.curr.slice<30>().val() : value<1>{0u}) : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x63u}) ? value<1>{0x1u} : value<1>{0u})));
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:121|/home/slan/src/hartysoc/hdl/riscv/hart.py:126
	// cell $flatten\hart.$procmux$435_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_435__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x1u});
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:121|/home/slan/src/hartysoc/hdl/riscv/hart.py:126
	// cell $flatten\hart.$procmux$435_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_435__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x5u});
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:121|/home/slan/src/hartysoc/hdl/riscv/hart.py:124
	// cell $flatten\hart.$procmux$436_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_436__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0u});
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:121|/home/slan/src/hartysoc/hdl/riscv/hart.py:124
	// cell $flatten\hart.$procmux$436_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_436__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x4u});
	// cells $flatten\interconnect.$116 $flatten\interconnect.$114 $flatten\interconnect.$112 $flatten\interconnect.$110 $flatten\interconnect.$108 $flatten\interconnect.$106 $flatten\interconnect.$105 $flatten\interconnect.$103 $flatten\interconnect.$101 $flatten\interconnect.$99 $flatten\interconnect.$97
	i_flatten_5c_interconnect_2e__24_115 = or_uu<1>(not_u<1>(and_uu<1>(eq_uu<1>(p_hart_2e_dbus____addr.slice<31>().val(), p_hart_2e_ibus____addr.slice<31>().val()), or_uu<1>(reduce_or<1>(p_hart_2e_dbus____wmask), reduce_or<1>(p_hart_2e_dbus____rmask)))), and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_hart_2e_ibus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_hart_2e_ibus____rmask)));
	// cells $flatten\interconnect.$procmux$116 $flatten\interconnect.$84 $flatten\interconnect.$82 $flatten\interconnect.$80 $flatten\interconnect.$78 $flatten\interconnect.$76 $flatten\interconnect.$74 $flatten\interconnect.$73 $flatten\interconnect.$71 $flatten\interconnect.$69 $flatten\interconnect.$67 $flatten\interconnect.$65 $flatten\interconnect.$procmux$114 $flatten\interconnect.$procmux$115_CMP0
	p_interconnect_2e_ram____rmask = (or_uu<1>(not_u<1>(and_uu<1>(eq_uu<1>(p_hart_2e_dbus____addr.slice<31>().val(), p_hart_2e_ibus____addr.slice<31>().val()), or_uu<1>(reduce_or<1>(p_hart_2e_dbus____wmask), reduce_or<1>(p_hart_2e_dbus____rmask)))), and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_hart_2e_ibus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_hart_2e_ibus____rmask))) ? (eq_uu<1>(p_hart_2e_dbus____addr.slice<31>().val(), value<1>{0u}) ? i_flatten_5c_interconnect_2e__24_procmux_24_110__Y : p_hart_2e_dbus____rmask) : i_flatten_5c_interconnect_2e__24_procmux_24_110__Y);
	// cells $flatten\interconnect.$procmux$94 $flatten\interconnect.$procmux$92 $flatten\interconnect.$procmux$93_CMP0
	p_interconnect_2e_ram____wmask = (i_flatten_5c_interconnect_2e__24_115 ? (eq_uu<1>(p_hart_2e_dbus____addr.slice<31>().val(), value<1>{0u}) ? i_flatten_5c_interconnect_2e__24_procmux_24_88__Y : p_hart_2e_dbus____wmask) : i_flatten_5c_interconnect_2e__24_procmux_24_88__Y);
	// cells $flatten\ram.$procmux$269 $flatten\ram.$16 $flatten\ram.$procmux$267 $flatten\ram.$18
	p_ram_2e_ram____rdy = (reduce_or<1>(p_interconnect_2e_ram____wmask) ? value<1>{0x1u} : (reduce_or<1>(p_interconnect_2e_ram____rmask) ? value<1>{0x1u} : value<1>{0u}));
	// cells $flatten\interconnect.$procmux$133 $flatten\interconnect.$52 $flatten\interconnect.$51 $flatten\interconnect.$49 $flatten\interconnect.$47 $flatten\interconnect.$45 $flatten\interconnect.$procmux$131 $flatten\interconnect.$procmux$132_CMP0
	p_interconnect_2e_instruction__bus____rdy = (not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_hart_2e_ibus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_hart_2e_ibus____rmask))) ? (eq_uu<1>(p_hart_2e_ibus____addr.slice<31>().val(), value<1>{0u}) ? value<1>{0x1u} : p_ram_2e_ram____rdy) : value<1>{0x1u});
	// cells $flatten\hart.$procmux$441 $flatten\hart.$54 $flatten\hart.$procmux$439 $flatten\hart.$procmux$437 $flatten\hart.$56 $flatten\hart.$procmux$433 $flatten\hart.$procmux$434_CMP0 $flatten\hart.$procmux$435_ANY $flatten\hart.$procmux$436_ANY $flatten\hart.$60 $flatten\hart.$58
	p_hart_2e_dbus____rmask = (not_u<1>(p_hart_2e_halt.curr) ? (p_interconnect_2e_instruction__bus____rdy ? (ne_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xfu}) ? (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x2u}) ? value<4>{0xfu} : (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_435__CMP) ? (p_hart_2e_alu_2e_out.curr.slice<1>().val() ? value<4>{0xcu} : value<4>{0x3u}) : (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_436__CMP) ? sshl_uu<4>(value<1>{0x1u}, p_hart_2e_alu_2e_out.curr.slice<1,0>().val()) : value<4>{0u}))) : value<4>{0u}) : value<4>{0u}) : value<4>{0u});
	// cells $flatten\hart.$procmux$431 $flatten\hart.$62 $flatten\hart.$procmux$429 $flatten\hart.$procmux$427 $flatten\hart.$64 $flatten\hart.$procmux$423 $flatten\hart.$procmux$424_CMP0 $flatten\hart.$procmux$425_CMP0 $flatten\hart.$procmux$426_CMP0 $flatten\hart.$68 $flatten\hart.$66
	p_hart_2e_dbus____wmask = (not_u<1>(p_hart_2e_halt.curr) ? (p_interconnect_2e_instruction__bus____rdy ? (ne_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xfu}) ? (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xau}) ? value<4>{0xfu} : (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x9u}) ? (p_hart_2e_alu_2e_out.curr.slice<1>().val() ? value<4>{0xcu} : value<4>{0x3u}) : (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x8u}) ? sshl_uu<4>(value<1>{0x1u}, p_hart_2e_alu_2e_out.curr.slice<1,0>().val()) : value<4>{0u}))) : value<4>{0u}) : value<4>{0u}) : value<4>{0u});
	// cells $flatten\hart.$procmux$447 $flatten\hart.$50 $flatten\hart.$procmux$445 $flatten\hart.$procmux$443 $flatten\hart.$52
	p_hart_2e_dbus____addr.slice<31,2>() = (not_u<1>(p_hart_2e_halt.curr) ? (p_interconnect_2e_instruction__bus____rdy ? (ne_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xfu}) ? p_hart_2e_alu_2e_out.curr.slice<31,2>().val() : value<30>{0u}) : value<30>{0u}) : value<30>{0u});
	// cells $flatten\hart.$procmux$459 $flatten\hart.$28 $flatten\hart.$procmux$457 $flatten\hart.\decoder.$procmux$504 $flatten\hart.\decoder.$procmux$505_CMP0 $flatten\hart.\decoder.$procmux$508_CMP0 $flatten\hart.\decoder.$procmux$509_CMP0 $flatten\hart.\decoder.$procmux$502 $flatten\hart.\decoder.$procmux$503_ANY $flatten\hart.\decoder.$procmux$506 $flatten\hart.\decoder.$procmux$507_CMP0
	p_hart_2e_alu__func__ex = (not_u<1>(p_hart_2e_halt.curr) ? (p_interconnect_2e_instruction__bus____rdy ? p_hart_2e_decoder_2e_alu__func__ex : value<1>{0u}) : value<1>{0u});
	// cells $flatten\hart.$procmux$467 $flatten\hart.$24 $flatten\hart.$procmux$465 $flatten\hart.\decoder.$procmux$510 $flatten\hart.\decoder.$procmux$511_CMP0 $flatten\hart.\decoder.$procmux$512_CMP0 $flatten\hart.\decoder.$procmux$513_CMP0
	p_hart_2e_registers__mem__r__addr_24_1 = (not_u<1>(p_hart_2e_halt.curr) ? (p_interconnect_2e_instruction__bus____rdy ? p_hart_2e_decoder_2e_rs2__addr : value<5>{0u}) : value<5>{0u});
	// \hdlname: hart registers rp2
	// cell \hart.registers.rp2
	auto tmp_5 = memory_index(p_hart_2e_registers__mem__r__addr_24_1, 0, 32);
	CXXRTL_ASSERT(tmp_5.valid && "out of bounds read");
	if(tmp_5.valid) {
		value<32> tmp_6 = memory_p_hart_2e_registers_2e_mem[tmp_5.index];
		p_hart_2e_registers_2e_mem__r__data_24_2 = tmp_6;
	} else {
		p_hart_2e_registers_2e_mem__r__data_24_2 = value<32> {};
	}
	// cells $flatten\hart.$procmux$471 $flatten\hart.$22 $flatten\hart.$procmux$469 $flatten\hart.\decoder.$procmux$560 $flatten\hart.\decoder.$procmux$561_CMP0 $flatten\hart.\decoder.$procmux$562_CMP0 $flatten\hart.\decoder.$procmux$563_CMP0 $flatten\hart.\decoder.$procmux$564_CMP0 $flatten\hart.\decoder.$procmux$565_CMP0 $flatten\hart.\decoder.$procmux$566_CMP0
	p_hart_2e_registers__mem__r__addr = (not_u<1>(p_hart_2e_halt.curr) ? (p_interconnect_2e_instruction__bus____rdy ? p_hart_2e_decoder_2e_rs1__addr : value<5>{0u}) : value<5>{0u});
	// \hdlname: hart registers rp1
	// cell \hart.registers.rp1
	auto tmp_7 = memory_index(p_hart_2e_registers__mem__r__addr, 0, 32);
	CXXRTL_ASSERT(tmp_7.valid && "out of bounds read");
	if(tmp_7.valid) {
		value<32> tmp_8 = memory_p_hart_2e_registers_2e_mem[tmp_7.index];
		p_hart_2e_registers_2e_mem__r__data = tmp_8;
	} else {
		p_hart_2e_registers_2e_mem__r__data = value<32> {};
	}
	// cells $flatten\ram.$procmux$261 $flatten\ram.$26 $flatten\ram.$procmux$259 $flatten\ram.$28
	p_ram_2e_ram____rdata = (reduce_or<1>(p_interconnect_2e_ram____wmask) ? value<32>{0u} : (reduce_or<1>(p_interconnect_2e_ram____rmask) ? p_rp____data : value<32>{0u}));
	// cells $flatten\interconnect.$procmux$162 $flatten\interconnect.$10 $flatten\interconnect.$9 $flatten\interconnect.$7 $flatten\interconnect.$5 $flatten\interconnect.$3 $flatten\interconnect.$procmux$160 $flatten\interconnect.$procmux$161_CMP0
	p_interconnect_2e_instruction__bus____rdata = (not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_hart_2e_ibus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_hart_2e_ibus____rmask))) ? (eq_uu<1>(p_hart_2e_ibus____addr.slice<31>().val(), value<1>{0u}) ? value<32>{0x1u} : p_ram_2e_ram____rdata) : p_interconnect_2e_cached__ibus____rdata.curr);
	// cells $flatten\hart.$procmux$479 $flatten\hart.$15 $flatten\hart.$procmux$477
	p_hart_2e_decoder__pc = (not_u<1>(p_hart_2e_halt.curr) ? (p_interconnect_2e_instruction__bus____rdy ? p_hart_2e_pc.curr : value<32>{0u}) : value<32>{0u});
	// cells $flatten\hart.$107 $flatten\hart.$106
	i_flatten_5c_hart_2e__24_103 = (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers_2e_mem__r__data_24_2 : value<32>{0u});
	// cells $flatten\hart.$112 $flatten\hart.$111
	i_flatten_5c_hart_2e__24_108 = (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers_2e_mem__r__data_24_2 : value<32>{0u});
	// cells $flatten\hart.$116 $flatten\hart.$115
	i_flatten_5c_hart_2e__24_113 = (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers_2e_mem__r__data_24_2 : value<32>{0u});
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:119
	// cell $flatten\hart.$72
	i_flatten_5c_hart_2e__24_71 = ne_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xfu});
	// cells $flatten\interconnect.$procmux$6 $flatten\interconnect.$232 $flatten\interconnect.$230 $flatten\interconnect.$228 $flatten\interconnect.$226 $flatten\interconnect.$224 $flatten\interconnect.$222 $flatten\interconnect.$221 $flatten\interconnect.$219 $flatten\interconnect.$217 $flatten\interconnect.$215 $flatten\interconnect.$213 $flatten\interconnect.$procmux$4 $flatten\interconnect.$procmux$5_CMP0
	p_interconnect_2e_data__bus____rdy = (or_uu<1>(not_u<1>(and_uu<1>(eq_uu<1>(p_hart_2e_dbus____addr.slice<31>().val(), p_hart_2e_ibus____addr.slice<31>().val()), or_uu<1>(reduce_or<1>(p_hart_2e_dbus____wmask), reduce_or<1>(p_hart_2e_dbus____rmask)))), and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_hart_2e_ibus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_hart_2e_ibus____rmask))) ? (eq_uu<1>(p_hart_2e_dbus____addr.slice<31>().val(), value<1>{0u}) ? value<1>{0x1u} : p_ram_2e_ram____rdy) : value<1>{0u});
	// cells $flatten\hart.\decoder.$procmux$516 $flatten\hart.\decoder.$procmux$517_CMP0 $flatten\hart.\decoder.$procmux$518_CMP0 $flatten\hart.\decoder.$procmux$519_CMP0
	p_hart_2e_decoder_2e_branch__cond = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x63u}) ? p_hart_2e_decoder__insn.curr.slice<14,12>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<10>{0x67u}) ? value<3>{0x2u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x6fu}) ? value<3>{0x2u} : value<3>{0x3u})));
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:72
	// cell $flatten\hart.$70
	i_flatten_5c_hart_2e__24_69 = not_u<1>(p_hart_2e_halt.curr);
	// \src: /home/slan/src/hartysoc/hdl/riscv/alu.py:19
	// cell $flatten\hart.\alu.$2
	p_hart_2e_alu_2e_eq = eq_uu<1>(p_hart_2e_alu__op1.curr, p_hart_2e_alu__op2.curr);
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:221
	// cell $flatten\hart.$procmux$313_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_313__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x6u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:221
	// cell $flatten\hart.$procmux$313_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_313__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:226
	// cell $flatten\hart.$procmux$312_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_312__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x7u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:226
	// cell $flatten\hart.$procmux$312_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_312__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x5u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:221
	// cell $flatten\hart.$procmux$301_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_301__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x6u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:221
	// cell $flatten\hart.$procmux$301_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_301__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:226
	// cell $flatten\hart.$procmux$300_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_300__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x7u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:203|/home/slan/src/hartysoc/hdl/riscv/hart.py:226
	// cell $flatten\hart.$procmux$300_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_300__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x5u});
	// cells $flatten\hart.\decoder.$procmux$514 $flatten\hart.\decoder.$procmux$515_CMP0 $flatten\hart.\decoder.$33 $flatten\hart.\decoder.$31 $flatten\hart.$procmux$479 $flatten\hart.$15 $flatten\hart.$procmux$477
	p_hart_2e_decoder_2e_branch__target = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x63u}) ? add_ss<34>(p_hart_2e_decoder__pc, pos_s<32>(p_hart_2e_decoder__insn.curr.slice<31>().concat(p_hart_2e_decoder__insn.curr.slice<7>()).concat(p_hart_2e_decoder__insn.curr.slice<30,25>()).concat(p_hart_2e_decoder__insn.curr.slice<11,8>()).concat(value<1>{0u}).val())).slice<31,0>().val() : value<32>{0u});
	// cells $flatten\interconnect.$procmux$12 $flatten\interconnect.$210 $flatten\interconnect.$208 $flatten\interconnect.$206 $flatten\interconnect.$204 $flatten\interconnect.$202 $flatten\interconnect.$200 $flatten\interconnect.$199 $flatten\interconnect.$197 $flatten\interconnect.$195 $flatten\interconnect.$193 $flatten\interconnect.$191 $flatten\interconnect.$procmux$10 $flatten\interconnect.$procmux$11_CMP0
	p_interconnect_2e_data__bus____rdata = (or_uu<1>(not_u<1>(and_uu<1>(eq_uu<1>(p_hart_2e_dbus____addr.slice<31>().val(), p_hart_2e_ibus____addr.slice<31>().val()), or_uu<1>(reduce_or<1>(p_hart_2e_dbus____wmask), reduce_or<1>(p_hart_2e_dbus____rmask)))), and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_hart_2e_ibus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_hart_2e_ibus____rmask))) ? (eq_uu<1>(p_hart_2e_dbus____addr.slice<31>().val(), value<1>{0u}) ? value<32>{0x1u} : p_ram_2e_ram____rdata) : value<32>{0u});
	// cells $flatten\interconnect.$procmux$99 $flatten\interconnect.$procmux$97 $flatten\interconnect.$procmux$98_CMP0
	i_flatten_5c_interconnect_2e__24_procmux_24_99__Y = (i_flatten_5c_interconnect_2e__24_85 ? (eq_uu<1>(p_hart_2e_ibus____addr.slice<31>().val(), value<1>{0u}) ? p_ibus____wmask : value<4>{0u}) : value<4>{0u});
	// cells $flatten\hart.$procmux$421 $flatten\hart.$procmux$419 $flatten\hart.$procmux$417 $flatten\hart.$procmux$406 $flatten\hart.$procmux$407_CMP0 $flatten\hart.$procmux$411_CMP0 $flatten\hart.$procmux$416_CMP0 $flatten\hart.$procmux$409 $flatten\hart.$procmux$410_CMP0 $flatten\hart.$procmux$414 $flatten\hart.$procmux$415_CMP0 $flatten\hart.$87 $flatten\hart.$86
	p_hart_2e_dbus____wdata.slice<15,8>() = (i_flatten_5c_hart_2e__24_69 ? (p_interconnect_2e_instruction__bus____rdy ? (i_flatten_5c_hart_2e__24_71 ? (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xau}) ? i_flatten_5c_hart_2e__24_113.slice<15,8>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x9u}) ? (eq_uu<1>(p_hart_2e_alu_2e_out.curr.slice<1>().val(), value<1>{0u}) ? i_flatten_5c_hart_2e__24_103.slice<15,8>().val() : value<8>{0u}) : (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x8u}) ? (eq_uu<1>(p_hart_2e_alu_2e_out.curr.slice<1,0>().val(), value<2>{0x1u}) ? (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers_2e_mem__r__data_24_2 : value<32>{0u}).slice<7,0>().val() : value<8>{0u}) : value<8>{0u}))) : value<8>{0u}) : value<8>{0u}) : value<8>{0u});
	// cells $flatten\hart.$procmux$404 $flatten\hart.$procmux$402 $flatten\hart.$procmux$400 $flatten\hart.$procmux$389 $flatten\hart.$procmux$390_CMP0 $flatten\hart.$procmux$395_CMP0 $flatten\hart.$procmux$399_CMP0 $flatten\hart.$procmux$393 $flatten\hart.$procmux$394_CMP0 $flatten\hart.$procmux$397 $flatten\hart.$procmux$398_CMP0 $flatten\hart.$92 $flatten\hart.$91
	p_hart_2e_dbus____wdata.slice<23,16>() = (i_flatten_5c_hart_2e__24_69 ? (p_interconnect_2e_instruction__bus____rdy ? (i_flatten_5c_hart_2e__24_71 ? (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xau}) ? i_flatten_5c_hart_2e__24_113.slice<23,16>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x9u}) ? (eq_uu<1>(p_hart_2e_alu_2e_out.curr.slice<1>().val(), value<1>{0u}) ? value<8>{0u} : i_flatten_5c_hart_2e__24_108.slice<7,0>().val()) : (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x8u}) ? (eq_uu<1>(p_hart_2e_alu_2e_out.curr.slice<1,0>().val(), value<2>{0x2u}) ? (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers_2e_mem__r__data_24_2 : value<32>{0u}).slice<7,0>().val() : value<8>{0u}) : value<8>{0u}))) : value<8>{0u}) : value<8>{0u}) : value<8>{0u});
	// cells $flatten\hart.$procmux$387 $flatten\hart.$procmux$385 $flatten\hart.$procmux$383 $flatten\hart.$procmux$371 $flatten\hart.$procmux$372_CMP0 $flatten\hart.$procmux$376_CMP0 $flatten\hart.$procmux$382_CMP0 $flatten\hart.$procmux$374 $flatten\hart.$procmux$375_CMP0 $flatten\hart.$procmux$380 $flatten\hart.$procmux$381_CMP0 $flatten\hart.$82 $flatten\hart.$81
	p_hart_2e_dbus____wdata.slice<7,0>() = (i_flatten_5c_hart_2e__24_69 ? (p_interconnect_2e_instruction__bus____rdy ? (i_flatten_5c_hart_2e__24_71 ? (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xau}) ? i_flatten_5c_hart_2e__24_113.slice<7,0>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x9u}) ? (eq_uu<1>(p_hart_2e_alu_2e_out.curr.slice<1>().val(), value<1>{0u}) ? i_flatten_5c_hart_2e__24_103.slice<7,0>().val() : value<8>{0u}) : (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x8u}) ? (eq_uu<1>(p_hart_2e_alu_2e_out.curr.slice<1,0>().val(), value<2>{0u}) ? (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers_2e_mem__r__data_24_2 : value<32>{0u}).slice<7,0>().val() : value<8>{0u}) : value<8>{0u}))) : value<8>{0u}) : value<8>{0u}) : value<8>{0u});
	// cells $flatten\hart.$procmux$369 $flatten\hart.$procmux$367 $flatten\hart.$procmux$365 $flatten\hart.$procmux$351 $flatten\hart.$procmux$352_CMP0 $flatten\hart.$procmux$357_CMP0 $flatten\hart.$procmux$364_CMP0 $flatten\hart.$procmux$355 $flatten\hart.$procmux$356_CMP0 $flatten\hart.$procmux$360 $flatten\hart.$procmux$361_CMP0 $flatten\hart.$procmux$362_CMP0 $flatten\hart.$procmux$363_CMP0 $flatten\hart.$97 $flatten\hart.$96
	p_hart_2e_dbus____wdata.slice<31,24>() = (i_flatten_5c_hart_2e__24_69 ? (p_interconnect_2e_instruction__bus____rdy ? (i_flatten_5c_hart_2e__24_71 ? (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xau}) ? i_flatten_5c_hart_2e__24_113.slice<31,24>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x9u}) ? (eq_uu<1>(p_hart_2e_alu_2e_out.curr.slice<1>().val(), value<1>{0u}) ? value<8>{0u} : i_flatten_5c_hart_2e__24_108.slice<15,8>().val()) : (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x8u}) ? (eq_uu<1>(p_hart_2e_alu_2e_out.curr.slice<1,0>().val(), value<2>{0x2u}) ? value<8>{0u} : (eq_uu<1>(p_hart_2e_alu_2e_out.curr.slice<1,0>().val(), value<2>{0x1u}) ? value<8>{0u} : (eq_uu<1>(p_hart_2e_alu_2e_out.curr.slice<1,0>().val(), value<2>{0u}) ? value<8>{0u} : (reduce_or<1>(p_hart_2e_registers__mem__r__addr_24_1) ? p_hart_2e_registers_2e_mem__r__data_24_2 : value<32>{0u}).slice<7,0>().val()))) : value<8>{0u}))) : value<8>{0u}) : value<8>{0u}) : value<8>{0u});
	// cells $flatten\hart.\decoder.$procmux$567 $flatten\hart.\decoder.$procmux$568_CMP0 $flatten\hart.\decoder.$procmux$569_CMP0 $flatten\hart.\decoder.$procmux$570_CMP0 $flatten\hart.\decoder.$procmux$571_CMP0 $flatten\hart.\decoder.$procmux$572_CMP0 $flatten\hart.\decoder.$procmux$573_CMP0 $flatten\hart.\decoder.$procmux$574_CMP0 $flatten\hart.\decoder.$procmux$575_CMP0 $flatten\hart.\decoder.$procmux$576_CMP0
	p_hart_2e_decoder_2e_rd__addr = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<31>().concat(p_hart_2e_decoder__insn.curr.slice<29,25>()).concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<13>{0x33u}) ? p_hart_2e_decoder__insn.curr.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x13u}) ? p_hart_2e_decoder__insn.curr.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x3u}) ? p_hart_2e_decoder__insn.curr.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<10>{0x67u}) ? p_hart_2e_decoder__insn.curr.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x6fu}) ? p_hart_2e_decoder__insn.curr.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x17u}) ? p_hart_2e_decoder__insn.curr.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x37u}) ? p_hart_2e_decoder__insn.curr.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<31,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<27>{0x6010173u}) ? p_hart_2e_decoder__insn.curr.slice<11,7>().val() : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<31,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<27>{0x6000173u}) ? p_hart_2e_decoder__insn.curr.slice<11,7>().val() : value<5>{0u})))))))));
	// cells $flatten\interconnect.$procmux$104 $flatten\interconnect.$procmux$102 $flatten\interconnect.$procmux$103_CMP0
	p_interconnect_2e_console____wmask = (i_flatten_5c_interconnect_2e__24_115 ? (eq_uu<1>(p_hart_2e_dbus____addr.slice<31>().val(), value<1>{0u}) ? p_hart_2e_dbus____wmask : i_flatten_5c_interconnect_2e__24_procmux_24_99__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_99__Y);
	// cells $flatten\interconnect.$procmux$150 $flatten\interconnect.$20 $flatten\interconnect.$19 $flatten\interconnect.$17 $flatten\interconnect.$15 $flatten\interconnect.$13 $flatten\interconnect.$procmux$148 $flatten\interconnect.$procmux$149_CMP0
	i_flatten_5c_interconnect_2e__24_procmux_24_150__Y = (not_u<1>(and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_hart_2e_ibus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_hart_2e_ibus____rmask))) ? (eq_uu<1>(p_hart_2e_ibus____addr.slice<31>().val(), value<1>{0u}) ? p_ibus____wdata : value<32>{0u}) : value<32>{0u});
	// cells $flatten\hart.\decoder.$procmux$577 $flatten\hart.\decoder.$procmux$578_CMP0 $flatten\hart.\decoder.$procmux$579_CMP0 $flatten\hart.\decoder.$procmux$580_CMP0 $flatten\hart.\decoder.$procmux$581_CMP0 $flatten\hart.\decoder.$procmux$582_CMP0 $flatten\hart.\decoder.$procmux$583_CMP0 $flatten\hart.\decoder.$procmux$584_CMP0 $flatten\hart.\decoder.$procmux$585_CMP0
	p_hart_2e_decoder_2e_reg__src = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<31>().concat(p_hart_2e_decoder__insn.curr.slice<29,25>()).concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<13>{0x33u}) ? value<3>{0x2u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x13u}) ? value<3>{0x2u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<10>{0x67u}) ? value<3>{0x3u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x6fu}) ? value<3>{0x3u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x17u}) ? value<3>{0x2u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x37u}) ? value<3>{0x2u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<31,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<27>{0x6010173u}) ? value<3>{0x5u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<31,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<27>{0x6000173u}) ? value<3>{0x4u} : value<3>{0u}))))))));
	// cells $flatten\hart.$procmux$475 $flatten\hart.$17 $flatten\hart.$procmux$473 $flatten\hart.$20
	p_hart_2e_pc__incr = (not_u<1>(p_hart_2e_halt.curr) ? (p_interconnect_2e_instruction__bus____rdy ? add_uu<33>(p_hart_2e_pc.curr, value<3>{0x4u}).slice<31,0>().val() : value<32>{0x80000000u}) : value<32>{0x80000000u});
	// cells $flatten\hart.$procmux$321 $flatten\hart.$170 $flatten\hart.$procmux$319 $flatten\hart.$procmux$317 $flatten\hart.$174 $flatten\hart.$172 $flatten\hart.$procmux$311 $flatten\hart.$procmux$312_ANY $flatten\hart.$procmux$313_ANY $flatten\hart.$procmux$314_CMP0 $flatten\hart.$procmux$315_CMP0 $flatten\hart.$procmux$316_CMP0 $flatten\hart.$182 $flatten\hart.$181 $flatten\hart.$178 $flatten\hart.$176
	p_hart_2e_branch__taken = (not_u<1>(p_hart_2e_halt.curr) ? (p_interconnect_2e_instruction__bus____rdy ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xfu}), p_interconnect_2e_data__bus____rdy) ? (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_312__CMP) ? not_u<1>(reduce_or<1>(p_hart_2e_alu_2e_out.curr)) : (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_313__CMP) ? reduce_or<1>(p_hart_2e_alu_2e_out.curr) : (eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x1u}) ? not_u<1>(p_hart_2e_alu_2e_eq) : (eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0u}) ? p_hart_2e_alu_2e_eq : (eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x2u}) ? value<1>{0x1u} : value<1>{0u}))))) : value<1>{0u}) : value<1>{0u}) : value<1>{0u});
	// cells $flatten\hart.$procmux$309 $flatten\hart.$184 $flatten\hart.$procmux$307 $flatten\hart.$procmux$305 $flatten\hart.$188 $flatten\hart.$186 $flatten\hart.$procmux$299 $flatten\hart.$procmux$300_ANY $flatten\hart.$procmux$301_ANY $flatten\hart.$procmux$302_CMP0 $flatten\hart.$procmux$303_CMP0 $flatten\hart.$procmux$304_CMP0
	p_hart_2e_branch__target = (not_u<1>(p_hart_2e_halt.curr) ? (p_interconnect_2e_instruction__bus____rdy ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xfu}), p_interconnect_2e_data__bus____rdy) ? (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_300__CMP) ? p_hart_2e_decoder_2e_branch__target : (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_301__CMP) ? p_hart_2e_decoder_2e_branch__target : (eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x1u}) ? p_hart_2e_decoder_2e_branch__target : (eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0u}) ? p_hart_2e_decoder_2e_branch__target : (eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x2u}) ? p_hart_2e_alu_2e_out.curr : value<32>{0x80000000u}))))) : value<32>{0x80000000u}) : value<32>{0x80000000u}) : value<32>{0x80000000u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:165|/home/slan/src/hartysoc/hdl/riscv/hart.py:166
	// cell $flatten\hart.$procmux$341_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_341__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:165|/home/slan/src/hartysoc/hdl/riscv/hart.py:166
	// cell $flatten\hart.$procmux$341_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_341__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:165|/home/slan/src/hartysoc/hdl/riscv/hart.py:176
	// cell $flatten\hart.$procmux$340_CMP1
	i_flatten_5c_hart_2e__24_procmux_24_340__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x5u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/hart.py:165|/home/slan/src/hartysoc/hdl/riscv/hart.py:176
	// cell $flatten\hart.$procmux$340_CMP0
	i_flatten_5c_hart_2e__24_procmux_24_340__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x1u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:208|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$622_CMP0
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x1u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:208|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$622_CMP1
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x2u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:208|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$622_CMP2
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP.slice<2>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x3u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:208|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$622_CMP3
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP.slice<3>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:208|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$622_CMP4
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP.slice<4>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x6u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:208|/home/slan/src/hartysoc/hdl/riscv/decoder.py:203
	// cell $flatten\hart.\decoder.$procmux$622_CMP5
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP.slice<5>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x7u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:149|/home/slan/src/hartysoc/hdl/riscv/decoder.py:148
	// cell $flatten\hart.\decoder.$procmux$633_CMP0
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_633__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:149|/home/slan/src/hartysoc/hdl/riscv/decoder.py:148
	// cell $flatten\hart.\decoder.$procmux$633_CMP1
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_633__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x1u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:149|/home/slan/src/hartysoc/hdl/riscv/decoder.py:148
	// cell $flatten\hart.\decoder.$procmux$633_CMP2
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_633__CMP.slice<2>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x2u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:134|/home/slan/src/hartysoc/hdl/riscv/decoder.py:133
	// cell $flatten\hart.\decoder.$procmux$637_CMP0
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP.slice<0>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:134|/home/slan/src/hartysoc/hdl/riscv/decoder.py:133
	// cell $flatten\hart.\decoder.$procmux$637_CMP1
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP.slice<1>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x1u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:134|/home/slan/src/hartysoc/hdl/riscv/decoder.py:133
	// cell $flatten\hart.\decoder.$procmux$637_CMP2
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP.slice<2>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x2u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:134|/home/slan/src/hartysoc/hdl/riscv/decoder.py:133
	// cell $flatten\hart.\decoder.$procmux$637_CMP3
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP.slice<3>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x4u});
	// \full_case: 1
	// \src: /home/slan/src/hartysoc/hdl/riscv/decoder.py:134|/home/slan/src/hartysoc/hdl/riscv/decoder.py:133
	// cell $flatten\hart.\decoder.$procmux$637_CMP4
	i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP.slice<4>() = eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x5u});
	// cells $flatten\interconnect.$procmux$155 $flatten\interconnect.$42 $flatten\interconnect.$40 $flatten\interconnect.$38 $flatten\interconnect.$36 $flatten\interconnect.$34 $flatten\interconnect.$32 $flatten\interconnect.$31 $flatten\interconnect.$29 $flatten\interconnect.$27 $flatten\interconnect.$25 $flatten\interconnect.$23 $flatten\interconnect.$procmux$153 $flatten\interconnect.$procmux$154_CMP0
	p_interconnect_2e_console____wdata = (or_uu<1>(not_u<1>(and_uu<1>(eq_uu<1>(p_hart_2e_dbus____addr.slice<31>().val(), p_hart_2e_ibus____addr.slice<31>().val()), or_uu<1>(reduce_or<1>(p_hart_2e_dbus____wmask), reduce_or<1>(p_hart_2e_dbus____rmask)))), and_uu<1>(and_uu<1>(p_interconnect_2e_cache__present.curr, eq_uu<1>(p_interconnect_2e_cached__ibus____addr.curr, p_hart_2e_ibus____addr)), eq_uu<1>(p_interconnect_2e_cached__ibus____rmask.curr, p_hart_2e_ibus____rmask))) ? (eq_uu<1>(p_hart_2e_dbus____addr.slice<31>().val(), value<1>{0u}) ? p_hart_2e_dbus____wdata : i_flatten_5c_interconnect_2e__24_procmux_24_150__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_150__Y);
	// cells $flatten\console.$procmux$166 $flatten\console.$10
	p_console_2e_uart__tx__rdy = (reduce_or<1>(p_interconnect_2e_console____wmask) ? value<1>{0x1u} : value<1>{0u});
	// cells $flatten\hart.\decoder.$procmux$623 $flatten\hart.\decoder.$procmux$624_CMP0 $flatten\hart.\decoder.$procmux$630_CMP0 $flatten\hart.\decoder.$procmux$634_CMP0 $flatten\hart.\decoder.$procmux$638_CMP0 $flatten\hart.\decoder.$procmux$641_CMP0 $flatten\hart.\decoder.$procmux$642_CMP0 $flatten\hart.\decoder.$procmux$643_CMP0 $flatten\hart.\decoder.$procmux$644_CMP0 $flatten\hart.\decoder.$procmux$645_CMP0 $flatten\hart.\decoder.$procmux$646_CMP0 $flatten\hart.\decoder.$procmux$647_CMP0 $flatten\hart.\decoder.$procmux$621 $flatten\hart.\decoder.$procmux$622_ANY $flatten\hart.\decoder.$procmux$619 $flatten\hart.\decoder.$procmux$628 $flatten\hart.\decoder.$procmux$629_CMP0 $flatten\hart.\decoder.$procmux$626 $flatten\hart.\decoder.$procmux$632 $flatten\hart.\decoder.$procmux$633_ANY $flatten\hart.\decoder.$procmux$636 $flatten\hart.\decoder.$procmux$637_ANY $flatten\hart.\decoder.$procmux$639 $flatten\hart.\decoder.$6 $flatten\hart.\decoder.$4 $flatten\hart.\decoder.$2
	p_hart_2e_decoder_2e_trap = (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<31>().concat(p_hart_2e_decoder__insn.curr.slice<29,25>()).concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<13>{0x33u}) ? (reduce_or<1>(i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_622__CMP) ? (p_hart_2e_decoder__insn.curr.slice<30>().val() ? value<1>{0x1u} : value<1>{0u}) : value<1>{0u}) : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x13u}) ? (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().val(), value<3>{0x1u}) ? (p_hart_2e_decoder__insn.curr.slice<30>().val() ? value<1>{0x1u} : value<1>{0u}) : value<1>{0u}) : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x23u}) ? (reduce_or<1>(i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_633__CMP) ? value<1>{0u} : value<1>{0x1u}) : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x3u}) ? (reduce_or<1>(i_flatten_5c_hart_2e__5c_decoder_2e__24_procmux_24_637__CMP) ? value<1>{0u} : value<1>{0x1u}) : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x63u}) ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x2u}), eq_uu<1>(p_hart_2e_decoder_2e_branch__cond, value<3>{0x3u})) ? value<1>{0x1u} : value<1>{0u}) : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<14,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<10>{0x67u}) ? value<1>{0u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x6fu}) ? value<1>{0u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x17u}) ? value<1>{0u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<6,0>().val(), value<7>{0x37u}) ? value<1>{0u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<31,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<27>{0x6010173u}) ? value<1>{0u} : (eq_uu<1>(p_hart_2e_decoder__insn.curr.slice<31,12>().concat(p_hart_2e_decoder__insn.curr.slice<6,0>()).val(), value<27>{0x6000173u}) ? value<1>{0u} : value<1>{0x1u})))))))))));
	// cells $flatten\hart.$procmux$297 $flatten\hart.$190 $flatten\hart.$procmux$295 $flatten\hart.$procmux$293 $flatten\hart.$194 $flatten\hart.$192 $flatten\hart.$196 $flatten\hart.$procmux$321 $flatten\hart.$170 $flatten\hart.$procmux$319 $flatten\hart.$procmux$317 $flatten\hart.$174 $flatten\hart.$172 $flatten\hart.$procmux$311 $flatten\hart.$procmux$312_ANY $flatten\hart.$procmux$313_ANY $flatten\hart.$procmux$314_CMP0 $flatten\hart.$procmux$315_CMP0 $flatten\hart.$procmux$316_CMP0 $flatten\hart.$182 $flatten\hart.$181 $flatten\hart.$178 $flatten\hart.$176 $flatten\hart.$procmux$309 $flatten\hart.$184 $flatten\hart.$procmux$307 $flatten\hart.$procmux$305 $flatten\hart.$188 $flatten\hart.$186 $flatten\hart.$procmux$299 $flatten\hart.$procmux$300_ANY $flatten\hart.$procmux$301_ANY $flatten\hart.$procmux$302_CMP0 $flatten\hart.$procmux$303_CMP0 $flatten\hart.$procmux$304_CMP0
	p_hart_2e_pc__wdata = (not_u<1>(p_hart_2e_halt.curr) ? (p_interconnect_2e_instruction__bus____rdy ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xfu}), p_interconnect_2e_data__bus____rdy) ? (p_hart_2e_branch__taken ? p_hart_2e_branch__target : p_hart_2e_pc__incr) : value<32>{0x80000000u}) : value<32>{0x80000000u}) : value<32>{0x80000000u});
	// cells $flatten\console.$procmux$164 $flatten\console.$12 $flatten\interconnect.$procmux$155 $flatten\interconnect.$42 $flatten\interconnect.$40 $flatten\interconnect.$38 $flatten\interconnect.$36 $flatten\interconnect.$34 $flatten\interconnect.$32 $flatten\interconnect.$31 $flatten\interconnect.$29 $flatten\interconnect.$27 $flatten\interconnect.$25 $flatten\interconnect.$23 $flatten\interconnect.$procmux$153 $flatten\interconnect.$procmux$154_CMP0
	p_console_2e_uart__tx__data = (reduce_or<1>(p_interconnect_2e_console____wmask) ? p_interconnect_2e_console____wdata.slice<7,0>().val() : value<8>{0u});
	// cells $flatten\hart.$procmux$330 $flatten\hart.$162 $flatten\hart.$procmux$328 $flatten\hart.$procmux$326 $flatten\hart.$166 $flatten\hart.$164 $flatten\hart.$procmux$324 $flatten\hart.$168
	p_hart_2e_registers__mem__w__addr = (not_u<1>(p_hart_2e_halt.curr) ? (p_interconnect_2e_instruction__bus____rdy ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xfu}), p_interconnect_2e_data__bus____rdy) ? (eq_uu<1>(p_hart_2e_decoder_2e_rd__addr, value<1>{0u}) ? value<5>{0u} : p_hart_2e_decoder_2e_rd__addr) : value<5>{0u}) : value<5>{0u}) : value<5>{0u});
	// cells $flatten\hart.$procmux$349 $flatten\hart.$118 $flatten\hart.$procmux$347 $flatten\hart.$procmux$345 $flatten\hart.$122 $flatten\hart.$120 $flatten\hart.$procmux$343 $flatten\hart.$124 $flatten\hart.$procmux$338 $flatten\hart.$procmux$339_CMP0 $flatten\hart.$procmux$340_ANY $flatten\hart.$procmux$341_ANY $flatten\hart.$160 $flatten\hart.$159 $flatten\hart.$158 $flatten\hart.$149 $flatten\hart.$148 $flatten\hart.$147 $flatten\hart.$155 $flatten\hart.$154 $flatten\hart.$153 $flatten\hart.$142 $flatten\hart.$141 $flatten\hart.$140 $flatten\hart.$131 $flatten\hart.$130 $flatten\hart.$129 $flatten\hart.$137 $flatten\hart.$136 $flatten\hart.$135 $flatten\hart.$procmux$332 $flatten\hart.$procmux$333_CMP0 $flatten\hart.$procmux$334_CMP0 $flatten\hart.$procmux$335_CMP0 $flatten\hart.$procmux$336_CMP0
	p_hart_2e_registers__mem__w__data = (not_u<1>(p_hart_2e_halt.curr) ? (p_interconnect_2e_instruction__bus____rdy ? (or_uu<1>(eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0xfu}), p_interconnect_2e_data__bus____rdy) ? (eq_uu<1>(p_hart_2e_decoder_2e_rd__addr, value<1>{0u}) ? value<32>{0u} : (eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x2u}) ? p_interconnect_2e_data__bus____rdata : (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_340__CMP) ? pos_s<32>((eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x5u}) ? pos_u<17>(shift_uu<16>(p_interconnect_2e_data__bus____rdata, mul_uu<6>(p_hart_2e_alu_2e_out.curr.slice<1>().val(), value<5>{0x10u}))) : pos_s<17>(shift_uu<16>(p_interconnect_2e_data__bus____rdata, mul_uu<6>(p_hart_2e_alu_2e_out.curr.slice<1>().val(), value<5>{0x10u}))))) : (reduce_or<1>(i_flatten_5c_hart_2e__24_procmux_24_341__CMP) ? pos_s<32>((eq_uu<1>(p_hart_2e_decoder_2e_mem__func, value<4>{0x4u}) ? pos_u<9>(shift_uu<8>(p_interconnect_2e_data__bus____rdata, mul_uu<6>(p_hart_2e_alu_2e_out.curr.slice<1,0>().val(), value<4>{0x8u}))) : pos_s<9>(shift_uu<8>(p_interconnect_2e_data__bus____rdata, mul_uu<6>(p_hart_2e_alu_2e_out.curr.slice<1,0>().val(), value<4>{0x8u}))))) : (eq_uu<1>(p_hart_2e_decoder_2e_reg__src, value<3>{0x5u}) ? p_hart_2e_minstret.curr.slice<31,0>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_reg__src, value<3>{0x4u}) ? p_hart_2e_mcycle.curr.slice<31,0>().val() : (eq_uu<1>(p_hart_2e_decoder_2e_reg__src, value<3>{0x3u}) ? p_hart_2e_pc__incr : (eq_uu<1>(p_hart_2e_decoder_2e_reg__src, value<3>{0x2u}) ? p_hart_2e_alu_2e_out.curr : value<32>{0u})))))))) : value<32>{0u}) : value<32>{0u}) : value<32>{0u});
	// cells $flatten\pll.\rs_hart.$4 $flatten\pll.\rs_hart.$2
	p_pll_2e_rs__hart_2e_async__ff__rst = or_uu<1>(not_u<1>(p_pll_2e_rs__hart__locked.curr), p_rst);
	// \src: /home/slan/src/hartysoc/hdl/riscv/registers.py:25
	// cell $flatten\hart.\registers.$5
	p_hart_2e_registers_2e_mem__w__en = reduce_or<1>(p_hart_2e_registers__mem__w__addr);
}

CXXRTL_EXTREMELY_COLD
void p_top::debug_info(debug_items &items, std::string path) {
	assert(path.empty() || path[path.size() - 1] == ' ');
	items.add(path + "interconnect instruction_bus__rdy", debug_item(debug_eval_outline, p_interconnect_2e_instruction__bus____rdy, 0));
	items.add(path + "interconnect instruction_bus__addr", debug_item(debug_eval_outline, p_hart_2e_ibus____addr, 0));
	items.add(path + "interconnect instruction_bus__rmask", debug_item(debug_eval_outline, p_hart_2e_ibus____rmask, 0));
	items.add(path + "interconnect instruction_bus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_instruction__bus____rdata, 0));
	items.add(path + "interconnect instruction_bus__wmask", debug_item(debug_alias(), p_ibus____wmask, 0));
	items.add(path + "interconnect instruction_bus__wdata", debug_item(debug_alias(), p_ibus____wdata, 0));
	items.add(path + "interconnect data_bus__rdy", debug_item(debug_eval_outline, p_interconnect_2e_data__bus____rdy, 0));
	items.add(path + "interconnect data_bus__addr", debug_item(debug_eval_outline, p_hart_2e_dbus____addr, 0));
	items.add(path + "interconnect data_bus__rmask", debug_item(debug_eval_outline, p_hart_2e_dbus____rmask, 0));
	items.add(path + "interconnect data_bus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_data__bus____rdata, 0));
	items.add(path + "interconnect data_bus__wmask", debug_item(debug_eval_outline, p_hart_2e_dbus____wmask, 0));
	items.add(path + "interconnect data_bus__wdata", debug_item(debug_eval_outline, p_hart_2e_dbus____wdata, 0));
	items.add(path + "interconnect hart_clk", debug_item(debug_alias(), p_hart__clk, 0));
	items.add(path + "interconnect hart_rst", debug_item(debug_alias(), p_pll_2e_rs__hart_2e_stage1, 0));
	items.add(path + "interconnect ram__wmask", debug_item(debug_eval_outline, p_interconnect_2e_ram____wmask, 0));
	items.add(path + "interconnect ram__rmask", debug_item(debug_eval_outline, p_interconnect_2e_ram____rmask, 0));
	items.add(path + "interconnect ram__rdy", debug_item(debug_eval_outline, p_ram_2e_ram____rdy, 0));
	items.add(path + "interconnect ram__rdata", debug_item(debug_eval_outline, p_ram_2e_ram____rdata, 0));
	static const value<1> const_p_interconnect_2e_console____rdy = value<1>{0x1u};
	items.add(path + "interconnect console__rdy", debug_item(const_p_interconnect_2e_console____rdy, 0));
	static const value<32> const_p_interconnect_2e_console____rdata = value<32>{0x1u};
	items.add(path + "interconnect console__rdata", debug_item(const_p_interconnect_2e_console____rdata, 0));
	items.add(path + "interconnect console__wmask", debug_item(debug_eval_outline, p_interconnect_2e_console____wmask, 0));
	items.add(path + "interconnect console__wdata", debug_item(debug_eval_outline, p_interconnect_2e_console____wdata, 0));
	items.add(path + "interconnect cache_present", debug_item(p_interconnect_2e_cache__present, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "interconnect cached_ibus__addr", debug_item(p_interconnect_2e_cached__ibus____addr, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "interconnect cached_ibus__rmask", debug_item(p_interconnect_2e_cached__ibus____rmask, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "interconnect cached_ibus__rdata", debug_item(p_interconnect_2e_cached__ibus____rdata, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "console hart_clk", debug_item(debug_alias(), p_hart__clk, 0));
	items.add(path + "console hart_rst", debug_item(debug_alias(), p_pll_2e_rs__hart_2e_stage1, 0));
	static const value<1> const_p_console_2e_console____rdy = value<1>{0x1u};
	items.add(path + "console console__rdy", debug_item(const_p_console_2e_console____rdy, 0));
	static const value<32> const_p_console_2e_console____rdata = value<32>{0x1u};
	items.add(path + "console console__rdata", debug_item(const_p_console_2e_console____rdata, 0));
	items.add(path + "console console__wmask", debug_item(debug_eval_outline, p_interconnect_2e_console____wmask, 0));
	items.add(path + "console console__wdata", debug_item(debug_eval_outline, p_interconnect_2e_console____wdata, 0));
	items.add(path + "console rx_i", debug_item(debug_alias(), p_rx__i, 0));
	items.add(path + "console rx_ack", debug_item(debug_alias(), p_rx__ack, 0));
	items.add(path + "console uart_tx_rdy", debug_item(debug_eval_outline, p_console_2e_uart__tx__rdy, 0));
	items.add(path + "console uart_tx_data", debug_item(debug_eval_outline, p_console_2e_uart__tx__data, 0));
	items.add(path + "console uart rx_ovf", debug_item(p_console_2e_uart_2e_rx__ovf, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "console uart rx_phase", debug_item(p_console_2e_uart_2e_rx__phase, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "console uart rx_rdy", debug_item(p_console_2e_uart_2e_rx__rdy, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "console uart rx_count", debug_item(p_console_2e_uart_2e_rx__count, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "console uart rx_shreg", debug_item(p_console_2e_uart_2e_rx__shreg, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "console uart tx_phase", debug_item(p_console_2e_uart_2e_tx__phase, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "console uart tx_count", debug_item(p_console_2e_uart_2e_tx__count, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "console uart tx_shreg", debug_item(p_console_2e_uart_2e_tx__shreg, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "console uart rx_ack", debug_item(debug_alias(), p_rx__ack, 0));
	items.add(path + "console uart rx_i", debug_item(debug_alias(), p_rx__i, 0));
	items.add(path + "console uart tx_data", debug_item(debug_eval_outline, p_console_2e_uart__tx__data, 0));
	items.add(path + "console uart tx_rdy", debug_item(debug_eval_outline, p_console_2e_uart__tx__rdy, 0));
	items.add(path + "console uart hart_rst", debug_item(debug_alias(), p_pll_2e_rs__hart_2e_stage1, 0));
	items.add(path + "console uart hart_clk", debug_item(debug_alias(), p_hart__clk, 0));
	items.add(path + "ram ram__wmask", debug_item(debug_eval_outline, p_interconnect_2e_ram____wmask, 0));
	items.add(path + "ram ram__rmask", debug_item(debug_eval_outline, p_interconnect_2e_ram____rmask, 0));
	items.add(path + "ram ram__rdy", debug_item(debug_eval_outline, p_ram_2e_ram____rdy, 0));
	items.add(path + "ram ram__rdata", debug_item(debug_eval_outline, p_ram_2e_ram____rdata, 0));
	items.add(path + "ram rp__data", debug_item(debug_alias(), p_rp____data, 0));
	items.add(path + "hart ibus__rdy", debug_item(debug_eval_outline, p_interconnect_2e_instruction__bus____rdy, 0));
	items.add(path + "hart ibus__addr", debug_item(debug_eval_outline, p_hart_2e_ibus____addr, 0));
	items.add(path + "hart ibus__rmask", debug_item(debug_eval_outline, p_hart_2e_ibus____rmask, 0));
	items.add(path + "hart ibus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_instruction__bus____rdata, 0));
	items.add(path + "hart dbus__rdy", debug_item(debug_eval_outline, p_interconnect_2e_data__bus____rdy, 0));
	items.add(path + "hart dbus__addr", debug_item(debug_eval_outline, p_hart_2e_dbus____addr, 0));
	items.add(path + "hart dbus__rmask", debug_item(debug_eval_outline, p_hart_2e_dbus____rmask, 0));
	items.add(path + "hart dbus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_data__bus____rdata, 0));
	items.add(path + "hart dbus__wmask", debug_item(debug_eval_outline, p_hart_2e_dbus____wmask, 0));
	items.add(path + "hart dbus__wdata", debug_item(debug_eval_outline, p_hart_2e_dbus____wdata, 0));
	items.add(path + "hart hart_clk", debug_item(debug_alias(), p_hart__clk, 0));
	items.add(path + "hart hart_rst", debug_item(debug_alias(), p_pll_2e_rs__hart_2e_stage1, 0));
	items.add(path + "hart registers_mem_r_addr", debug_item(debug_eval_outline, p_hart_2e_registers__mem__r__addr, 0));
	items.add(path + "hart registers_mem_r_addr$1", debug_item(debug_eval_outline, p_hart_2e_registers__mem__r__addr_24_1, 0));
	items.add(path + "hart registers_mem_r_data", debug_item(debug_eval_outline, p_hart_2e_registers_2e_mem__r__data, 0));
	items.add(path + "hart registers_mem_r_data$2", debug_item(debug_eval_outline, p_hart_2e_registers_2e_mem__r__data_24_2, 0));
	items.add(path + "hart registers_mem_w_data", debug_item(debug_eval_outline, p_hart_2e_registers__mem__w__data, 0));
	items.add(path + "hart registers_mem_w_addr", debug_item(debug_eval_outline, p_hart_2e_registers__mem__w__addr, 0));
	items.add(path + "hart alu_func", debug_item(p_hart_2e_alu__func, 0, debug_item::DRIVEN_COMB));
	items.add(path + "hart alu_func_ex", debug_item(debug_eval_outline, p_hart_2e_alu__func__ex, 0));
	items.add(path + "hart alu_op1", debug_item(p_hart_2e_alu__op1, 0, debug_item::DRIVEN_COMB));
	items.add(path + "hart alu_op2", debug_item(p_hart_2e_alu__op2, 0, debug_item::DRIVEN_COMB));
	items.add(path + "hart alu_out", debug_item(debug_alias(), p_hart_2e_alu_2e_out, 0));
	items.add(path + "hart alu_eq", debug_item(debug_eval_outline, p_hart_2e_alu_2e_eq, 0));
	items.add(path + "hart decoder_trap", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_trap, 0));
	items.add(path + "hart decoder_insn", debug_item(p_hart_2e_decoder__insn, 0, debug_item::DRIVEN_COMB));
	items.add(path + "hart decoder_pc", debug_item(debug_eval_outline, p_hart_2e_decoder__pc, 0));
	items.add(path + "hart decoder_rs1_addr", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_rs1__addr, 0));
	items.add(path + "hart decoder_rs2_addr", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_rs2__addr, 0));
	items.add(path + "hart decoder_alu_func", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_alu__func, 0));
	items.add(path + "hart decoder_alu_func_ex", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_alu__func__ex, 0));
	items.add(path + "hart decoder_alu_src1", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_alu__src1, 0));
	items.add(path + "hart decoder_alu_src2", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_alu__src2, 0));
	items.add(path + "hart decoder_imm", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_imm, 0));
	items.add(path + "hart decoder_mem_func", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_mem__func, 0));
	items.add(path + "hart decoder_rd_addr", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_rd__addr, 0));
	items.add(path + "hart decoder_reg_src", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_reg__src, 0));
	items.add(path + "hart decoder_branch_cond", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_branch__cond, 0));
	items.add(path + "hart decoder_branch_target", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_branch__target, 0));
	items.add(path + "hart halt", debug_item(p_hart_2e_halt, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "hart mcycle", debug_item(p_hart_2e_mcycle, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "hart pc", debug_item(p_hart_2e_pc, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "hart pc_incr", debug_item(debug_eval_outline, p_hart_2e_pc__incr, 0));
	items.add(path + "hart minstret", debug_item(p_hart_2e_minstret, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "hart branch_taken", debug_item(debug_eval_outline, p_hart_2e_branch__taken, 0));
	items.add(path + "hart branch_target", debug_item(debug_eval_outline, p_hart_2e_branch__target, 0));
	items.add(path + "hart pc_wdata", debug_item(debug_eval_outline, p_hart_2e_pc__wdata, 0));
	items.add(path + "hart registers mem_w_en", debug_item(debug_eval_outline, p_hart_2e_registers_2e_mem__w__en, 0));
	items.add(path + "hart registers mem_w_addr", debug_item(debug_eval_outline, p_hart_2e_registers__mem__w__addr, 0));
	items.add(path + "hart registers mem_w_data", debug_item(debug_eval_outline, p_hart_2e_registers__mem__w__data, 0));
	items.add(path + "hart registers mem_r_data$2", debug_item(debug_eval_outline, p_hart_2e_registers_2e_mem__r__data_24_2, 0));
	items.add(path + "hart registers mem_r_data", debug_item(debug_eval_outline, p_hart_2e_registers_2e_mem__r__data, 0));
	items.add(path + "hart registers mem_r_addr$1", debug_item(debug_eval_outline, p_hart_2e_registers__mem__r__addr_24_1, 0));
	items.add(path + "hart registers mem_r_addr", debug_item(debug_eval_outline, p_hart_2e_registers__mem__r__addr, 0));
	items.add(path + "hart registers hart_clk", debug_item(debug_alias(), p_hart__clk, 0));
	items.add(path + "hart alu eq", debug_item(debug_eval_outline, p_hart_2e_alu_2e_eq, 0));
	items.add(path + "hart alu out", debug_item(p_hart_2e_alu_2e_out, 0, debug_item::DRIVEN_COMB));
	items.add(path + "hart alu op2", debug_item(debug_alias(), p_hart_2e_alu__op2, 0));
	items.add(path + "hart alu op1", debug_item(debug_alias(), p_hart_2e_alu__op1, 0));
	items.add(path + "hart alu func_ex", debug_item(debug_eval_outline, p_hart_2e_alu__func__ex, 0));
	items.add(path + "hart alu func", debug_item(debug_alias(), p_hart_2e_alu__func, 0));
	items.add(path + "hart decoder branch_target", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_branch__target, 0));
	items.add(path + "hart decoder branch_cond", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_branch__cond, 0));
	items.add(path + "hart decoder reg_src", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_reg__src, 0));
	items.add(path + "hart decoder rd_addr", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_rd__addr, 0));
	items.add(path + "hart decoder mem_func", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_mem__func, 0));
	items.add(path + "hart decoder imm", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_imm, 0));
	items.add(path + "hart decoder alu_src2", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_alu__src2, 0));
	items.add(path + "hart decoder alu_src1", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_alu__src1, 0));
	items.add(path + "hart decoder alu_func_ex", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_alu__func__ex, 0));
	items.add(path + "hart decoder alu_func", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_alu__func, 0));
	items.add(path + "hart decoder rs2_addr", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_rs2__addr, 0));
	items.add(path + "hart decoder rs1_addr", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_rs1__addr, 0));
	items.add(path + "hart decoder pc", debug_item(debug_eval_outline, p_hart_2e_decoder__pc, 0));
	items.add(path + "hart decoder insn", debug_item(debug_alias(), p_hart_2e_decoder__insn, 0));
	items.add(path + "hart decoder trap", debug_item(debug_eval_outline, p_hart_2e_decoder_2e_trap, 0));
	items.add(path + "pll rst", debug_item(debug_alias(), p_rst, 0));
	items.add(path + "pll clk", debug_item(debug_alias(), p_clk, 0));
	items.add(path + "pll hart_clk", debug_item(debug_alias(), p_hart__clk, 0));
	items.add(path + "pll hart_rst", debug_item(debug_alias(), p_pll_2e_rs__hart_2e_stage1, 0));
	items.add(path + "pll rs_hart_locked", debug_item(p_pll_2e_rs__hart__locked, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "pll rs_hart stage1", debug_item(p_pll_2e_rs__hart_2e_stage1, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "pll rs_hart stage0", debug_item(p_pll_2e_rs__hart_2e_stage0, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "pll rs_hart async_ff_rst", debug_item(debug_eval_outline, p_pll_2e_rs__hart_2e_async__ff__rst, 0));
	items.add(path + "pll rs_hart async_ff_clk", debug_item(debug_alias(), p_hart__clk, 0));
	items.add(path + "pll rs_hart hart_rst", debug_item(debug_alias(), p_pll_2e_rs__hart_2e_stage1, 0));
	items.add(path + "pll rs_hart hart_clk", debug_item(debug_alias(), p_hart__clk, 0));
	items.add(path + "pll rs_hart rst", debug_item(debug_alias(), p_rst, 0));
	items.add(path + "pll rs_hart locked", debug_item(debug_alias(), p_pll_2e_rs__hart__locked, 0));
	items.add(path + "interconnect_data_bus__wdata", debug_item(debug_eval_outline, p_hart_2e_dbus____wdata, 0));
	items.add(path + "interconnect_data_bus__wmask", debug_item(debug_eval_outline, p_hart_2e_dbus____wmask, 0));
	items.add(path + "interconnect_data_bus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_data__bus____rdata, 0));
	items.add(path + "interconnect_data_bus__rmask", debug_item(debug_eval_outline, p_hart_2e_dbus____rmask, 0));
	items.add(path + "interconnect_data_bus__addr", debug_item(debug_eval_outline, p_hart_2e_dbus____addr, 0));
	items.add(path + "interconnect_data_bus__rdy", debug_item(debug_eval_outline, p_interconnect_2e_data__bus____rdy, 0));
	items.add(path + "interconnect_instruction_bus__wdata", debug_item(debug_alias(), p_ibus____wdata, 0));
	items.add(path + "interconnect_instruction_bus__wmask", debug_item(debug_alias(), p_ibus____wmask, 0));
	items.add(path + "interconnect_instruction_bus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_instruction__bus____rdata, 0));
	items.add(path + "interconnect_instruction_bus__rmask", debug_item(debug_eval_outline, p_hart_2e_ibus____rmask, 0));
	items.add(path + "interconnect_instruction_bus__addr", debug_item(debug_eval_outline, p_hart_2e_ibus____addr, 0));
	items.add(path + "interconnect_instruction_bus__rdy", debug_item(debug_eval_outline, p_interconnect_2e_instruction__bus____rdy, 0));
	items.add(path + "console_console__wdata", debug_item(debug_eval_outline, p_interconnect_2e_console____wdata, 0));
	items.add(path + "console_console__wmask", debug_item(debug_eval_outline, p_interconnect_2e_console____wmask, 0));
	static const value<32> const_p_console__console____rdata = value<32>{0x1u};
	items.add(path + "console_console__rdata", debug_item(const_p_console__console____rdata, 0));
	static const value<1> const_p_console__console____rdy = value<1>{0x1u};
	items.add(path + "console_console__rdy", debug_item(const_p_console__console____rdy, 0));
	items.add(path + "ram_ram__rdata", debug_item(debug_eval_outline, p_ram_2e_ram____rdata, 0));
	items.add(path + "ram_ram__rdy", debug_item(debug_eval_outline, p_ram_2e_ram____rdy, 0));
	items.add(path + "ram_ram__rmask", debug_item(debug_eval_outline, p_interconnect_2e_ram____rmask, 0));
	items.add(path + "ram_ram__wmask", debug_item(debug_eval_outline, p_interconnect_2e_ram____wmask, 0));
	items.add(path + "hart_dbus__wdata", debug_item(debug_eval_outline, p_hart_2e_dbus____wdata, 0));
	items.add(path + "hart_dbus__wmask", debug_item(debug_eval_outline, p_hart_2e_dbus____wmask, 0));
	items.add(path + "hart_dbus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_data__bus____rdata, 0));
	items.add(path + "hart_dbus__rmask", debug_item(debug_eval_outline, p_hart_2e_dbus____rmask, 0));
	items.add(path + "hart_dbus__addr", debug_item(debug_eval_outline, p_hart_2e_dbus____addr, 0));
	items.add(path + "hart_dbus__rdy", debug_item(debug_eval_outline, p_interconnect_2e_data__bus____rdy, 0));
	items.add(path + "hart_ibus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_instruction__bus____rdata, 0));
	items.add(path + "hart_ibus__rmask", debug_item(debug_eval_outline, p_hart_2e_ibus____rmask, 0));
	items.add(path + "hart_ibus__addr", debug_item(debug_eval_outline, p_hart_2e_ibus____addr, 0));
	items.add(path + "hart_ibus__rdy", debug_item(debug_eval_outline, p_interconnect_2e_instruction__bus____rdy, 0));
	items.add(path + "pll_hart_rst", debug_item(debug_alias(), p_pll_2e_rs__hart_2e_stage1, 0));
	items.add(path + "rx_ack", debug_item(p_rx__ack, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "rx_i", debug_item(p_rx__i, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "rp__data", debug_item(p_rp____data, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "hart_clk", debug_item(p_hart__clk, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "clk", debug_item(p_clk, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "rst", debug_item(p_rst, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "ibus__wdata", debug_item(p_ibus____wdata, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "ibus__wmask", debug_item(p_ibus____wmask, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "hart registers mem", debug_item(memory_p_hart_2e_registers_2e_mem, 0));
}

} // namespace cxxrtl_design

extern "C"
cxxrtl_toplevel cxxrtl_design_create() {
	return new _cxxrtl_toplevel { std::unique_ptr<cxxrtl_design::p_top>(new cxxrtl_design::p_top) };
}
