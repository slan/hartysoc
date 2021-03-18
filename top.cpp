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
	// \hdlname: interconnect ibus__rdy
	// \src: /home/slan/src/hartysoc/toysoc.py:192
	wire<1> p_interconnect_2e_ibus____rdy;
	// \hdlname: cpu halt
	// \init: 0
	// \src: /home/slan/src/hartysoc/toysoc.py:240
	wire<1> p_cpu_2e_halt {0u};
	// \hdlname: cpu pc
	// \init: 4
	// \src: /home/slan/src/hartysoc/toysoc.py:260
	wire<3> p_cpu_2e_pc {0x4u};
	// \src: /home/slan/src/hartysoc/toysoc.py:193
	wire<1> p_interconnect__dbus____rmask;
	// \src: /home/slan/src/hartysoc/toysoc.py:193
	wire<4> p_interconnect__dbus____addr;
	// \src: /home/slan/src/hartysoc/toysoc.py:41
	/*input*/ value<8> p_ram__bus____wdata;
	// \src: /home/slan/src/hartysoc/toysoc.py:41
	/*input*/ value<1> p_ram__bus____wmask;
	// \src: /home/slan/src/hartysoc/toysoc.py:204
	/*input*/ value<1> p_cache__valid;
	// \src: /home/slan/src/hartysoc/toysoc.py:254
	/*input*/ value<1> p_reg__r__addr;
	// \src: /home/slan/src/nmigen/nmigen/hdl/ir.py:526
	/*input*/ value<1> p_clk;
	value<1> prev_p_clk;
	bool posedge_p_clk() const {
		return !prev_p_clk.slice<0>().val() && p_clk.slice<0>().val();
	}
	// \src: /home/slan/src/nmigen/nmigen/hdl/ir.py:526
	/*input*/ value<1> p_rst;
	// \src: /home/slan/src/hartysoc/toysoc.py:193
	/*input*/ value<8> p_dbus____wdata;
	// \src: /home/slan/src/hartysoc/toysoc.py:239
	/*input*/ value<1> p_dbus____wmask;
	// \src: /home/slan/src/hartysoc/toysoc.py:192
	/*input*/ value<8> p_ibus____wdata;
	// \src: /home/slan/src/hartysoc/toysoc.py:238
	/*input*/ value<1> p_ibus____wmask;
	// \hdlname: ram ram_bus__rdata
	// \src: /home/slan/src/hartysoc/toysoc.py:41
	/*outline*/ value<8> p_ram_2e_ram__bus____rdata;
	// \hdlname: ram ram_bus__rdy
	// \src: /home/slan/src/hartysoc/toysoc.py:41
	/*outline*/ value<1> p_ram_2e_ram__bus____rdy;
	// \hdlname: ram mem_r_addr
	// \src: /home/slan/src/hartysoc/toysoc.py:50
	/*outline*/ value<2> p_ram_2e_mem__r__addr;
	// \hdlname: ram mem_r_data
	// \src: /home/slan/src/hartysoc/toysoc.py:50
	/*outline*/ value<8> p_ram_2e_mem__r__data;
	// \hdlname: ram mem_w_en
	// \src: /home/slan/src/hartysoc/toysoc.py:51
	/*outline*/ value<1> p_ram_2e_mem__w__en;
	// \hdlname: ram mem_w_addr
	// \src: /home/slan/src/hartysoc/toysoc.py:51
	/*outline*/ value<2> p_ram_2e_mem__w__addr;
	// \hdlname: ram mem_w_data
	// \src: /home/slan/src/hartysoc/toysoc.py:51
	/*outline*/ value<8> p_ram_2e_mem__w__data;
	// \hdlname: rom rom_bus__rdata
	// \src: /home/slan/src/hartysoc/toysoc.py:18
	/*outline*/ value<8> p_rom_2e_rom__bus____rdata;
	// \hdlname: rom rom_bus__rdy
	// \src: /home/slan/src/hartysoc/toysoc.py:18
	/*outline*/ value<1> p_rom_2e_rom__bus____rdy;
	// \hdlname: rom mem_r_addr
	// \src: /home/slan/src/hartysoc/toysoc.py:27
	/*outline*/ value<2> p_rom_2e_mem__r__addr;
	// \hdlname: rom mem_r_data
	// \src: /home/slan/src/hartysoc/toysoc.py:27
	/*outline*/ value<8> p_rom_2e_mem__r__data;
	// \hdlname: interconnect ibus__rdata
	// \src: /home/slan/src/hartysoc/toysoc.py:192
	/*outline*/ value<8> p_interconnect_2e_ibus____rdata;
	// \hdlname: interconnect dbus__rdata
	// \src: /home/slan/src/hartysoc/toysoc.py:193
	/*outline*/ value<8> p_interconnect_2e_dbus____rdata;
	// \hdlname: interconnect dbus__rdy
	// \src: /home/slan/src/hartysoc/toysoc.py:193
	/*outline*/ value<1> p_interconnect_2e_dbus____rdy;
	// \hdlname: interconnect ram_bus__rmask
	// \src: /home/slan/src/hartysoc/toysoc.py:41
	/*outline*/ value<1> p_interconnect_2e_ram__bus____rmask;
	// \hdlname: interconnect rom_bus__rmask
	// \src: /home/slan/src/hartysoc/toysoc.py:18
	/*outline*/ value<1> p_interconnect_2e_rom__bus____rmask;
	// \hdlname: interconnect ram_bus__addr
	// \src: /home/slan/src/hartysoc/toysoc.py:41
	/*outline*/ value<4> p_interconnect_2e_ram__bus____addr;
	// \hdlname: interconnect rom_bus__addr
	// \src: /home/slan/src/hartysoc/toysoc.py:18
	/*outline*/ value<4> p_interconnect_2e_rom__bus____addr;
	// \hdlname: cpu ibus__addr
	// \src: /home/slan/src/hartysoc/toysoc.py:238
	/*outline*/ value<4> p_cpu_2e_ibus____addr;
	// \hdlname: cpu ibus__rmask
	// \src: /home/slan/src/hartysoc/toysoc.py:238
	/*outline*/ value<1> p_cpu_2e_ibus____rmask;
	// \hdlname: cpu dbus__addr
	// \src: /home/slan/src/hartysoc/toysoc.py:239
	/*outline*/ value<4> p_cpu_2e_dbus____addr;
	// \hdlname: cpu dbus__rmask
	// \src: /home/slan/src/hartysoc/toysoc.py:239
	/*outline*/ value<1> p_cpu_2e_dbus____rmask;
	// \hdlname: cpu reg_w_en
	// \src: /home/slan/src/hartysoc/toysoc.py:255
	/*outline*/ value<1> p_cpu_2e_reg__w__en;
	// \hdlname: cpu reg_w_addr
	// \src: /home/slan/src/hartysoc/toysoc.py:255
	/*outline*/ value<1> p_cpu_2e_reg__w__addr;
	// \hdlname: cpu reg_w_data
	// \src: /home/slan/src/hartysoc/toysoc.py:255
	/*outline*/ value<8> p_cpu_2e_reg__w__data;
	// \hdlname: ram mem
	memory<8> memory_p_ram_2e_mem { 4u,
		memory<8>::init<4> { 0, {
			value<8>{0x12u}, value<8>{0x34u}, value<8>{0x56u}, value<8>{0x78u},
		}},
	};
	// \hdlname: rom mem
	memory<8> memory_p_rom_2e_mem { 4u,
		memory<8>::init<4> { 0, {
			value<8>{0x00u}, value<8>{0x2cu}, value<8>{0x84u}, value<8>{0xffu},
		}},
	};
	// \hdlname: cpu reg
	memory<8> memory_p_cpu_2e_reg { 2u,
		memory<8>::init<2> { 0, {
			value<8>{0x00u}, value<8>{0x00u},
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
	bool posedge_p_clk = this->posedge_p_clk();
	// \hdlname: ram ram_bus__rmask
	// \src: /home/slan/src/hartysoc/toysoc.py:41
	value<1> p_ram_2e_ram__bus____rmask;
	// \hdlname: ram ram_bus__addr
	// \src: /home/slan/src/hartysoc/toysoc.py:41
	value<4> p_ram_2e_ram__bus____addr;
	// \hdlname: ram ram_bus__wmask
	// \src: /home/slan/src/hartysoc/toysoc.py:41
	value<1> p_ram_2e_ram__bus____wmask;
	// \hdlname: ram mem_r_data
	// \src: /home/slan/src/hartysoc/toysoc.py:50
	value<8> p_ram_2e_mem__r__data;
	// \hdlname: ram mem_w_en
	// \src: /home/slan/src/hartysoc/toysoc.py:51
	value<1> p_ram_2e_mem__w__en;
	// \hdlname: rom rom_bus__rmask
	// \src: /home/slan/src/hartysoc/toysoc.py:18
	value<1> p_rom_2e_rom__bus____rmask;
	// \hdlname: rom mem_r_data
	// \src: /home/slan/src/hartysoc/toysoc.py:27
	value<8> p_rom_2e_mem__r__data;
	// \hdlname: interconnect ibus__addr
	// \src: /home/slan/src/hartysoc/toysoc.py:192
	value<4> p_interconnect_2e_ibus____addr;
	// \hdlname: interconnect ibus__rmask
	// \src: /home/slan/src/hartysoc/toysoc.py:192
	value<1> p_interconnect_2e_ibus____rmask;
	// \hdlname: interconnect dbus__addr
	// \src: /home/slan/src/hartysoc/toysoc.py:193
	value<4> p_interconnect_2e_dbus____addr;
	// \hdlname: interconnect dbus__rmask
	// \src: /home/slan/src/hartysoc/toysoc.py:193
	value<1> p_interconnect_2e_dbus____rmask;
	// \hdlname: interconnect dbus__wmask
	// \src: /home/slan/src/hartysoc/toysoc.py:193
	value<1> p_interconnect_2e_dbus____wmask;
	// \hdlname: interconnect cache_valid
	// \src: /home/slan/src/hartysoc/toysoc.py:204
	value<1> p_interconnect_2e_cache__valid;
	// \hdlname: interconnect ram_bus__rdata
	// \src: /home/slan/src/hartysoc/toysoc.py:41
	value<8> p_interconnect_2e_ram__bus____rdata;
	// \hdlname: interconnect rom_bus__rdata
	// \src: /home/slan/src/hartysoc/toysoc.py:18
	value<8> p_interconnect_2e_rom__bus____rdata;
	// \hdlname: interconnect ram_bus__rdy
	// \src: /home/slan/src/hartysoc/toysoc.py:41
	value<1> p_interconnect_2e_ram__bus____rdy;
	// \hdlname: interconnect rom_bus__rdy
	// \src: /home/slan/src/hartysoc/toysoc.py:18
	value<1> p_interconnect_2e_rom__bus____rdy;
	// \src: /home/slan/src/hartysoc/toysoc.py:218
	value<1> i_flatten_5c_interconnect_2e__24_7;
	// \src: /home/slan/src/hartysoc/toysoc.py:221
	value<1> i_flatten_5c_interconnect_2e__24_9;
	// \src: /home/slan/src/hartysoc/toysoc.py:218
	value<1> i_flatten_5c_interconnect_2e__24_23;
	// \src: /home/slan/src/hartysoc/toysoc.py:221
	value<1> i_flatten_5c_interconnect_2e__24_25;
	value<4> i_flatten_5c_interconnect_2e__24_procmux_24_57__Y;
	value<4> i_flatten_5c_interconnect_2e__24_procmux_24_71__Y;
	value<1> i_flatten_5c_interconnect_2e__24_procmux_24_85__Y;
	value<1> i_flatten_5c_interconnect_2e__24_procmux_24_99__Y;
	// \hdlname: cpu ibus__rdata
	// \src: /home/slan/src/hartysoc/toysoc.py:238
	value<8> p_cpu_2e_ibus____rdata;
	// \hdlname: cpu ibus__rdy
	// \src: /home/slan/src/hartysoc/toysoc.py:238
	value<1> p_cpu_2e_ibus____rdy;
	// \hdlname: cpu dbus__rmask
	// \src: /home/slan/src/hartysoc/toysoc.py:239
	value<1> p_cpu_2e_dbus____rmask;
	// \hdlname: cpu dbus__wmask
	// \src: /home/slan/src/hartysoc/toysoc.py:239
	value<1> p_cpu_2e_dbus____wmask;
	// \hdlname: cpu dbus__rdy
	// \src: /home/slan/src/hartysoc/toysoc.py:239
	value<1> p_cpu_2e_dbus____rdy;
	// \hdlname: cpu rst
	// \src: /home/slan/src/nmigen/nmigen/hdl/ir.py:526
	value<1> p_cpu_2e_rst;
	// \hdlname: cpu clk
	// \src: /home/slan/src/nmigen/nmigen/hdl/ir.py:526
	value<1> p_cpu_2e_clk;
	// \hdlname: cpu reg_w_en
	// \src: /home/slan/src/hartysoc/toysoc.py:255
	value<1> p_cpu_2e_reg__w__en;
	value<4> i_flatten_5c_cpu_2e__24_procmux_24_135__Y;
	// connection
	p_interconnect_2e_cache__valid = p_cache__valid;
	// connection
	p_ram_2e_ram__bus____wmask = p_ram__bus____wmask;
	// connection
	p_cpu_2e_dbus____wmask = p_dbus____wmask;
	// connection
	p_interconnect_2e_dbus____wmask = p_dbus____wmask;
	// cells $flatten\cpu.$procmux$168 $flatten\cpu.$3
	p_interconnect_2e_ibus____rmask = (not_u<1>(p_cpu_2e_halt.curr) ? value<1>{0x1u} : value<1>{0u});
	// cells $flatten\cpu.$procmux$166 $flatten\cpu.$5 $flatten\cpu.$7
	p_interconnect_2e_ibus____addr = (not_u<1>(p_cpu_2e_halt.curr) ? pos_u<4>(p_cpu_2e_pc.curr) : value<4>{0u});
	// cells $flatten\interconnect.$procmux$57 $flatten\interconnect.$procmux$54 $flatten\interconnect.$procmux$55_CMP0 $flatten\interconnect.$16
	i_flatten_5c_interconnect_2e__24_procmux_24_57__Y = (p_interconnect_2e_cache__valid ? value<4>{0u} : (eq_uu<1>(p_interconnect_2e_ibus____addr.slice<3,2>().val(), value<2>{0u}) ? value<4>{0u} : pos_u<4>(p_interconnect_2e_ibus____addr.slice<1,0>().val())));
	// cells $flatten\interconnect.$procmux$71 $flatten\interconnect.$procmux$68 $flatten\interconnect.$procmux$69_CMP0 $flatten\interconnect.$14
	i_flatten_5c_interconnect_2e__24_procmux_24_71__Y = (p_interconnect_2e_cache__valid ? value<4>{0u} : (eq_uu<1>(p_interconnect_2e_ibus____addr.slice<3,2>().val(), value<2>{0u}) ? pos_u<4>(p_interconnect_2e_ibus____addr.slice<1,0>().val()) : value<4>{0u}));
	// cells $flatten\interconnect.$procmux$85 $flatten\interconnect.$procmux$82 $flatten\interconnect.$procmux$83_CMP0
	i_flatten_5c_interconnect_2e__24_procmux_24_85__Y = (p_interconnect_2e_cache__valid ? value<1>{0u} : (eq_uu<1>(p_interconnect_2e_ibus____addr.slice<3,2>().val(), value<2>{0u}) ? value<1>{0u} : p_interconnect_2e_ibus____rmask));
	// cells $flatten\interconnect.$procmux$99 $flatten\interconnect.$procmux$96 $flatten\interconnect.$procmux$97_CMP0
	i_flatten_5c_interconnect_2e__24_procmux_24_99__Y = (p_interconnect_2e_cache__valid ? value<1>{0u} : (eq_uu<1>(p_interconnect_2e_ibus____addr.slice<3,2>().val(), value<2>{0u}) ? p_interconnect_2e_ibus____rmask : value<1>{0u}));
	// connection
	p_interconnect_2e_dbus____addr = p_interconnect__dbus____addr.curr;
	// \src: /home/slan/src/hartysoc/toysoc.py:221
	// cell $flatten\interconnect.$26
	i_flatten_5c_interconnect_2e__24_25 = ne_uu<1>(p_interconnect_2e_ibus____addr.slice<3,2>().val(), p_interconnect_2e_dbus____addr.slice<3,2>().val());
	// \src: /home/slan/src/hartysoc/toysoc.py:221
	// cell $flatten\interconnect.$10
	i_flatten_5c_interconnect_2e__24_9 = ne_uu<1>(p_interconnect_2e_ibus____addr.slice<3,2>().val(), p_interconnect_2e_dbus____addr.slice<3,2>().val());
	// connection
	p_interconnect_2e_dbus____rmask = p_interconnect__dbus____rmask.curr;
	// cells $flatten\interconnect.$8 $flatten\interconnect.$6 $flatten\interconnect.$4 $flatten\interconnect.$2
	i_flatten_5c_interconnect_2e__24_7 = and_uu<1>(p_interconnect_2e_ibus____rdy.curr, or_uu<1>(reduce_or<1>(p_interconnect_2e_dbus____rmask), reduce_or<1>(p_interconnect_2e_dbus____wmask)));
	// cells $flatten\interconnect.$procmux$106 $flatten\interconnect.$procmux$104 $flatten\interconnect.$procmux$102 $flatten\interconnect.$procmux$103_CMP0
	p_ram_2e_ram__bus____rmask = (i_flatten_5c_interconnect_2e__24_7 ? (i_flatten_5c_interconnect_2e__24_9 ? (eq_uu<1>(p_interconnect_2e_dbus____addr.slice<3,2>().val(), value<2>{0u}) ? p_interconnect_2e_dbus____rmask : i_flatten_5c_interconnect_2e__24_procmux_24_99__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_99__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_99__Y);
	// cells $flatten\interconnect.$procmux$93 $flatten\interconnect.$procmux$91 $flatten\interconnect.$procmux$89 $flatten\interconnect.$procmux$90_CMP0
	p_rom_2e_rom__bus____rmask = (i_flatten_5c_interconnect_2e__24_7 ? (i_flatten_5c_interconnect_2e__24_9 ? (eq_uu<1>(p_interconnect_2e_dbus____addr.slice<3,2>().val(), value<2>{0u}) ? i_flatten_5c_interconnect_2e__24_procmux_24_85__Y : p_interconnect_2e_dbus____rmask) : i_flatten_5c_interconnect_2e__24_procmux_24_85__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_85__Y);
	// cells $flatten\rom.$procmux$15 $flatten\rom.$7
	p_interconnect_2e_rom__bus____rdy = (reduce_or<1>(p_rom_2e_rom__bus____rmask) ? value<1>{0x1u} : value<1>{0u});
	// cells $flatten\ram.$procmux$9 $flatten\ram.$9 $flatten\ram.$procmux$7 $flatten\ram.$7
	p_interconnect_2e_ram__bus____rdy = (reduce_or<1>(p_ram_2e_ram__bus____wmask) ? value<1>{0x1u} : (reduce_or<1>(p_ram_2e_ram__bus____rmask) ? value<1>{0x1u} : value<1>{0u}));
	// cells $flatten\interconnect.$procmux$43 $flatten\interconnect.$procmux$40 $flatten\interconnect.$procmux$41_CMP0
	p_interconnect_2e_ibus____rdy.next = (p_interconnect_2e_cache__valid ? value<1>{0u} : (eq_uu<1>(p_interconnect_2e_ibus____addr.slice<3,2>().val(), value<2>{0u}) ? p_interconnect_2e_ram__bus____rdy : p_interconnect_2e_rom__bus____rdy));
	// cells $flatten\interconnect.$24 $flatten\interconnect.$22 $flatten\interconnect.$20 $flatten\interconnect.$18
	i_flatten_5c_interconnect_2e__24_23 = and_uu<1>(p_interconnect_2e_ibus____rdy.curr, or_uu<1>(reduce_or<1>(p_interconnect_2e_dbus____rmask), reduce_or<1>(p_interconnect_2e_dbus____wmask)));
	// cells $flatten\interconnect.$procmux$78 $flatten\interconnect.$procmux$76 $flatten\interconnect.$procmux$74 $flatten\interconnect.$procmux$75_CMP0 $flatten\interconnect.$30
	p_ram_2e_ram__bus____addr = (i_flatten_5c_interconnect_2e__24_23 ? (i_flatten_5c_interconnect_2e__24_25 ? (eq_uu<1>(p_interconnect_2e_dbus____addr.slice<3,2>().val(), value<2>{0u}) ? pos_u<4>(p_interconnect_2e_dbus____addr.slice<1,0>().val()) : i_flatten_5c_interconnect_2e__24_procmux_24_71__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_71__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_71__Y);
	// cells \rom.rp $flatten\rom.$procmux$19 $flatten\rom.$3 $flatten\interconnect.$procmux$65 $flatten\interconnect.$procmux$63 $flatten\interconnect.$procmux$61 $flatten\interconnect.$procmux$62_CMP0 $flatten\interconnect.$32
	auto tmp_0 = memory_index((reduce_or<1>(p_rom_2e_rom__bus____rmask) ? (i_flatten_5c_interconnect_2e__24_23 ? (i_flatten_5c_interconnect_2e__24_25 ? (eq_uu<1>(p_interconnect_2e_dbus____addr.slice<3,2>().val(), value<2>{0u}) ? i_flatten_5c_interconnect_2e__24_procmux_24_57__Y : pos_u<4>(p_interconnect_2e_dbus____addr.slice<1,0>().val())) : i_flatten_5c_interconnect_2e__24_procmux_24_57__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_57__Y).slice<1,0>().val() : value<2>{0u}), 0, 4);
	CXXRTL_ASSERT(tmp_0.valid && "out of bounds read");
	if(tmp_0.valid) {
		p_rom_2e_mem__r__data = memory_p_rom_2e_mem[tmp_0.index];
	} else {
		p_rom_2e_mem__r__data = value<8> {};
	}
	// cells \ram.rp $flatten\ram.$procmux$13 $flatten\ram.$3
	auto tmp_1 = memory_index((reduce_or<1>(p_ram_2e_ram__bus____rmask) ? p_ram_2e_ram__bus____addr.slice<1,0>().val() : value<2>{0u}), 0, 4);
	CXXRTL_ASSERT(tmp_1.valid && "out of bounds read");
	if(tmp_1.valid) {
		value<8> tmp_2 = memory_p_ram_2e_mem[tmp_1.index];
		p_ram_2e_mem__r__data = tmp_2;
	} else {
		p_ram_2e_mem__r__data = value<8> {};
	}
	// cells $flatten\rom.$procmux$17 $flatten\rom.$5
	p_interconnect_2e_rom__bus____rdata = (reduce_or<1>(p_rom_2e_rom__bus____rmask) ? p_rom_2e_mem__r__data : value<8>{0u});
	// cells $flatten\ram.$procmux$11 $flatten\ram.$5
	p_interconnect_2e_ram__bus____rdata = (reduce_or<1>(p_ram_2e_ram__bus____rmask) ? p_ram_2e_mem__r__data : value<8>{0u});
	// cells $flatten\interconnect.$procmux$50 $flatten\interconnect.$procmux$47 $flatten\interconnect.$procmux$48_CMP0
	p_cpu_2e_ibus____rdata = (p_interconnect_2e_cache__valid ? value<8>{0u} : (eq_uu<1>(p_interconnect_2e_ibus____addr.slice<3,2>().val(), value<2>{0u}) ? p_interconnect_2e_ram__bus____rdata : p_interconnect_2e_rom__bus____rdata));
	// connection
	p_cpu_2e_ibus____rdy = p_interconnect_2e_ibus____rdy.curr;
	// cells $flatten\cpu.$procmux$149 $flatten\cpu.$13 $flatten\cpu.$procmux$147 $flatten\cpu.$procmux$145 $flatten\cpu.$procmux$146_CMP0
	p_cpu_2e_dbus____rmask = (not_u<1>(p_cpu_2e_halt.curr) ? (p_cpu_2e_ibus____rdy ? (eq_uu<1>(p_cpu_2e_ibus____rdata.slice<2,0>().val(), value<3>{0x4u}) ? value<1>{0x1u} : value<1>{0u}) : value<1>{0u}) : value<1>{0u});
	// connection
	p_interconnect__dbus____rmask.next = p_cpu_2e_dbus____rmask;
	// cells $flatten\interconnect.$procmux$28 $flatten\interconnect.$50 $flatten\interconnect.$48 $flatten\interconnect.$46 $flatten\interconnect.$44 $flatten\interconnect.$procmux$26 $flatten\interconnect.$52 $flatten\interconnect.$procmux$24 $flatten\interconnect.$procmux$25_CMP0
	p_cpu_2e_dbus____rdy = (and_uu<1>(p_interconnect_2e_ibus____rdy.curr, or_uu<1>(reduce_or<1>(p_interconnect_2e_dbus____rmask), reduce_or<1>(p_interconnect_2e_dbus____wmask))) ? (ne_uu<1>(p_interconnect_2e_ibus____addr.slice<3,2>().val(), p_interconnect_2e_dbus____addr.slice<3,2>().val()) ? (eq_uu<1>(p_interconnect_2e_dbus____addr.slice<3,2>().val(), value<2>{0u}) ? p_interconnect_2e_ram__bus____rdy : p_interconnect_2e_rom__bus____rdy) : value<1>{0x1u}) : value<1>{0u});
	// cells $flatten\cpu.$procmux$135 $flatten\cpu.$21 $flatten\cpu.$19 $flatten\cpu.$17
	i_flatten_5c_cpu_2e__24_procmux_24_135__Y = (or_uu<1>(reduce_or<1>(p_cpu_2e_dbus____rmask), reduce_or<1>(p_cpu_2e_dbus____wmask)) ? p_cpu_2e_ibus____rdata.slice<7,4>().val() : value<4>{0u});
	// cells $flatten\cpu.$procmux$143 $flatten\cpu.$15 $flatten\cpu.$procmux$141 $flatten\cpu.$procmux$139 $flatten\cpu.$33 $flatten\cpu.$31 $flatten\cpu.$29 $flatten\cpu.$28 $flatten\cpu.$25 $flatten\cpu.$24 $flatten\cpu.$procmux$137 $flatten\cpu.$35
	p_interconnect__dbus____addr.next = (not_u<1>(p_cpu_2e_halt.curr) ? (p_cpu_2e_ibus____rdy ? (or_uu<1>(and_uu<1>(not_u<1>(reduce_or<1>(p_cpu_2e_dbus____rmask)), not_u<1>(reduce_or<1>(p_cpu_2e_dbus____wmask))), p_cpu_2e_dbus____rdy) ? (reduce_or<1>(p_cpu_2e_dbus____rmask) ? p_cpu_2e_ibus____rdata.slice<7,4>().val() : i_flatten_5c_cpu_2e__24_procmux_24_135__Y) : i_flatten_5c_cpu_2e__24_procmux_24_135__Y) : value<4>{0u}) : value<4>{0u});
	// connection
	p_cpu_2e_rst = p_rst;
	// connection
	p_cpu_2e_clk = p_clk;
	// cells $flatten\cpu.$procmux$133 $flatten\cpu.$39 $flatten\cpu.$procmux$131 $flatten\cpu.$procmux$129 $flatten\cpu.$51 $flatten\cpu.$49 $flatten\cpu.$47 $flatten\cpu.$46 $flatten\cpu.$43 $flatten\cpu.$42 $flatten\cpu.$procmux$127 $flatten\cpu.$53
	p_cpu_2e_reg__w__en = (not_u<1>(p_cpu_2e_halt.curr) ? (p_cpu_2e_ibus____rdy ? (or_uu<1>(and_uu<1>(not_u<1>(reduce_or<1>(p_cpu_2e_dbus____rmask)), not_u<1>(reduce_or<1>(p_cpu_2e_dbus____wmask))), p_cpu_2e_dbus____rdy) ? (reduce_or<1>(p_cpu_2e_dbus____rmask) ? value<1>{0x1u} : value<1>{0u}) : value<1>{0u}) : value<1>{0u}) : value<1>{0u});
	// cells $flatten\ram.$procmux$1 $flatten\ram.$15
	p_ram_2e_mem__w__en = (reduce_or<1>(p_ram_2e_ram__bus____wmask) ? value<1>{0x1u} : value<1>{0u});
	// cells $flatten\cpu.$procdff$171 $flatten\cpu.$procmux$164 $flatten\cpu.$procmux$162 $flatten\cpu.$9 $flatten\cpu.$procmux$160 $flatten\cpu.$procmux$158 $flatten\cpu.$procmux$159_CMP0
	if (posedge_p_clk) {
		p_cpu_2e_halt.next = (p_cpu_2e_rst ? value<1>{0u} : (not_u<1>(p_cpu_2e_halt.curr) ? (p_cpu_2e_ibus____rdy ? (eq_uu<1>(p_cpu_2e_ibus____rdata, value<8>{0xffu}) ? value<1>{0x1u} : p_cpu_2e_halt.curr) : p_cpu_2e_halt.curr) : p_cpu_2e_halt.curr));
	}
	// cells $flatten\cpu.$procdff$170 $flatten\cpu.$procmux$114 $flatten\cpu.$procmux$112 $flatten\cpu.$77 $flatten\cpu.$procmux$110 $flatten\cpu.$procmux$108 $flatten\cpu.$89 $flatten\cpu.$87 $flatten\cpu.$85 $flatten\cpu.$84 $flatten\cpu.$81 $flatten\cpu.$80 $flatten\cpu.$92
	if (posedge_p_clk) {
		p_cpu_2e_pc.next = (p_cpu_2e_rst ? value<3>{0x4u} : (not_u<1>(p_cpu_2e_halt.curr) ? (p_cpu_2e_ibus____rdy ? (or_uu<1>(and_uu<1>(not_u<1>(reduce_or<1>(p_cpu_2e_dbus____rmask)), not_u<1>(reduce_or<1>(p_cpu_2e_dbus____wmask))), p_cpu_2e_dbus____rdy) ? add_uu<4>(p_cpu_2e_pc.curr, value<1>{0x1u}).slice<2,0>().val() : p_cpu_2e_pc.curr) : p_cpu_2e_pc.curr) : p_cpu_2e_pc.curr));
	}
	// cells \cpu.reg_wp $flatten\cpu.$procmux$125 $flatten\cpu.$57 $flatten\cpu.$procmux$123 $flatten\cpu.$procmux$121 $flatten\cpu.$69 $flatten\cpu.$67 $flatten\cpu.$65 $flatten\cpu.$64 $flatten\cpu.$61 $flatten\cpu.$60 $flatten\cpu.$procmux$119 $flatten\cpu.$71 $flatten\interconnect.$procmux$36 $flatten\interconnect.$40 $flatten\interconnect.$38 $flatten\interconnect.$36 $flatten\interconnect.$34 $flatten\interconnect.$procmux$34 $flatten\interconnect.$42 $flatten\interconnect.$procmux$32 $flatten\interconnect.$procmux$33_CMP0 $flatten\cpu.$procmux$117 $flatten\cpu.$73 $flatten\cpu.$75 $flatten\cpu.$procmux$156 $flatten\cpu.$11 $flatten\cpu.$procmux$154 $flatten\cpu.$procmux$151 $flatten\cpu.$procmux$152_CMP0 $flatten\cpu.$procmux$153_CMP0
	if (posedge_p_clk) {
		auto tmp_3 = memory_index((not_u<1>(p_cpu_2e_halt.curr) ? (p_cpu_2e_ibus____rdy ? (eq_uu<1>(p_cpu_2e_ibus____rdata.slice<2,0>().val(), value<3>{0x4u}) ? p_cpu_2e_ibus____rdata.slice<3>().val() : (eq_uu<1>(p_cpu_2e_ibus____rdata.slice<2,0>().val(), value<3>{0x1u}) ? p_cpu_2e_ibus____rdata.slice<3>().val() : value<1>{0u})) : value<1>{0u}) : value<1>{0u}), 0, 2);
		CXXRTL_ASSERT(tmp_3.valid && "out of bounds write");
		if (tmp_3.valid) {
			memory_p_cpu_2e_reg.update(tmp_3.index, (not_u<1>(p_cpu_2e_halt.curr) ? (p_cpu_2e_ibus____rdy ? (or_uu<1>(and_uu<1>(not_u<1>(reduce_or<1>(p_cpu_2e_dbus____rmask)), not_u<1>(reduce_or<1>(p_cpu_2e_dbus____wmask))), p_cpu_2e_dbus____rdy) ? (reduce_or<1>(p_cpu_2e_dbus____rmask) ? (and_uu<1>(p_interconnect_2e_ibus____rdy.curr, or_uu<1>(reduce_or<1>(p_interconnect_2e_dbus____rmask), reduce_or<1>(p_interconnect_2e_dbus____wmask))) ? (ne_uu<1>(p_interconnect_2e_ibus____addr.slice<3,2>().val(), p_interconnect_2e_dbus____addr.slice<3,2>().val()) ? (eq_uu<1>(p_interconnect_2e_dbus____addr.slice<3,2>().val(), value<2>{0u}) ? p_interconnect_2e_ram__bus____rdata : p_interconnect_2e_rom__bus____rdata) : value<8>{0u}) : value<8>{0u}) : (reduce_or<1>(p_cpu_2e_dbus____wmask) ? value<8>{0u} : pos_u<8>(p_cpu_2e_ibus____rdata.slice<7,4>().val()))) : value<8>{0u}) : value<8>{0u}) : value<8>{0u}), p_cpu_2e_reg__w__en.repeat<8>().val(), 0);
		}
	}
	// cells \ram.wp $flatten\ram.$procmux$3 $flatten\ram.$13 $flatten\ram.$procmux$5 $flatten\ram.$11
	if (posedge_p_clk) {
		auto tmp_4 = memory_index((reduce_or<1>(p_ram_2e_ram__bus____wmask) ? p_ram_2e_ram__bus____addr.slice<1,0>().val() : value<2>{0u}), 0, 4);
		CXXRTL_ASSERT(tmp_4.valid && "out of bounds write");
		if (tmp_4.valid) {
			memory_p_ram_2e_mem.update(tmp_4.index, (reduce_or<1>(p_ram_2e_ram__bus____wmask) ? p_ram__bus____wdata : value<8>{0u}), p_ram_2e_mem__w__en.repeat<8>().val(), 0);
		}
	}
	return converged;
}

bool p_top::commit() {
	bool changed = false;
	if (p_interconnect_2e_ibus____rdy.commit()) changed = true;
	if (p_cpu_2e_halt.commit()) changed = true;
	if (p_cpu_2e_pc.commit()) changed = true;
	if (p_interconnect__dbus____rmask.commit()) changed = true;
	if (p_interconnect__dbus____addr.commit()) changed = true;
	prev_p_clk = p_clk;
	if (memory_p_ram_2e_mem.commit()) changed = true;
	if (memory_p_cpu_2e_reg.commit()) changed = true;
	return changed;
}

void p_top::debug_eval() {
	// \src: /home/slan/src/hartysoc/toysoc.py:218
	value<1> i_flatten_5c_interconnect_2e__24_7;
	// \src: /home/slan/src/hartysoc/toysoc.py:221
	value<1> i_flatten_5c_interconnect_2e__24_9;
	// \src: /home/slan/src/hartysoc/toysoc.py:218
	value<1> i_flatten_5c_interconnect_2e__24_23;
	// \src: /home/slan/src/hartysoc/toysoc.py:221
	value<1> i_flatten_5c_interconnect_2e__24_25;
	value<4> i_flatten_5c_interconnect_2e__24_procmux_24_57__Y;
	value<4> i_flatten_5c_interconnect_2e__24_procmux_24_71__Y;
	value<1> i_flatten_5c_interconnect_2e__24_procmux_24_85__Y;
	value<1> i_flatten_5c_interconnect_2e__24_procmux_24_99__Y;
	value<4> i_flatten_5c_cpu_2e__24_procmux_24_135__Y;
	// cells $flatten\cpu.$procmux$168 $flatten\cpu.$3
	p_cpu_2e_ibus____rmask = (not_u<1>(p_cpu_2e_halt.curr) ? value<1>{0x1u} : value<1>{0u});
	// cells $flatten\cpu.$procmux$166 $flatten\cpu.$5 $flatten\cpu.$7
	p_cpu_2e_ibus____addr = (not_u<1>(p_cpu_2e_halt.curr) ? pos_u<4>(p_cpu_2e_pc.curr) : value<4>{0u});
	// cells $flatten\interconnect.$procmux$57 $flatten\interconnect.$procmux$54 $flatten\interconnect.$procmux$55_CMP0 $flatten\interconnect.$16
	i_flatten_5c_interconnect_2e__24_procmux_24_57__Y = (p_cache__valid ? value<4>{0u} : (eq_uu<1>(p_cpu_2e_ibus____addr.slice<3,2>().val(), value<2>{0u}) ? value<4>{0u} : pos_u<4>(p_cpu_2e_ibus____addr.slice<1,0>().val())));
	// cells $flatten\interconnect.$procmux$71 $flatten\interconnect.$procmux$68 $flatten\interconnect.$procmux$69_CMP0 $flatten\interconnect.$14
	i_flatten_5c_interconnect_2e__24_procmux_24_71__Y = (p_cache__valid ? value<4>{0u} : (eq_uu<1>(p_cpu_2e_ibus____addr.slice<3,2>().val(), value<2>{0u}) ? pos_u<4>(p_cpu_2e_ibus____addr.slice<1,0>().val()) : value<4>{0u}));
	// cells $flatten\interconnect.$procmux$85 $flatten\interconnect.$procmux$82 $flatten\interconnect.$procmux$83_CMP0
	i_flatten_5c_interconnect_2e__24_procmux_24_85__Y = (p_cache__valid ? value<1>{0u} : (eq_uu<1>(p_cpu_2e_ibus____addr.slice<3,2>().val(), value<2>{0u}) ? value<1>{0u} : p_cpu_2e_ibus____rmask));
	// cells $flatten\interconnect.$procmux$99 $flatten\interconnect.$procmux$96 $flatten\interconnect.$procmux$97_CMP0
	i_flatten_5c_interconnect_2e__24_procmux_24_99__Y = (p_cache__valid ? value<1>{0u} : (eq_uu<1>(p_cpu_2e_ibus____addr.slice<3,2>().val(), value<2>{0u}) ? p_cpu_2e_ibus____rmask : value<1>{0u}));
	// \src: /home/slan/src/hartysoc/toysoc.py:221
	// cell $flatten\interconnect.$26
	i_flatten_5c_interconnect_2e__24_25 = ne_uu<1>(p_cpu_2e_ibus____addr.slice<3,2>().val(), p_cpu_2e_dbus____addr.slice<3,2>().val());
	// \src: /home/slan/src/hartysoc/toysoc.py:221
	// cell $flatten\interconnect.$10
	i_flatten_5c_interconnect_2e__24_9 = ne_uu<1>(p_cpu_2e_ibus____addr.slice<3,2>().val(), p_cpu_2e_dbus____addr.slice<3,2>().val());
	// cells $flatten\interconnect.$8 $flatten\interconnect.$6 $flatten\interconnect.$4 $flatten\interconnect.$2
	i_flatten_5c_interconnect_2e__24_7 = and_uu<1>(p_interconnect_2e_ibus____rdy.curr, or_uu<1>(reduce_or<1>(p_cpu_2e_dbus____rmask), reduce_or<1>(p_dbus____wmask)));
	// cells $flatten\interconnect.$procmux$106 $flatten\interconnect.$procmux$104 $flatten\interconnect.$procmux$102 $flatten\interconnect.$procmux$103_CMP0
	p_interconnect_2e_ram__bus____rmask = (i_flatten_5c_interconnect_2e__24_7 ? (i_flatten_5c_interconnect_2e__24_9 ? (eq_uu<1>(p_cpu_2e_dbus____addr.slice<3,2>().val(), value<2>{0u}) ? p_cpu_2e_dbus____rmask : i_flatten_5c_interconnect_2e__24_procmux_24_99__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_99__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_99__Y);
	// cells $flatten\interconnect.$procmux$93 $flatten\interconnect.$procmux$91 $flatten\interconnect.$procmux$89 $flatten\interconnect.$procmux$90_CMP0
	p_interconnect_2e_rom__bus____rmask = (i_flatten_5c_interconnect_2e__24_7 ? (i_flatten_5c_interconnect_2e__24_9 ? (eq_uu<1>(p_cpu_2e_dbus____addr.slice<3,2>().val(), value<2>{0u}) ? i_flatten_5c_interconnect_2e__24_procmux_24_85__Y : p_cpu_2e_dbus____rmask) : i_flatten_5c_interconnect_2e__24_procmux_24_85__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_85__Y);
	// cells $flatten\rom.$procmux$15 $flatten\rom.$7
	p_rom_2e_rom__bus____rdy = (reduce_or<1>(p_interconnect_2e_rom__bus____rmask) ? value<1>{0x1u} : value<1>{0u});
	// cells $flatten\ram.$procmux$9 $flatten\ram.$9 $flatten\ram.$procmux$7 $flatten\ram.$7
	p_ram_2e_ram__bus____rdy = (reduce_or<1>(p_ram__bus____wmask) ? value<1>{0x1u} : (reduce_or<1>(p_interconnect_2e_ram__bus____rmask) ? value<1>{0x1u} : value<1>{0u}));
	// cells $flatten\interconnect.$24 $flatten\interconnect.$22 $flatten\interconnect.$20 $flatten\interconnect.$18
	i_flatten_5c_interconnect_2e__24_23 = and_uu<1>(p_interconnect_2e_ibus____rdy.curr, or_uu<1>(reduce_or<1>(p_cpu_2e_dbus____rmask), reduce_or<1>(p_dbus____wmask)));
	// cells $flatten\interconnect.$procmux$65 $flatten\interconnect.$procmux$63 $flatten\interconnect.$procmux$61 $flatten\interconnect.$procmux$62_CMP0 $flatten\interconnect.$32
	p_interconnect_2e_rom__bus____addr = (i_flatten_5c_interconnect_2e__24_23 ? (i_flatten_5c_interconnect_2e__24_25 ? (eq_uu<1>(p_cpu_2e_dbus____addr.slice<3,2>().val(), value<2>{0u}) ? i_flatten_5c_interconnect_2e__24_procmux_24_57__Y : pos_u<4>(p_cpu_2e_dbus____addr.slice<1,0>().val())) : i_flatten_5c_interconnect_2e__24_procmux_24_57__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_57__Y);
	// cells $flatten\interconnect.$procmux$78 $flatten\interconnect.$procmux$76 $flatten\interconnect.$procmux$74 $flatten\interconnect.$procmux$75_CMP0 $flatten\interconnect.$30
	p_interconnect_2e_ram__bus____addr = (i_flatten_5c_interconnect_2e__24_23 ? (i_flatten_5c_interconnect_2e__24_25 ? (eq_uu<1>(p_cpu_2e_dbus____addr.slice<3,2>().val(), value<2>{0u}) ? pos_u<4>(p_cpu_2e_dbus____addr.slice<1,0>().val()) : i_flatten_5c_interconnect_2e__24_procmux_24_71__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_71__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_71__Y);
	// cells $flatten\rom.$procmux$19 $flatten\rom.$3 $flatten\interconnect.$procmux$65 $flatten\interconnect.$procmux$63 $flatten\interconnect.$procmux$61 $flatten\interconnect.$procmux$62_CMP0 $flatten\interconnect.$32
	p_rom_2e_mem__r__addr = (reduce_or<1>(p_interconnect_2e_rom__bus____rmask) ? p_interconnect_2e_rom__bus____addr.slice<1,0>().val() : value<2>{0u});
	// cells $flatten\ram.$procmux$13 $flatten\ram.$3
	p_ram_2e_mem__r__addr = (reduce_or<1>(p_interconnect_2e_ram__bus____rmask) ? p_interconnect_2e_ram__bus____addr.slice<1,0>().val() : value<2>{0u});
	// cells \rom.rp $flatten\rom.$procmux$19 $flatten\rom.$3 $flatten\interconnect.$procmux$65 $flatten\interconnect.$procmux$63 $flatten\interconnect.$procmux$61 $flatten\interconnect.$procmux$62_CMP0 $flatten\interconnect.$32
	auto tmp_5 = memory_index((reduce_or<1>(p_rom_2e_rom__bus____rmask) ? (i_flatten_5c_interconnect_2e__24_23 ? (i_flatten_5c_interconnect_2e__24_25 ? (eq_uu<1>(p_interconnect_2e_dbus____addr.slice<3,2>().val(), value<2>{0u}) ? i_flatten_5c_interconnect_2e__24_procmux_24_57__Y : pos_u<4>(p_interconnect_2e_dbus____addr.slice<1,0>().val())) : i_flatten_5c_interconnect_2e__24_procmux_24_57__Y) : i_flatten_5c_interconnect_2e__24_procmux_24_57__Y).slice<1,0>().val() : value<2>{0u}), 0, 4);
	CXXRTL_ASSERT(tmp_5.valid && "out of bounds read");
	if(tmp_5.valid) {
		p_rom_2e_mem__r__data = memory_p_rom_2e_mem[tmp_5.index];
	} else {
		p_rom_2e_mem__r__data = value<8> {};
	}
	// cells \ram.rp $flatten\ram.$procmux$13 $flatten\ram.$3
	auto tmp_6 = memory_index((reduce_or<1>(p_ram_2e_ram__bus____rmask) ? p_ram_2e_ram__bus____addr.slice<1,0>().val() : value<2>{0u}), 0, 4);
	CXXRTL_ASSERT(tmp_6.valid && "out of bounds read");
	if(tmp_6.valid) {
		value<8> tmp_7 = memory_p_ram_2e_mem[tmp_6.index];
		p_ram_2e_mem__r__data = tmp_7;
	} else {
		p_ram_2e_mem__r__data = value<8> {};
	}
	// cells $flatten\rom.$procmux$17 $flatten\rom.$5
	p_rom_2e_rom__bus____rdata = (reduce_or<1>(p_interconnect_2e_rom__bus____rmask) ? p_rom_2e_mem__r__data : value<8>{0u});
	// cells $flatten\ram.$procmux$11 $flatten\ram.$5
	p_ram_2e_ram__bus____rdata = (reduce_or<1>(p_interconnect_2e_ram__bus____rmask) ? p_ram_2e_mem__r__data : value<8>{0u});
	// cells $flatten\interconnect.$procmux$50 $flatten\interconnect.$procmux$47 $flatten\interconnect.$procmux$48_CMP0
	p_interconnect_2e_ibus____rdata = (p_cache__valid ? value<8>{0u} : (eq_uu<1>(p_cpu_2e_ibus____addr.slice<3,2>().val(), value<2>{0u}) ? p_ram_2e_ram__bus____rdata : p_rom_2e_rom__bus____rdata));
	// cells $flatten\cpu.$procmux$149 $flatten\cpu.$13 $flatten\cpu.$procmux$147 $flatten\cpu.$procmux$145 $flatten\cpu.$procmux$146_CMP0
	p_cpu_2e_dbus____rmask = (not_u<1>(p_cpu_2e_halt.curr) ? (p_interconnect_2e_ibus____rdy.curr ? (eq_uu<1>(p_interconnect_2e_ibus____rdata.slice<2,0>().val(), value<3>{0x4u}) ? value<1>{0x1u} : value<1>{0u}) : value<1>{0u}) : value<1>{0u});
	// cells $flatten\interconnect.$procmux$28 $flatten\interconnect.$50 $flatten\interconnect.$48 $flatten\interconnect.$46 $flatten\interconnect.$44 $flatten\interconnect.$procmux$26 $flatten\interconnect.$52 $flatten\interconnect.$procmux$24 $flatten\interconnect.$procmux$25_CMP0
	p_interconnect_2e_dbus____rdy = (and_uu<1>(p_interconnect_2e_ibus____rdy.curr, or_uu<1>(reduce_or<1>(p_cpu_2e_dbus____rmask), reduce_or<1>(p_dbus____wmask))) ? (ne_uu<1>(p_cpu_2e_ibus____addr.slice<3,2>().val(), p_cpu_2e_dbus____addr.slice<3,2>().val()) ? (eq_uu<1>(p_cpu_2e_dbus____addr.slice<3,2>().val(), value<2>{0u}) ? p_ram_2e_ram__bus____rdy : p_rom_2e_rom__bus____rdy) : value<1>{0x1u}) : value<1>{0u});
	// cells $flatten\cpu.$procmux$135 $flatten\cpu.$21 $flatten\cpu.$19 $flatten\cpu.$17
	i_flatten_5c_cpu_2e__24_procmux_24_135__Y = (or_uu<1>(reduce_or<1>(p_cpu_2e_dbus____rmask), reduce_or<1>(p_dbus____wmask)) ? p_interconnect_2e_ibus____rdata.slice<7,4>().val() : value<4>{0u});
	// cells $flatten\cpu.$procmux$143 $flatten\cpu.$15 $flatten\cpu.$procmux$141 $flatten\cpu.$procmux$139 $flatten\cpu.$33 $flatten\cpu.$31 $flatten\cpu.$29 $flatten\cpu.$28 $flatten\cpu.$25 $flatten\cpu.$24 $flatten\cpu.$procmux$137 $flatten\cpu.$35
	p_cpu_2e_dbus____addr = (not_u<1>(p_cpu_2e_halt.curr) ? (p_interconnect_2e_ibus____rdy.curr ? (or_uu<1>(and_uu<1>(not_u<1>(reduce_or<1>(p_cpu_2e_dbus____rmask)), not_u<1>(reduce_or<1>(p_dbus____wmask))), p_interconnect_2e_dbus____rdy) ? (reduce_or<1>(p_cpu_2e_dbus____rmask) ? p_interconnect_2e_ibus____rdata.slice<7,4>().val() : i_flatten_5c_cpu_2e__24_procmux_24_135__Y) : i_flatten_5c_cpu_2e__24_procmux_24_135__Y) : value<4>{0u}) : value<4>{0u});
	// cells $flatten\interconnect.$procmux$36 $flatten\interconnect.$40 $flatten\interconnect.$38 $flatten\interconnect.$36 $flatten\interconnect.$34 $flatten\interconnect.$procmux$34 $flatten\interconnect.$42 $flatten\interconnect.$procmux$32 $flatten\interconnect.$procmux$33_CMP0
	p_interconnect_2e_dbus____rdata = (and_uu<1>(p_interconnect_2e_ibus____rdy.curr, or_uu<1>(reduce_or<1>(p_cpu_2e_dbus____rmask), reduce_or<1>(p_dbus____wmask))) ? (ne_uu<1>(p_cpu_2e_ibus____addr.slice<3,2>().val(), p_cpu_2e_dbus____addr.slice<3,2>().val()) ? (eq_uu<1>(p_cpu_2e_dbus____addr.slice<3,2>().val(), value<2>{0u}) ? p_ram_2e_ram__bus____rdata : p_rom_2e_rom__bus____rdata) : value<8>{0u}) : value<8>{0u});
	// cells $flatten\cpu.$procmux$156 $flatten\cpu.$11 $flatten\cpu.$procmux$154 $flatten\cpu.$procmux$151 $flatten\cpu.$procmux$152_CMP0 $flatten\cpu.$procmux$153_CMP0
	p_cpu_2e_reg__w__addr = (not_u<1>(p_cpu_2e_halt.curr) ? (p_interconnect_2e_ibus____rdy.curr ? (eq_uu<1>(p_interconnect_2e_ibus____rdata.slice<2,0>().val(), value<3>{0x4u}) ? p_interconnect_2e_ibus____rdata.slice<3>().val() : (eq_uu<1>(p_interconnect_2e_ibus____rdata.slice<2,0>().val(), value<3>{0x1u}) ? p_interconnect_2e_ibus____rdata.slice<3>().val() : value<1>{0u})) : value<1>{0u}) : value<1>{0u});
	// cells $flatten\cpu.$procmux$133 $flatten\cpu.$39 $flatten\cpu.$procmux$131 $flatten\cpu.$procmux$129 $flatten\cpu.$51 $flatten\cpu.$49 $flatten\cpu.$47 $flatten\cpu.$46 $flatten\cpu.$43 $flatten\cpu.$42 $flatten\cpu.$procmux$127 $flatten\cpu.$53
	p_cpu_2e_reg__w__en = (not_u<1>(p_cpu_2e_halt.curr) ? (p_interconnect_2e_ibus____rdy.curr ? (or_uu<1>(and_uu<1>(not_u<1>(reduce_or<1>(p_cpu_2e_dbus____rmask)), not_u<1>(reduce_or<1>(p_dbus____wmask))), p_interconnect_2e_dbus____rdy) ? (reduce_or<1>(p_cpu_2e_dbus____rmask) ? value<1>{0x1u} : value<1>{0u}) : value<1>{0u}) : value<1>{0u}) : value<1>{0u});
	// cells $flatten\cpu.$procmux$125 $flatten\cpu.$57 $flatten\cpu.$procmux$123 $flatten\cpu.$procmux$121 $flatten\cpu.$69 $flatten\cpu.$67 $flatten\cpu.$65 $flatten\cpu.$64 $flatten\cpu.$61 $flatten\cpu.$60 $flatten\cpu.$procmux$119 $flatten\cpu.$71 $flatten\interconnect.$procmux$36 $flatten\interconnect.$40 $flatten\interconnect.$38 $flatten\interconnect.$36 $flatten\interconnect.$34 $flatten\interconnect.$procmux$34 $flatten\interconnect.$42 $flatten\interconnect.$procmux$32 $flatten\interconnect.$procmux$33_CMP0 $flatten\cpu.$procmux$117 $flatten\cpu.$73 $flatten\cpu.$75
	p_cpu_2e_reg__w__data = (not_u<1>(p_cpu_2e_halt.curr) ? (p_interconnect_2e_ibus____rdy.curr ? (or_uu<1>(and_uu<1>(not_u<1>(reduce_or<1>(p_cpu_2e_dbus____rmask)), not_u<1>(reduce_or<1>(p_dbus____wmask))), p_interconnect_2e_dbus____rdy) ? (reduce_or<1>(p_cpu_2e_dbus____rmask) ? p_interconnect_2e_dbus____rdata : (reduce_or<1>(p_dbus____wmask) ? value<8>{0u} : pos_u<8>(p_interconnect_2e_ibus____rdata.slice<7,4>().val()))) : value<8>{0u}) : value<8>{0u}) : value<8>{0u});
	// cells $flatten\ram.$procmux$5 $flatten\ram.$11
	p_ram_2e_mem__w__addr = (reduce_or<1>(p_ram__bus____wmask) ? p_interconnect_2e_ram__bus____addr.slice<1,0>().val() : value<2>{0u});
	// cells $flatten\ram.$procmux$3 $flatten\ram.$13
	p_ram_2e_mem__w__data = (reduce_or<1>(p_ram__bus____wmask) ? p_ram__bus____wdata : value<8>{0u});
	// cells $flatten\ram.$procmux$1 $flatten\ram.$15
	p_ram_2e_mem__w__en = (reduce_or<1>(p_ram__bus____wmask) ? value<1>{0x1u} : value<1>{0u});
}

CXXRTL_EXTREMELY_COLD
void p_top::debug_info(debug_items &items, std::string path) {
	assert(path.empty() || path[path.size() - 1] == ' ');
	items.add(path + "ram clk", debug_item(debug_alias(), p_clk, 0));
	items.add(path + "ram ram_bus__rmask", debug_item(debug_eval_outline, p_interconnect_2e_ram__bus____rmask, 0));
	items.add(path + "ram ram_bus__addr", debug_item(debug_eval_outline, p_interconnect_2e_ram__bus____addr, 0));
	items.add(path + "ram ram_bus__rdata", debug_item(debug_eval_outline, p_ram_2e_ram__bus____rdata, 0));
	items.add(path + "ram ram_bus__rdy", debug_item(debug_eval_outline, p_ram_2e_ram__bus____rdy, 0));
	items.add(path + "ram ram_bus__wmask", debug_item(debug_alias(), p_ram__bus____wmask, 0));
	items.add(path + "ram ram_bus__wdata", debug_item(debug_alias(), p_ram__bus____wdata, 0));
	items.add(path + "ram mem_r_addr", debug_item(debug_eval_outline, p_ram_2e_mem__r__addr, 0));
	items.add(path + "ram mem_r_data", debug_item(debug_eval_outline, p_ram_2e_mem__r__data, 0));
	items.add(path + "ram mem_w_en", debug_item(debug_eval_outline, p_ram_2e_mem__w__en, 0));
	items.add(path + "ram mem_w_addr", debug_item(debug_eval_outline, p_ram_2e_mem__w__addr, 0));
	items.add(path + "ram mem_w_data", debug_item(debug_eval_outline, p_ram_2e_mem__w__data, 0));
	items.add(path + "rom rom_bus__rmask", debug_item(debug_eval_outline, p_interconnect_2e_rom__bus____rmask, 0));
	items.add(path + "rom rom_bus__addr", debug_item(debug_eval_outline, p_interconnect_2e_rom__bus____addr, 0));
	items.add(path + "rom rom_bus__rdata", debug_item(debug_eval_outline, p_rom_2e_rom__bus____rdata, 0));
	items.add(path + "rom rom_bus__rdy", debug_item(debug_eval_outline, p_rom_2e_rom__bus____rdy, 0));
	items.add(path + "rom mem_r_addr", debug_item(debug_eval_outline, p_rom_2e_mem__r__addr, 0));
	items.add(path + "rom mem_r_data", debug_item(debug_eval_outline, p_rom_2e_mem__r__data, 0));
	items.add(path + "interconnect ibus__addr", debug_item(debug_eval_outline, p_cpu_2e_ibus____addr, 0));
	items.add(path + "interconnect ibus__rmask", debug_item(debug_eval_outline, p_cpu_2e_ibus____rmask, 0));
	items.add(path + "interconnect ibus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_ibus____rdata, 0));
	items.add(path + "interconnect ibus__rdy", debug_item(p_interconnect_2e_ibus____rdy, 0, debug_item::DRIVEN_COMB));
	items.add(path + "interconnect dbus__addr", debug_item(debug_eval_outline, p_cpu_2e_dbus____addr, 0));
	items.add(path + "interconnect dbus__rmask", debug_item(debug_eval_outline, p_cpu_2e_dbus____rmask, 0));
	items.add(path + "interconnect dbus__wmask", debug_item(debug_alias(), p_dbus____wmask, 0));
	items.add(path + "interconnect dbus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_dbus____rdata, 0));
	items.add(path + "interconnect dbus__rdy", debug_item(debug_eval_outline, p_interconnect_2e_dbus____rdy, 0));
	items.add(path + "interconnect cache_valid", debug_item(debug_alias(), p_cache__valid, 0));
	items.add(path + "interconnect ram_bus__rmask", debug_item(debug_eval_outline, p_interconnect_2e_ram__bus____rmask, 0));
	items.add(path + "interconnect rom_bus__rmask", debug_item(debug_eval_outline, p_interconnect_2e_rom__bus____rmask, 0));
	items.add(path + "interconnect ram_bus__addr", debug_item(debug_eval_outline, p_interconnect_2e_ram__bus____addr, 0));
	items.add(path + "interconnect rom_bus__addr", debug_item(debug_eval_outline, p_interconnect_2e_rom__bus____addr, 0));
	items.add(path + "interconnect ram_bus__rdata", debug_item(debug_eval_outline, p_ram_2e_ram__bus____rdata, 0));
	items.add(path + "interconnect rom_bus__rdata", debug_item(debug_eval_outline, p_rom_2e_rom__bus____rdata, 0));
	items.add(path + "interconnect ram_bus__rdy", debug_item(debug_eval_outline, p_ram_2e_ram__bus____rdy, 0));
	items.add(path + "interconnect rom_bus__rdy", debug_item(debug_eval_outline, p_rom_2e_rom__bus____rdy, 0));
	items.add(path + "cpu ibus__addr", debug_item(debug_eval_outline, p_cpu_2e_ibus____addr, 0));
	items.add(path + "cpu ibus__rmask", debug_item(debug_eval_outline, p_cpu_2e_ibus____rmask, 0));
	items.add(path + "cpu ibus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_ibus____rdata, 0));
	items.add(path + "cpu ibus__rdy", debug_item(debug_alias(), p_interconnect_2e_ibus____rdy, 0));
	items.add(path + "cpu dbus__addr", debug_item(debug_eval_outline, p_cpu_2e_dbus____addr, 0));
	items.add(path + "cpu dbus__rmask", debug_item(debug_eval_outline, p_cpu_2e_dbus____rmask, 0));
	items.add(path + "cpu dbus__wmask", debug_item(debug_alias(), p_dbus____wmask, 0));
	items.add(path + "cpu dbus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_dbus____rdata, 0));
	items.add(path + "cpu dbus__rdy", debug_item(debug_eval_outline, p_interconnect_2e_dbus____rdy, 0));
	items.add(path + "cpu rst", debug_item(debug_alias(), p_rst, 0));
	items.add(path + "cpu clk", debug_item(debug_alias(), p_clk, 0));
	items.add(path + "cpu reg_w_en", debug_item(debug_eval_outline, p_cpu_2e_reg__w__en, 0));
	items.add(path + "cpu reg_w_addr", debug_item(debug_eval_outline, p_cpu_2e_reg__w__addr, 0));
	items.add(path + "cpu reg_w_data", debug_item(debug_eval_outline, p_cpu_2e_reg__w__data, 0));
	items.add(path + "cpu halt", debug_item(p_cpu_2e_halt, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "cpu pc", debug_item(p_cpu_2e_pc, 0, debug_item::DRIVEN_SYNC));
	items.add(path + "interconnect_rom_bus__rdy", debug_item(debug_eval_outline, p_rom_2e_rom__bus____rdy, 0));
	items.add(path + "interconnect_ram_bus__rdy", debug_item(debug_eval_outline, p_ram_2e_ram__bus____rdy, 0));
	items.add(path + "interconnect_rom_bus__rdata", debug_item(debug_eval_outline, p_rom_2e_rom__bus____rdata, 0));
	items.add(path + "interconnect_ram_bus__rdata", debug_item(debug_eval_outline, p_ram_2e_ram__bus____rdata, 0));
	items.add(path + "interconnect_rom_bus__addr", debug_item(debug_eval_outline, p_interconnect_2e_rom__bus____addr, 0));
	items.add(path + "interconnect_ram_bus__addr", debug_item(debug_eval_outline, p_interconnect_2e_ram__bus____addr, 0));
	items.add(path + "interconnect_rom_bus__rmask", debug_item(debug_eval_outline, p_interconnect_2e_rom__bus____rmask, 0));
	items.add(path + "interconnect_ram_bus__rmask", debug_item(debug_eval_outline, p_interconnect_2e_ram__bus____rmask, 0));
	items.add(path + "interconnect_dbus__rdy", debug_item(debug_eval_outline, p_interconnect_2e_dbus____rdy, 0));
	items.add(path + "interconnect_dbus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_dbus____rdata, 0));
	items.add(path + "interconnect_dbus__wmask", debug_item(debug_alias(), p_dbus____wmask, 0));
	items.add(path + "interconnect_dbus__rmask", debug_item(debug_eval_outline, p_cpu_2e_dbus____rmask, 0));
	items.add(path + "interconnect_dbus__addr", debug_item(debug_eval_outline, p_cpu_2e_dbus____addr, 0));
	items.add(path + "interconnect_ibus__rdy", debug_item(debug_alias(), p_interconnect_2e_ibus____rdy, 0));
	items.add(path + "interconnect_ibus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_ibus____rdata, 0));
	items.add(path + "interconnect_ibus__rmask", debug_item(debug_eval_outline, p_cpu_2e_ibus____rmask, 0));
	items.add(path + "interconnect_ibus__addr", debug_item(debug_eval_outline, p_cpu_2e_ibus____addr, 0));
	items.add(path + "cpu_dbus__rdy", debug_item(debug_eval_outline, p_interconnect_2e_dbus____rdy, 0));
	items.add(path + "cpu_dbus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_dbus____rdata, 0));
	items.add(path + "cpu_dbus__rmask", debug_item(debug_eval_outline, p_cpu_2e_dbus____rmask, 0));
	items.add(path + "cpu_dbus__addr", debug_item(debug_eval_outline, p_cpu_2e_dbus____addr, 0));
	items.add(path + "cpu_ibus__rdy", debug_item(debug_alias(), p_interconnect_2e_ibus____rdy, 0));
	items.add(path + "cpu_ibus__rdata", debug_item(debug_eval_outline, p_interconnect_2e_ibus____rdata, 0));
	items.add(path + "cpu_ibus__rmask", debug_item(debug_eval_outline, p_cpu_2e_ibus____rmask, 0));
	items.add(path + "cpu_ibus__addr", debug_item(debug_eval_outline, p_cpu_2e_ibus____addr, 0));
	items.add(path + "ram_bus__wdata", debug_item(p_ram__bus____wdata, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "ram_bus__wmask", debug_item(p_ram__bus____wmask, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "cache_valid", debug_item(p_cache__valid, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "reg_r_addr", debug_item(p_reg__r__addr, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "clk", debug_item(p_clk, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "rst", debug_item(p_rst, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "dbus__wdata", debug_item(p_dbus____wdata, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "dbus__wmask", debug_item(p_dbus____wmask, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "ibus__wdata", debug_item(p_ibus____wdata, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "ibus__wmask", debug_item(p_ibus____wmask, 0, debug_item::INPUT|debug_item::UNDRIVEN));
	items.add(path + "ram mem", debug_item(memory_p_ram_2e_mem, 0));
	items.add(path + "rom mem", debug_item(memory_p_rom_2e_mem, 0));
	items.add(path + "cpu reg", debug_item(memory_p_cpu_2e_reg, 0));
}

} // namespace cxxrtl_design

extern "C"
cxxrtl_toplevel cxxrtl_design_create() {
	return new _cxxrtl_toplevel { std::unique_ptr<cxxrtl_design::p_top>(new cxxrtl_design::p_top) };
}
