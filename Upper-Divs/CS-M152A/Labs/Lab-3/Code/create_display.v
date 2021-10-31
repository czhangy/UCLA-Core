`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:50:16 10/31/2021 
// Design Name: 
// Module Name:    create_display 
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
module create_display(
	// Inputs
	input clk_fst,
	input clk_blnk,
	input sel,
	input adj,
	input [6:0] minutes_tens_cathode,
	input [6:0] minutes_ones_cathode,
	input [6:0] seconds_tens_cathode,
	input [6:0] seconds_ones_cathode,
	// Outputs
	output reg [6:0] cathode,
	output reg [3:0] anode
);

	// Get constants
	`include "stopwatch_definitions.v"

	// Specify which digit
	reg digit = 0;
	
	always @(posedge clk_fst) begin
		// Handle minutes tens place
		if (digit == 0) begin
			digit <= digit + 1;
			cathode <= minutes_tens_cathode;
			anode <= MINUTES_TENS_DIGIT;
			// Check for blinking
			if (adj && ~sel && clk_blnk) begin
				cathode <= ST_OFF;
			end
		// Handle minutes ones place
		end else if (digit == 1) begin
			digit <= digit + 1;
			cathode <= minutes_ones_cathode;
			anode = MINUTES_ONES_DIGIT;
			// Check for blinking
			if (adj && ~sel && clk_blnk) begin
				cathode <= ST_OFF;
			end
		// Handle seconds tens place
		end else if (digit == 2) begin
			digit <= digit + 1;
			cathode <= seconds_tens_cathode;
			anode = SECONDS_TENS_DIGIT;
			// Check for blinking
			if (adj && sel && clk_blnk) begin
				cathode <= ST_OFF;
			end
		// Handle seconds ones place
		end else if (digit == 3) begin
			digit <= 0;
			cathode <= seconds_ones_cathode;
			anode = SECONDS_ONES_DIGIT;
			// Check for blinking
			if (adj && sel && clk_blnk) begin
				cathode <= ST_OFF;
			end
		end
	end

endmodule
