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
	// Inputs
	input clk,
	input rst,
	// Outputs
	output clk_ssd,
	output clk_vga
);

	// 17-bit counter variable
	reg [16:0] counter;

	always @(posedge clk or posedge rst) begin
		// Reset
		if (rst)
			counter <= 0;
		else
			counter <= counter + 1;
	end
	
	// Assign clock signals
	assign clk_ssd = counter[SSD_BIT];
	assign clk_vga = counter[VGA_BIT];

endmodule
