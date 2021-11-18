`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:50:16 10/31/2021 
// Design Name: 
// Module Name:    ssd 
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
module ssd(
	// Inputs
	input clk_fst,
	input [3:0] p1_state,
	input [3:0] p2_state,
	// Outputs
	output reg [6:0] cathode,
	output reg [3:0] anode
);

	// Get constants
	`include "battleship_definitions.v"

	// Cathode values
	wire [6:0] p1_cathode;
	wire [6:0] p2_cathode;

	// Digit counter
	reg [1:0] digit = 0;
	
	// Translate states to cathodes
	get_cathode p1 (.display_state(p1_state), .cathode(p1_cathode));
	get_cathode p2 (.display_state(p2_state), .cathode(p2_cathode));

	// Display on SSD
	always @(posedge clk_fst) begin
		// Handle P1's left digit
		if (digit == 0) begin
			digit <= digit + 1;
			cathode <= ST_OFF;
			anode <= P1_LEFT;
		// Handle P1's right digit
		end else if (digit == 1) begin
			digit <= digit + 1;
			cathode <= p1_cathode;
			anode <= P1_RIGHT;
		// Handle P2's left digit
		end else if (digit == 2) begin
			digit <= digit + 1;
			cathode <= ST_OFF;
			anode <= P2_LEFT;
		// Handle P2's right digit
		end else if (digit == 3) begin
			digit <= 0;
			cathode <= p2_cathode;
			anode <= P2_RIGHT;
		end
	end

endmodule
