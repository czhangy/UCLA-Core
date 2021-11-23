`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    12:49:03 11/16/2021 
// Design Name: 
// Module Name:    vga 
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
module vga(
	// Inputs
	input clk_vga,
	input rst,
	input integer p1_board,
	input integer p2_board,
	// Outputs
	output hsync,
	output vsync,
	output reg [7:0] rgb
);

	// Get constants
	`include "battleship_definitions.v"

	// Registers for storing the horizontal & vertical counters
	reg [10:0] 	h_counter;
	reg [9:0] 	v_counter;
	
	// Store position
	integer row;
	integer col;

	always @(posedge clk_vga or posedge rst) begin
		// Reset condition
		if (rst) begin
			h_counter <= 0;
			v_counter <= 0;
		end else begin
			// Keep counting until the end of the line
			if (h_counter < HPIXELS - 1)
				h_counter <= h_counter + 1;
			else begin
				h_counter <= 0;
				// Check for vertical wrap-around
				if (v_counter < VLINES - 1)
					v_counter <= v_counter + 1;
				else
					v_counter <= 0;
			end
		end
	end

	// Generate sync pulses (active low)
	assign hsync = (h_counter < HPULSE) ? 0 : 1;
	assign vsync = (v_counter < VPULSE) ? 0 : 1;

	always @(*) begin
		// Set row
		if (v_counter < HEADER)
			row = OUT_OF_BOUNDS;
		else if (v_counter <= HEADER + BLOCK_SIZE)
			row = 0;
		else if (v_counter <= HEADER + BLOCK_SIZE * 2)
			row = 1;
		else if (v_counter <= HEADER + BLOCK_SIZE * 3)
			row = 2;
		else if (v_counter <= HEADER + BLOCK_SIZE * 4)
			row = 3;
		else if (v_counter <= HEADER + BLOCK_SIZE * 5)
			row = 4;
		else if (v_counter <= HEADER + BLOCK_SIZE * 6)
			row = 5;
		else if (v_counter <= HEADER + BLOCK_SIZE * 7)
			row = 6;
		else if (v_counter <= HEADER + BLOCK_SIZE * 8)
			row = 7;
		else if (v_counter <= HEADER + BLOCK_SIZE * 9)
			row = 8;
		else if (v_counter <= HEADER + BLOCK_SIZE * 10)
			row = 9;
		else
			row = OUT_OF_BOUNDS;
		// Set column
		if (h_counter < MARGIN)
			col = OUT_OF_BOUNDS;
		else if (h_counter <= MARGIN + BLOCK_SIZE)
			col = 0;
		else if (h_counter <= MARGIN + BLOCK_SIZE * 2)
			col = 1;
		else if (h_counter <= MARGIN + BLOCK_SIZE * 3)
			col = 2;
		else if (h_counter <= MARGIN + BLOCK_SIZE * 4)
			col = 3;
		else if (h_counter <= MARGIN + BLOCK_SIZE * 5)
			col = 4;
		else if (h_counter <= MARGIN + BLOCK_SIZE * 6)
			col = 5;
		else if (h_counter <= MARGIN + BLOCK_SIZE * 7)
			col = 6;
		else if (h_counter <= MARGIN + BLOCK_SIZE * 8)
			col = 7;
		else if (h_counter <= MARGIN + BLOCK_SIZE * 9)
			col = 8;
		else if (h_counter <= MARGIN + BLOCK_SIZE * 10)
			col = 9; 
		else
			col = OUT_OF_BOUNDS;

		// Check if we're within vertical active video range
		if (v_counter >= VBP && v_counter < VFP) begin
			if (v_counter < HEADER)
				rgb = BLANK;
			else begin
				if (h_counter >= HBP && h_counter < HBP + 640)
					rgb = SHIP;
				// Outside active horizontal range so display black
				else
					rgb = 0;
			end
		// Outside active vertical range so display black
		end else
			rgb = 0;
	end
	
endmodule
