module rvfi_wrapper(
	input         clock,
	input         reset,
    `RVFI_OUTPUTS
);

(* keep *) wire [31:0] imem_data;

// `rvformal_rand_reg [31:0] imem_data_randval;

// assign imem_data = imem_data_randval;

\riscv.Hart dut (
    .clk(clock),
    .rst(reset),

    .imem_data(imem_data),

    .rvfi__valid(rvfi_valid),
    .rvfi__order(rvfi_order),
    .rvfi__insn(rvfi_insn),
    .rvfi__trap(rvfi_trap),
    .rvfi__halt(rvfi_halt),
    .rvfi__intr(rvfi_intr),
    .rvfi__mode(rvfi_mode),
    .rvfi__ixl(rvfi_ixl),
    .rvfi__rs1_addr(rvfi_rs1_addr),
    .rvfi__rs2_addr(rvfi_rs2_addr),
    .rvfi__rs1_rdata(rvfi_rs1_rdata),
    .rvfi__rs2_rdata(rvfi_rs2_rdata),
    .rvfi__rd_addr(rvfi_rd_addr),
    .rvfi__rd_wdata(rvfi_rd_wdata),
    .rvfi__pc_rdata(rvfi_pc_rdata),
    .rvfi__pc_wdata(rvfi_pc_wdata),
    .rvfi__mem_addr(rvfi_mem_addr),
    .rvfi__mem_rmask(rvfi_mem_rmask),
    .rvfi__mem_wmask(rvfi_mem_wmask),
    .rvfi__mem_rdata(rvfi_mem_rdata),
    .rvfi__mem_wdata(rvfi_mem_wdata),
);

endmodule