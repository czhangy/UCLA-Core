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
	output [7:0] rgb
);

	// Get constants
	`include "battleship_definitions.v"
	
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

	// Game boards
	wire [BOARD_SIZE - 1:0] p1_board;
	wire [BOARD_SIZE - 1:0] p2_board;

	// Initialize score
	reg [2:0] p1_ships;
	reg [2:0] p2_ships;
	initial begin
		p1_ships = 5;
		p2_ships = 5;
	end
	
	// Track player turn (0 is p1, 1 is p2)
	reg turn;
	initial begin
		turn = 0;
	end
	
	// Track game mode (0 is placement, 1 is play)
	reg mode;
	initial begin
		mode = 0;
	end

	// Debounce all inputs
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

	// Check for reset
    assign rst = btnC && sw0 && sw1 && sw2 && sw3 && sw4 && sw5 && sw6 && sw7;
	
	// Divide the master clock signal
	clock_divider clk_div(
		.clk(clk),
		.rst(rst),
		.clk_ssd(clk_ssd),
		.clk_vga(clk_vga)
	);
	
	// Determine the game mode and handle logic
	game game_logic(
		.clk(clk),
		.rst(rst),
		.btnC(btnC),
		.btnL(btnL),
		.btnR(btnR),
		.btnU(btnU),
		.btnD(btnD),
		.sw0(sw0),
		.sw1(sw1),
		.sw2(sw2),
		.sw3(sw3),
		.sw4(sw4),
		.sw5(sw5),
		.sw6(sw6),
		.sw7(sw7),
		.p1_board(p1_board),
		.p2_board(p2_board),
		.p1_ships(p1_ships),
		.p2_ships(p2_ships),
		.mode(mode),
		.turn(turn)
	)

	wire [1:0] game_state;
	assign game_state = 2;
	
	// Handle SSD
	ssd ssd_display(
		.clk_ssd(clk_ssd),
		.p1_ships(p1_ships),
		.p2_ships(p2_ships),
		.game_state(game_state),
		.cathode(cathode),
		.anode(anode)
	);
	
	// Handle VGA
	vga vga_display(
		.clk_vga(clk_vga),
		.rst(rst),
		.player_turn(turn),
		.p1_board(p1_board),
		.p2_board(p2_board),
		.game_state(game_state),
		.hsync(hsync),
		.vsync(vsync),
		.rgb(rgb)
	);

endmodule
