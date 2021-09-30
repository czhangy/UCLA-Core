`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   13:59:32 09/28/2021
// Design Name:   counter
// Module Name:   C:/Users/152/Desktop/lab-0-counter/counter_tb.v
// Project Name:  lab-0-counter
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: counter
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module counter_tb;

	// Inputs
	reg clk;
	reg rst;

	// Outputs
	wire [3:0] a;

	// Instantiate the Unit Under Test (UUT)
	counter uut (
		.clk(clk), 
		.rst(rst), 
		.a(a)
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

