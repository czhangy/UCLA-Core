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

		if (ROW_0_MIN <= v_counter && v_counter <= ROW_0_MAX)
			row = 0;
		if (ROW_1_MIN <= v_counter && v_counter <= ROW_1_MAX)
			row = 1;
		if (ROW_2_MIN <= v_counter && v_counter <= ROW_2_MAX)
			row = 2;
		if (ROW_3_MIN <= v_counter && v_counter <= ROW_3_MAX)
			row = 3;
		if (ROW_4_MIN <= v_counter && v_counter <= ROW_4_MAX)
			row = 4;
		if (ROW_5_MIN <= v_counter && v_counter <= ROW_5_MAX)
			row = 5;
		if (ROW_6_MIN <= v_counter && v_counter <= ROW_6_MAX)
			row = 6;
		if (ROW_7_MIN <= v_counter && v_counter <= ROW_7_MAX)
			row = 7;
		if (ROW_8_MIN <= v_counter && v_counter <= ROW_8_MAX)
			row = 8;
		if (ROW_9_MIN <= v_counter && v_counter <= ROW_9_MAX)
			row = 9;
			

			if (hc >= hbp && hc < (hbp+80))
			begin
				red = 3'b111;
				green = 3'b111;
				blue = 2'b11;
			end
			// display yellow bar
			else if (hc >= (hbp+80) && hc < (hbp+160))
			begin
				red = 3'b111;
				green = 3'b111;
				blue = 2'b00;
			end
			// display cyan bar
			else if (hc >= (hbp+160) && hc < (hbp+240))
			begin
				red = 3'b000;
				green = 3'b111;
				blue = 2'b11;
			end
			// display green bar
			else if (hc >= (hbp+240) && hc < (hbp+320))
			begin
				red = 3'b000;
				green = 3'b111;
				blue = 2'b00;
			end
			// display magenta bar
			else if (hc >= (hbp+320) && hc < (hbp+400))
			begin
				red = 3'b111;
				green = 3'b000;
				blue = 2'b11;
			end
			// display red bar
			else if (hc >= (hbp+400) && hc < (hbp+480))
			begin
				red = 3'b111;
				green = 3'b000;
				blue = 2'b00;
			end
			// display blue bar
			else if (hc >= (hbp+480) && hc < (hbp+560))
			begin
				red = 3'b000;
				green = 3'b000;
				blue = 2'b11;
			end
			// display black bar
			else if (hc >= (hbp+560) && hc < (hbp+640))
			begin
				red = 3'b000;
				green = 3'b000;
				blue = 2'b00;
			end
			// we're outside active horizontal range so display black
			else
			begin
				red = 0;
				green = 0;
				blue = 0;
			end
		end
		// we're outside active vertical range so display black
		else begin
			red = 0;
			green = 0;
			blue = 0;
		end
	end

endmodule
