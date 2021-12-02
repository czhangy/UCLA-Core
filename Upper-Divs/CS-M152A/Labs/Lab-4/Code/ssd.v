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
	input clk_ssd,
	input [1:0] turn,
	// Outputs
	output reg [6:0] cathode,
	output reg [3:0] anode
);

    // Get constants
    `include "battleship_definitions.v"

	// SSD cathodes
	parameter CAT_P = 7'b0001100;
	parameter CAT_1 = 7'b1111001;
	parameter CAT_2 = 7'b0100100;
	parameter CAT_OFF = 7'b1111111;

	// SSD anodes
	parameter AN_1 = 4'b0111;
	parameter AN_2 = 4'b1011;
	parameter AN_3 = 4'b1101;
	parameter AN_4 = 4'b1110;

	// SSD digits
	parameter DIGIT_1 = 0;
	parameter DIGIT_2 = 1;
	parameter DIGIT_3 = 2;
	parameter DIGIT_4 = 3;

	// Digit counter
	reg [1:0] digit = 0;

	// Display on SSD
	always @(posedge clk_ssd) begin
		if (digit == DIGIT_1) begin
			cathode <= CAT_OFF;
			anode <= AN_1;
			digit <= DIGIT_2;
		end else if (digit == DIGIT_2) begin
			cathode <= CAT_P;
			anode <= AN_2;
			digit <= DIGIT_3;
		end else if (digit == DIGIT_3) begin
			cathode <= (turn == PLAYER_1) ? CAT_1 : CAT_2;
			anode <= AN_3;
			digit <= DIGIT_4;
		end else if (digit == DIGIT_4) begin
			cathode <= CAT_OFF;
			anode <= AN_4;
			digit <= DIGIT_1;
		end
	end

endmodule
