`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    08:43:55 10/27/2021 
// Design Name: 
// Module Name:    clock_divider 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module clock_divider(clk, rst, clk_2hz, clk_1hz, clk_fst, clk_blnk);

	// Inputs
	input clk; // 10 ns
	input rst;
	
	// Outputs
	output reg clk_2hz; // 50,000,000 clk cycles
	output reg clk_1hz; // 100,000,000 clk cycles
	output reg clk_fst; // 400,000 clk cycles (250 Hz)
	output reg clk_blnk; // 75,000,000 clk cycles (1.5 Hz)
	
	// Counters
	reg [24:0] counter_2hz = 0; // counts to 25,000,000
	reg [25:0] counter_1hz = 0; // counts to 50,000,000 
	reg [17:0] counter_fst = 0; // counts to 200,000
	reg [25:0] counter_blnk = 0; // counts to 37,500,000
	
	always @(posedge clk or posedge rst) begin
		// Check reset
		if (rst) begin
			// Reset clock signals
			clk_2hz <= 0;
			clk_1hz <= 0;
			clk_fst <= 0;
			clk_blnk <= 0;
			// Reset counters
			counter_2hz <= 0;
			counter_1hz <= 0;
			counter_fst <= 0;
			counter_blnk <= 0;
		end else begin
			// Increment counters
			counter_2hz <= counter_2hz + 1;
			counter_1hz <= counter_1hz + 1;
			counter_fst <= counter_fst + 1;
			counter_blnk <= counter_blnk + 1;
			// Check counters
			if (counter_2hz >= 25000000) begin
				counter_2hz <= 0;
				clk_2hz <= ~clk_2hz;
			end
			if (counter_1hz >= 50000000) begin
				counter_1hz <= 0;
				clk_1hz = ~clk_1hz;
			end
			if (counter_fst >= 200000) begin
				counter_fst <= 0;
				clk_fst = ~clk_fst;
			end
			if (counter_blnk >= 37500000) begin
				counter_blnk <= 0;
				clk_blnk = ~clk_blnk;
			end
		end
	end

endmodule
