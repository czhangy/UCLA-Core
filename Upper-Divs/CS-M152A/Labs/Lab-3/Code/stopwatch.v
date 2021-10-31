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
	
	// Debounced input signals
	wire sel;
	wire adj;
	wire rst;
	wire pause;

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

	// Debounce input signals
	debouncer sel_debouncer (
		.clk(clk),
		.signal_i(SEL),
		.signal_f(sel)
	);
	
	debouncer adj_debouncer (
		.clk(clk),
		.signal_i(ADJ),
		.signal_f(adj)
	);
	
	debouncer rst_debouncer (
		.clk(clk),
		.signal_i(RESET),
		.signal_f(rst)
	);
	
	debouncer pause_debouncer (
		.clk(clk),
		.signal_i(PAUSE),
		.signal_f(pause)
	);

	// Initialize counter
	counter decade_counter (
		.clk_1hz(clk_1hz),
		.clk_2hz(clk_2hz),
		.sel(sel),
		.adj(adj),
		.rst(rst),
		.pause(pause),
		.minutes_tens(minutes_tens),
		.minutes_ones(minutes_ones),
		.seconds_tens(seconds_tens),
		.seconds_ones(seconds_ones)
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
