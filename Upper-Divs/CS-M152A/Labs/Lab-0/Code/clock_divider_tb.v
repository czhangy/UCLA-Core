`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   14:12:37 09/30/2021
// Design Name:   clock_divider
// Module Name:   C:/Users/152/Downloads/lab-0/clock_divider_tb.v
// Project Name:  lab-0-counter
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: clock_divider
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module clock_divider_tb;

	// Inputs
	reg clk;
	reg rst;

	// Outputs
	wire led;

	// Instantiate the Unit Under Test (UUT)
	clock_divider uut (
		.clk(clk), 
		.rst(rst), 
		.led(led)
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

