`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    00:15:37 10/31/2021 
// Design Name: 
// Module Name:    counter 
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
module counter(
	// Inputs
	input clk_1hz,
	input clk_2hz,
	input sel,
	input adj,
	input rst,
	input pause,
	// Outputs
	output reg minutes_tens,
	output reg minutes_ones,
	output reg seconds_tens,
	output reg seconds_ones
);
	
	// Get constants
	`include "stopwatch_definitions.v"
	
	// Handle pause state
	reg is_paused = 0;
	
	always @(posedge rst) begin
		// Reset clock
		minutes_tens <= 0;
		minutes_ones <= 0;
		seconds_tens <= 0;
		seconds_ones <= 0;
	end
	
	always @(posedge pause) begin
		// Pause the clock
		is_paused = ~is_paused;
	end
	
	// Fast clock increase
	always @(posedge clk_2hz) begin
		if (ADJ && ~pause) begin
			// Make the minutes update faster
			if (SEL) begin
				// Update 1s place
				if (minutes_ones == MAX_ONES) begin
					minutes_ones <= 0;
					// Update 10s place
					if (minutes_tens == MAX_TENS) begin
						minutes_tens <= 0;
					end else begin
						minutes_tens <= minutes_tens + 1;
					end
				end else begin
					minutes_ones <= minutes_ones + 1;
				end
			// Make the seconds update faster
			end else begin
				// Update 1s place
				if (seconds_ones == MAX_ONES) begin
					seconds_ones <= 0;
					// Update 10s place
					if (seconds_tens == MAX_TENS) begin
						seconds_tens <= 0;
					end else begin
						seconds_tens <= seconds_tens + 1;
					end
				end else begin
					seconds_ones <= seconds_ones + 1;
				end
			end
		end
	end

	// Regular clock increase
	always @(posedge clk_1hz) begin
		if (~ADJ && ~pause) begin
			// Update seconds (1s place)
			if (seconds_ones == MAX_ONES) begin
				seconds_ones = 0;
				// Update seconds (10s place)
				if (seconds_tens == MAX_TENS) begin
					seconds_tens = 0;
					// Update minutes (1s place)
					if (minutes_ones == MAX_ONES) begin
						minutes_ones = 0;
						// Update minutes (10s place)
						if (minutes_tens == MAX_TENS) begin
							minutes_tens = 0;
						end else begin
							minutes_tens = minutes_tens + 1;
						end
					end else begin
						minutes_ones = minutes_ones + 1;
					end
				end else begin
					seconds_tens = seconds_tens + 1;
				end
			end else begin
				seconds_ones = seconds_ones + 1;
			end
		end
	end

endmodule