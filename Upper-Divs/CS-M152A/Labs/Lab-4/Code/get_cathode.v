`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    01:31:50 10/31/2021 
// Design Name: 
// Module Name:    get_cathode 
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
module get_cathode(
	// Input
	input [3:0] display_state,
	// Output
	output reg [6:0] cathode
);

	// Get constants
	`include "battleship_definitions.v"

	always @(*) begin
		// Translate state to cathode value
		case(display_state)
			0 : cathode = ST_000;
			1 : cathode = ST_001;
			2 : cathode = ST_010;
			3 : cathode = ST_011;
			4 : cathode = ST_100;
			5 : cathode = ST_101;
		endcase
	end

endmodule
