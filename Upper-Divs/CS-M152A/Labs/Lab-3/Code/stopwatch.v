`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    08:40:54 10/27/2021 
// Design Name: 
// Module Name:    stopwatch 
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
module stopwatch(
	// Inputs
	input clk, 
	input SEL,
	input ADJ,
	input RESET,
	input PAUSE,
	// Outputs
	output [6:0] cathode,
	output [3:0] anode
);
	
	// Divided clock signals
	wire clk_2hz;
	wire clk_1hz;
	wire clk_fst;
	wire clk_blnk;

	wire [3:0] display_state_0;
	wire [3:0] display_state_1;
	wire [3:0] display_state_2;
	wire [3:0] display_state_3;

	// Divide master clock into 4 signals
	clock_divider clk_div (
		.clk(clk),
		.rst(RESET),
		.clk_2hz(clk_2hz),
		.clk_1hz(clk_1hz),
		.clk_fst(clk_fst),
		.clk_blnk(clk_blnk)
	);

	// Initialize counter
	counter m2 (
		.clk_1hz(clk_1hz),
		.clk_2hz(clk_2hz),
		.ADJ(ADJ),
		.SEL(SEL),
		.RESET(RESET),
		.display_state_0(display_state_0),
		.display_state_1(display_state_1),
		.display_state_2(display_state_2),
		.display_state_3(display_state_3)
	);

	// Connect to seven-segment display
	ssd m3 (
		.display_state(display_state_3),
		.clk_blnk(clk_blnk),
		.ADJ(ADJ),
		.ssd(ssd_3)
	);

	ssd m4 (
		.display_state(display_state_2),
		.clk_blnk(clk_blnk),
		.ADJ(ADJ),
		.ssd(ssd_2)
	);

	ssd m5 (
		.display_state(display_state_1),
		.clk_blnk(clk_blnk),
		.ADJ(ADJ),
		.ssd(ssd_1)
	);
	
	ssd m6 (
		.display_state(display_state_0),
		.clk_blnk(clk_blnk),
		.ADJ(ADJ),
		.ssd(ssd_0)
	);

endmodule
