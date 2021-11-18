`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    08:43:55 10/27/2021 
// Design Name: 
// Module Name:    clock_divider 
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
module clock_divider(
	// Input
	input clk, // 100MHz
	// Output
	output reg clk_ssd, // 400,000 clock cycles (250 Hz)
	output reg clk_vga // 4 clock cycles (25 MHz)
);

	// Get constants
	`include "battleship_definitions.v"
	
	// Counters
	reg [31:0] ssd_counter = 0; // counts to 200,000
	reg [31:0] vga_counter = 0; // counts to 2
	
	always @(posedge clk) begin
		// Increment counters
		ssd_counter <= ssd_counter + 1;
		vga_counter <= vga_counter + 1;
		// Check counters
		if (ssd_counter >= CLK_SSD_COUNT) begin
			ssd_counter <= 0;
			clk_ssd <= ~clk_ssd;
		end
		if (vga_counter >= CLK_VGA_COUNT) begin
			vga_counter <= 0;
			clk_vga <= ~clk_vga;
		end
	end

endmodule
