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
	input clk_vga,			// VGA clock: 25MHz
	input rst,				// Asynchronous reset
	// Outputs
	output hsync,			// Horizontal sync out
	output vsync,			// Vertical sync out
	output reg [2:0] red,	// Red VGA output
	output reg [2:0] green, // green VGA output
	output reg [1:0] blue	// blue VGA output
);
	

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
		if (ROW_0_MIN <= v_counter && v_counter <= ROW_0_MAX)
			row = 0;
		else if (ROW_1_MIN <= v_counter && v_counter <= ROW_1_MAX)
			row = 1;
		else if (ROW_2_MIN <= v_counter && v_counter <= ROW_2_MAX)
			row = 2;
		else if (ROW_3_MIN <= v_counter && v_counter <= ROW_3_MAX)
			row = 3;
		else if (ROW_4_MIN <= v_counter && v_counter <= ROW_4_MAX)
			row = 4;
		else if (ROW_5_MIN <= v_counter && v_counter <= ROW_5_MAX)
			row = 5;
		else if (ROW_6_MIN <= v_counter && v_counter <= ROW_6_MAX)
			row = 6;
		else if (ROW_7_MIN <= v_counter && v_counter <= ROW_7_MAX)
			row = 7;
		else if (ROW_8_MIN <= v_counter && v_counter <= ROW_8_MAX)
			row = 8;
		else if (ROW_9_MIN <= v_counter && v_counter <= ROW_9_MAX)
			row = 9;
		else
			row = 10;
		// Set column
		if (COL_0_MIN <= h_counter && h_counter <= COL_0_MAX)
			col = 0;
		else if (COL_1_MIN <= h_counter && h_counter <= COL_1_MAX)
			col = 1;
		else if (COL_2_MIN <= h_counter && h_counter <= COL_2_MAX)
			col = 2;
		else if (COL_3_MIN <= h_counter && h_counter <= COL_3_MAX)
			col = 3;
		else if (COL_4_MIN <= h_counter && h_counter <= COL_4_MAX)
			col = 4;
		else if (COL_5_MIN <= h_counter && h_counter <= COL_5_MAX)
			col = 5;
		else if (COL_6_MIN <= h_counter && h_counter <= COL_6_MAX)
			col = 6;
		else if (COL_7_MIN <= h_counter && h_counter <= COL_7_MAX)
			col = 7;
		else if (COL_8_MIN <= h_counter && h_counter <= COL_8_MAX)
			col = 8;
		else if (COL_9_MIN <= h_counter && h_counter <= COL_9_MAX)
			col = 9;
		else
			col = 10;
	end

endmodule
