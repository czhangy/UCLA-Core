`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:51:42 11/16/2021 
// Design Name: 
// Module Name:    battleship 
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
module battleship(
	// Inputs
	input clk,
	input SEL,
	input RST,
	input ROT,
	input SW0,
	input SW1,
	input SW2,
	input SW3,
	input SW4,
	input SW5,
	// Outputs
	output [6:0] cathode,
	output [3:0] anode,
	output hsync,
	output vsync,
	output [7:0] rgb
);

	// Get constants
	`include "battleship_definitions.v"
	
	// Debounced input signals
	wire sel, rst, rot;
	wire sw0, sw1, sw2, sw3, sw4, sw5;
	
	// Divided clock signals
	wire clk_ssd;
	wire clk_vga;
	
	// Cathode values
	wire [6:0] p1_cathode;
	wire [6:0] p2_cathode;

	// Game state
	wire [11:0] active_ship;
	wire [35:0] ship_locs;
	wire [5:0] ship_bitmap;
	wire [24:0] miss_bitmap;
	wire [1:0] mode;
	wire turn;

	// Debounce all inputs
	debouncer db_sel(.clk(clk), .signal_i(SEL), .signal_f(sel));
	debouncer db_rst(.clk(clk), .signal_i(RST), .signal_f(rst));
	debouncer db_rot(.clk(clk), .signal_i(ROT), .signal_f(rot));
	debouncer db_sw0(.clk(clk), .signal_i(SW0), .signal_f(sw0));
	debouncer db_sw1(.clk(clk), .signal_i(SW1), .signal_f(sw1));
	debouncer db_sw2(.clk(clk), .signal_i(SW2), .signal_f(sw2));
	debouncer db_sw3(.clk(clk), .signal_i(SW3), .signal_f(sw3));
	debouncer db_sw4(.clk(clk), .signal_i(SW4), .signal_f(sw4));
	debouncer db_sw5(.clk(clk), .signal_i(SW5), .signal_f(sw5));

	// Divide the master clock signal
	clock_divider clk_div(
		.clk(clk),
		.rst(rst),
		.clk_ssd(clk_ssd),
		.clk_vga(clk_vga)
	);
	
	// Determine the game mode and handle logic
	game_logic game(
		.clk(clk),
		.sel(sel),
		.rst(rst),
		.rot(rot),
		.sw0(sw0),
		.sw1(sw1),
		.sw2(sw2),
		.sw3(sw3),
		.sw4(sw4),
		.sw5(sw5),
		.active_ship(active_ship),
		.ship_locs(ship_locs),
		.ship_bitmap(ship_bitmap),
		.miss_bitmap(miss_bitmap),
		.mode(mode),
		.turn(turn)
	);
	
	// Handle SSD
	ssd ssd_display(
		.clk_ssd(clk_ssd),
		.turn(turn),
		.cathode(cathode),
		.anode(anode)
	);
	
	// Handle VGA
	vga vga_display(
		.clk_vga(clk_vga),
		.rst(rst),
		.active_ship(active_ship),
		.ship_locs(ship_locs),
		.ship_bitmap(ship_bitmap),
		.miss_bitmap(miss_bitmap),
		.mode(mode),
		.hsync(hsync),
		.vsync(vsync),
		.rgb(rgb)
	);

endmodule
