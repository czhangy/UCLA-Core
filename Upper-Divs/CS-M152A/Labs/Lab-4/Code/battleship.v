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
	input BTNC,
	input BTNL,
	input BTNR,
	input BTNU,
	input BTND,
	input SW0,
	input SW1,
	input SW2,
	input SW3,
	input SW4,
	input SW5,
	input SW6,
	input SW7,
	// Outputs
	output [6:0] cathode,
	output [3:0] anode,
	output hsync,
	output vsync,
	output [2:0] red,
	output [2:0] green,
	output [1:0] blue
);

	// Debounced input signals
	wire rst;
	wire btnC, btnL, btnR, btnU, btnD;
	wire sw0, sw1, sw2, sw3, sw4, sw5, sw6, sw7;
	
	// Divided clock signals
	wire clk_ssd;
	wire clk_vga;
	
	// Cathode values
	wire [6:0] p1_cathode;
	wire [6:0] p2_cathode;

	// Score
	wire [2:0] p1_ships;
	wire [2:0] p2_ships;
	assign p1_ships = 5;
	assign p2_ships = 5;
	
	// Game boards

	// Debounce all inputs
	debouncer db_rst(.clk(clk), .signal_i(RST), .signal_f(rst));
	debouncer db_btnC(.clk(clk), .signal_i(BTNC), .signal_f(btnC));
	debouncer db_btnL(.clk(clk), .signal_i(BTNL), .signal_f(btnL));
	debouncer db_btnR(.clk(clk), .signal_i(BTNR), .signal_f(btnR));
	debouncer db_btnU(.clk(clk), .signal_i(BTNU), .signal_f(btnU));
	debouncer db_btnD(.clk(clk), .signal_i(BTND), .signal_f(btnD));
	debouncer db_sw0(.clk(clk), .signal_i(SW0), .signal_f(sw0));
	debouncer db_sw1(.clk(clk), .signal_i(SW1), .signal_f(sw1));
	debouncer db_sw2(.clk(clk), .signal_i(SW2), .signal_f(sw2));
	debouncer db_sw3(.clk(clk), .signal_i(SW3), .signal_f(sw3));
	debouncer db_sw4(.clk(clk), .signal_i(SW4), .signal_f(sw4));
	debouncer db_sw5(.clk(clk), .signal_i(SW5), .signal_f(sw5));
	debouncer db_sw6(.clk(clk), .signal_i(SW6), .signal_f(sw6));
	debouncer db_sw7(.clk(clk), .signal_i(SW7), .signal_f(sw7));
	
	// Divide the master clock signal
	clock_divider clk_div(
		.clk(clk),
		.rst(btnC),
		.clk_ssd(clk_ssd),
		.clk_vga(clk_vga)
	);
	
	// Handle SSD
	ssd ssd_display(
		.clk_ssd(clk_ssd),
		.p1_ships(p1_ships),
		.p2_ships(p2_ships),
		.cathode(cathode),
		.anode(anode)
	);
	
	// Handle VGA
	vga vga_display(
		.clk_vga(clk_vga),
		.rst(btnC),
		.hsync(hsync),
		.vsync(vsync),
		.red(red),
		.green(green),
		.blue(blue)
	);

endmodule
