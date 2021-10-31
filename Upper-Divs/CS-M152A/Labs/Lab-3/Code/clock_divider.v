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
module clock_divider(
	// Input
	input clk, // 100MHz
	input rst,
	// Output
	output reg clk_2hz, // 50,000,000 clock cycles
	output reg clk_1hz, // 100,000,000 clock cycles
	output reg clk_fst, // 400,000 clock cycles (250 Hz)
	output reg clk_blnk // 75,000,000 clock cycles (1.5 Hz)
);

	// Get constants
	`include "stopwatch_definitions.v"
	
	// Counters
	reg [31:0] counter_2hz = 0; // counts to 25,000,000
	reg [31:0] counter_1hz = 0; // counts to 50,000,000 
	reg [31:0] counter_fst = 0; // counts to 200,000
	reg [31:0] counter_blnk = 0; // counts to 37,500,000
	
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
			if (counter_2hz >= TWO_HZ_COUNT) begin
				counter_2hz <= 0;
				clk_2hz <= ~clk_2hz;
			end
			if (counter_1hz >= ONE_HZ_COUNT) begin
				counter_1hz <= 0;
				clk_1hz = ~clk_1hz;
			end
			if (counter_fst >= FAST_COUNT) begin
				counter_fst <= 0;
				clk_fst = ~clk_fst;
			end
			if (counter_blnk >= BLINK_COUNT) begin
				counter_blnk <= 0;
				clk_blnk = ~clk_blnk;
			end
		end
	end

endmodule
