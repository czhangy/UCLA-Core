`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   14:33:21 09/28/2021
// Design Name:   old_counter
// Module Name:   C:/Users/152/Desktop/lab-0-counter/old_counter_tb.v
// Project Name:  lab-0-counter
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: old_counter
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module old_counter_tb;

	// Inputs
	reg clk;
	reg rst;

	// Outputs
	wire a0;
	wire a1;
	wire a2;
	wire a3;

	// Instantiate the Unit Under Test (UUT)
	old_counter uut (
		.clk(clk), 
		.rst(rst), 
		.a0(a0), 
		.a1(a1),
		.a2(a2),
		.a3(a3)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		rst = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Add stimulus here

	end
      
endmodule

