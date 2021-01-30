module testbench();

reg clk=0;
reg rst=1;

top top(.rst_0__io(rst), .clk100_0__io(clk));

always #5 clk=~clk;

endmodule
