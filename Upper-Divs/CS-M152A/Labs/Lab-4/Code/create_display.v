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
	input [6:0] p1_cathode,
	input [6:0] p2_cathode,
	// Outputs
	output reg [6:0] cathode,
	output reg [3:0] anode
);

	// Get constants
	`include "battleship_definitions.v"

	// Specify which digit
	reg [1:0] digit = 0;
	
	always @(posedge clk_fst) begin
		// Handle P1's left digit
		if (digit == 0) begin
			digit <= digit + 1'b1;
			cathode <= ST_OFF;
			anode <= P1_LEFT;
		// Handle P1's right digit
		end else if (digit == 1) begin
			digit <= digit + 1'b1;
			cathode <= p1_cathode;
			anode <= P1_RIGHT;
		// Handle P2's left digit
		end else if (digit == 2) begin
			digit <= digit + 1'b1;
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
