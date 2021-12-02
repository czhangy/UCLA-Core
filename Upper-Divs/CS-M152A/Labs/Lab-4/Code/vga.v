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
	input [11:0] active_ship,
	input [35:0] ship_locs,
	input [5:0] ship_bitmap,
	input [24:0] miss_bitmap,
	input [1:0] mode,
	// Outputs
	output hsync,
	output vsync,
	output reg [7:0] rgb
);

	// Get constants
	`include "battleship_definitions.v"

	// VGA constants
	parameter HPIXELS = 800;
	parameter VLINES = 521;
	parameter HPULSE = 96;
	parameter VPULSE = 2;
	parameter HBP = 144;
	parameter HFP = 784;
	parameter VBP = 31;
	parameter VFP = 511;

	// Board bounds
	parameter OUT_OF_BOUNDS = 5;
	parameter HEADER = 80;
	parameter MARGIN = 120;
	parameter BLOCK_SIZE = 80;
	parameter TOP_BORDER = 0;
	parameter LEFT_BORDER = 0;
	parameter BOTTOM_BORDER = BLOCK_SIZE - 1;
	parameter RIGHT_BORDER = BLOCK_SIZE - 1;

	// Board colors
	parameter BLACK = 0;
	parameter BLANK = 8'b01011111; 		    // Light blue
	parameter SHIP = 8'b10010010; 	        // Gray
	parameter ACTIVE = 8'b00010100; 	    // Green
	parameter OVERLAP = 8'b11100000; 	    // Red
	parameter HIT = 8'b11100000; 			// Red
	parameter MISS = 8'b11111100; 			// Yellow

	// Registers for storing the horizontal & vertical counters
	reg [10:0] h_counter;
	reg [9:0] v_counter;
	
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
		if (v_counter < VBP + HEADER)
			row = OUT_OF_BOUNDS;
		else if (v_counter <= VBP + HEADER + BLOCK_SIZE)
			row = 0;
		else if (v_counter <= VBP + HEADER + BLOCK_SIZE * 2)
			row = 1;
		else if (v_counter <= VBP + HEADER + BLOCK_SIZE * 3)
			row = 2;
		else if (v_counter <= VBP + HEADER + BLOCK_SIZE * 4)
			row = 3;
		else if (v_counter <= VBP + HEADER + BLOCK_SIZE * 5)
			row = 4;
		else
			row = OUT_OF_BOUNDS;
		// Set column
		if (h_counter < HBP + MARGIN)
			col = OUT_OF_BOUNDS;
		else if (h_counter <= HBP + MARGIN + BLOCK_SIZE)
			col = 0;
		else if (h_counter <= HBP + MARGIN + BLOCK_SIZE * 2)
			col = 1;
		else if (h_counter <= HBP + MARGIN + BLOCK_SIZE * 3)
			col = 2;
		else if (h_counter <= HBP + MARGIN + BLOCK_SIZE * 4)
			col = 3;
		else if (h_counter <= HBP + MARGIN + BLOCK_SIZE * 5)
			col = 4;
		else
			col = OUT_OF_BOUNDS;

		// Check if we're within vertical active video range
		if (v_counter >= VBP && v_counter < VFP) begin
			if (row == OUT_OF_BOUNDS)
				rgb = 0;
			else begin
				// Check if we're within horizontal active video range
				if (h_counter >= HBP && h_counter < HFP) begin
					if (mode == WIN)
						rgb = ACTIVE;
					else if (col == OUT_OF_BOUNDS)
						rgb = BLACK;
					// Grid lines
					else if ((v_counter - HEADER - VBP) % BLOCK_SIZE == TOP_BORDER ||
							(v_counter - HEADER - VBP) % BLOCK_SIZE == BOTTOM_BORDER ||
							(h_counter - MARGIN - HBP) % BLOCK_SIZE == LEFT_BORDER ||
							(h_counter - MARGIN - HBP) % BLOCK_SIZE == RIGHT_BORDER)
						rgb = BLACK;
					// Board spaces
					else begin
						if (col == ship_locs[2:0] && row == ship_locs[5:3]) begin
							if (((col == active_ship[2:0] && row == active_ship[5:3]) ||
								(col == active_ship[8:6] && row == active_ship[11:9])) &&
								mode == PLACEMENT)
								rgb = OVERLAP;
							else if (ship_bitmap[5] == 0)
								rgb = HIT;
							else if (col == active_ship[8:6] && row == active_ship[11:9])
								rgb = ACTIVE;
							else if (ship_bitmap[5] == 1)
								rgb = (mode == PLACEMENT) ? SHIP : BLANK;
						end else if (col == ship_locs[8:6] && row == ship_locs[11:9]) begin
							if (((col == active_ship[2:0] && row == active_ship[5:3]) ||
								(col == active_ship[8:6] && row == active_ship[11:9])) &&
								mode == PLACEMENT)
								rgb = OVERLAP;
							else if (ship_bitmap[4] == 0)
								rgb = HIT;
							else if (col == active_ship[8:6] && row == active_ship[11:9])
								rgb = ACTIVE;
							else if (ship_bitmap[4] == 1)
								rgb = (mode == PLACEMENT) ? SHIP : BLANK;
						end else if (col == ship_locs[14:12] && row == ship_locs[17:15]) begin
							if (((col == active_ship[2:0] && row == active_ship[5:3]) ||
								(col == active_ship[8:6] && row == active_ship[11:9])) &&
								mode == PLACEMENT)
								rgb = OVERLAP;
							else if (ship_bitmap[3] == 0)
								rgb = HIT;
							else if (col == active_ship[8:6] && row == active_ship[11:9])
								rgb = ACTIVE;
							else if (ship_bitmap[3] == 1)
								rgb = (mode == PLACEMENT) ? SHIP : BLANK;
						end else if (col == ship_locs[20:18] && row == ship_locs[23:21]) begin
							if (((col == active_ship[2:0] && row == active_ship[5:3]) ||
								(col == active_ship[8:6] && row == active_ship[11:9])) &&
								mode == PLACEMENT)
								rgb = OVERLAP;
							else if (ship_bitmap[2] == 0)
								rgb = HIT;
							else if (col == active_ship[8:6] && row == active_ship[11:9])
								rgb = ACTIVE;
							else if (ship_bitmap[2] == 1)
								rgb = (mode == PLACEMENT) ? SHIP : BLANK;
						end else if (col == ship_locs[26:24] && row == ship_locs[29:27]) begin
							if (((col == active_ship[2:0] && row == active_ship[5:3]) ||
								(col == active_ship[8:6] && row == active_ship[11:9])) &&
								mode == PLACEMENT)
								rgb = OVERLAP;
							else if (ship_bitmap[1] == 0)
								rgb = HIT;
							else if (col == active_ship[8:6] && row == active_ship[11:9])
								rgb = ACTIVE;
							else if (ship_bitmap[1] == 1)
								rgb = (mode == PLACEMENT) ? SHIP : BLANK;
						end else if (col == ship_locs[32:30] && row == ship_locs[35:33]) begin
							if (((col == active_ship[2:0] && row == active_ship[5:3]) ||
								(col == active_ship[8:6] && row == active_ship[11:9])) &&
								mode == PLACEMENT)
								rgb = OVERLAP;
							else if (ship_bitmap[0] == 0)
								rgb = HIT;
							else if (col == active_ship[8:6] && row == active_ship[11:9])
								rgb = ACTIVE;
							else if (ship_bitmap[0] == 1)
								rgb = (mode == PLACEMENT) ? SHIP : BLANK;
						end else if ((col == active_ship[2:0] && row == active_ship[5:3]) ||
									(col == active_ship[8:6] && row == active_ship[11:9]))
							rgb = ACTIVE;
						else if (row == 0 && col == 0)
							rgb = (miss_bitmap[0] == 1) ? MISS : BLANK;
						else if (row == 0 && col == 1)
							rgb = (miss_bitmap[1] == 1) ? MISS : BLANK;
						else if (row == 0 && col == 2)
							rgb = (miss_bitmap[2] == 1) ? MISS : BLANK;
						else if (row == 0 && col == 3)
							rgb = (miss_bitmap[3] == 1) ? MISS : BLANK;
						else if (row == 0 && col == 4)
							rgb = (miss_bitmap[4] == 1) ? MISS : BLANK;
						else if (row == 1 && col == 0)
							rgb = (miss_bitmap[5] == 1) ? MISS : BLANK;
						else if (row == 1 && col == 1)
							rgb = (miss_bitmap[6] == 1) ? MISS : BLANK;
						else if (row == 1 && col == 2)
							rgb = (miss_bitmap[7] == 1) ? MISS : BLANK;
						else if (row == 1 && col == 3)
							rgb = (miss_bitmap[8] == 1) ? MISS : BLANK;
						else if (row == 1 && col == 4)
							rgb = (miss_bitmap[9] == 1) ? MISS : BLANK;
						else if (row == 2 && col == 0)
							rgb = (miss_bitmap[10] == 1) ? MISS : BLANK;
						else if (row == 2 && col == 1)
							rgb = (miss_bitmap[11] == 1) ? MISS : BLANK;
						else if (row == 2 && col == 2)
							rgb = (miss_bitmap[12] == 1) ? MISS : BLANK;
						else if (row == 2 && col == 3)
							rgb = (miss_bitmap[13] == 1) ? MISS : BLANK;
						else if (row == 2 && col == 4)
							rgb = (miss_bitmap[14] == 1) ? MISS : BLANK;
						else if (row == 3 && col == 0)
							rgb = (miss_bitmap[15] == 1) ? MISS : BLANK;
						else if (row == 3 && col == 1)
							rgb = (miss_bitmap[16] == 1) ? MISS : BLANK;
						else if (row == 3 && col == 2)
							rgb = (miss_bitmap[17] == 1) ? MISS : BLANK;
						else if (row == 3 && col == 3)
							rgb = (miss_bitmap[18] == 1) ? MISS : BLANK;
						else if (row == 3 && col == 4)
							rgb = (miss_bitmap[19] == 1) ? MISS : BLANK;
						else if (row == 4 && col == 0)
							rgb = (miss_bitmap[20] == 1) ? MISS : BLANK;
						else if (row == 4 && col == 1)
							rgb = (miss_bitmap[21] == 1) ? MISS : BLANK;
						else if (row == 4 && col == 2)
							rgb = (miss_bitmap[22] == 1) ? MISS : BLANK;
						else if (row == 4 && col == 3)
							rgb = (miss_bitmap[23] == 1) ? MISS : BLANK;
						else if (row == 4 && col == 4)
							rgb = (miss_bitmap[24] == 1) ? MISS : BLANK;
						else
							rgb = BLANK;
					end
				// Outside active horizontal range so display black
				end else
					rgb = BLACK;
			end
		// Outside active vertical range so display black
		end else
			rgb = BLACK;
	end
	
endmodule
