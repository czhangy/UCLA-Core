`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   02:45:10 10/31/2021
// Design Name:   stopwatch
// Module Name:   /home/ise/lab-3/stopwatch_tb.v
// Project Name:  lab-3
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: stopwatch
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module stopwatch_tb;

	// Inputs
	reg clk;
	reg SEL;
	reg ADJ;
	reg RESET;
	reg PAUSE;

	// Outputs
	wire [6:0] cathode;
	wire [3:0] anode;

	// Instantiate the Unit Under Test (UUT)
	stopwatch uut (
		.clk(clk), 
		.SEL(SEL), 
		.ADJ(ADJ), 
		.RESET(RESET), 
		.PAUSE(PAUSE), 
		.cathode(cathode), 
		.anode(anode)
	);
	
	// Global clock
	always #5 clk = ~clk;

	initial begin
		// Initialize Inputs
		clk = 0;
		SEL = 0;
		ADJ = 0;
		RESET = 0;
		PAUSE = 0;

		// Wait 100 ns for global reset to finish
		#100;
        
		// Reset
		RESET = 1;
		// Wait 1ms for the debouncer to allow the signal through
		#1100000;
		RESET = 0;
		#1100000;
		
		$display("Reset complete, beginning stopwatch");
		
		// Test one second default
		#500000000;
		
		$display("-------------------------------------------");
		$display("Normal mode test complete\nResults:");
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		
		// Test ADJ, SEL = 0
		ADJ = 1;
		#1100000;
		#500000000;
		
		$display("-------------------------------------------");
		$display("Minute adjustment mode test complete\nResults:");
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		
		// Test ADJ, SEL = 1
		SEL = 1;
		#1100000;
		#500000000;
		
		$display("-------------------------------------------");
		$display("Second adjustment mode test complete\nResults:");
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		
		// Test ADJ = 0
		ADJ = 0;
		#1100000;
		#1000000000;
		
		$display("-------------------------------------------");
		$display("ADJ off mode test complete\nResults:");
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		
		// Test PAUSE
		PAUSE = 1;
		#1100000;
		#100000000;
		PAUSE = 0;
		#1100000;
		
		$display("-------------------------------------------");
		$display("Pause test complete\nResults:");
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		
		// Test Unpause
		PAUSE = 1;
		#1100000;
		#100000000;
		PAUSE = 0;
		#1100000;
		
		$display("-------------------------------------------");
		$display("Unpause test complete\nResults:");
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		
		// Test RESET
		RESET = 1;
		#1100000;
		
		$display("-------------------------------------------");
		$display("Reset test complete\nResults:");
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;
		$display("%b: %b", anode, cathode);
		#4000000;

	end
      
endmodule
