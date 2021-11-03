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
	
	// FSM states
	wire [3:0] minutes_tens;
	wire [3:0] minutes_ones;
	wire [3:0] seconds_tens;
	wire [3:0] seconds_ones;
	
	// Cathode values
	wire [6:0] minutes_tens_cathode;
	wire [6:0] minutes_ones_cathode;
	wire [6:0] seconds_tens_cathode;
	wire [6:0] seconds_ones_cathode;

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
	
	// Get cathode values
	get_cathode translate_minutes_tens (
		.display_state(minutes_tens),
		.cathode(minutes_tens_cathode)
	);
	
	get_cathode translate_minutes_ones (
		.display_state(minutes_ones),
		.cathode(minutes_ones_cathode)
	);
	
	get_cathode translate_seconds_tens (
		.display_state(seconds_tens),
		.cathode(seconds_tens_cathode)
	);
	
	get_cathode translate_seconds_ones (
		.display_state(seconds_ones),
		.cathode(seconds_ones_cathode)
	);
	
	// Set the display
	create_display display (
		.clk_fst(clk_fst),
		.clk_blnk(clk_blnk),
		.sel(sel),
		.adj(adj),
		.minutes_tens_cathode(minutes_tens_cathode),
		.minutes_ones_cathode(minutes_ones_cathode),
		.seconds_tens_cathode(seconds_tens_cathode),
		.seconds_ones_cathode(seconds_ones_cathode),
		.cathode(cathode),
		.anode(anode)
	);
	
endmodule
