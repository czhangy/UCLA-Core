`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    18:47:23 11/30/2021 
// Design Name: 
// Module Name:    game_logic 
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
module game_logic(
	// Inputs
	input clk,
	input sel,
	input rst,
	input rot,
	input sw0,
	input sw1,
	input sw2,
	input sw3,
	input sw4,
	input sw5,
	// Outputs
	output reg [11:0] active_ship,
	output reg [35:0] ship_locs,
	output reg [5:0] ship_bitmap,
	output reg [24:0] miss_bitmap,
	output reg [1:0] mode,
	output reg turn
);

	// Get constants
	`include "battleship_definitions.v"

	// Initialization constants
	parameter SHIP_INIT = 6'b101101;
	parameter STANDING_SHIP_INIT = 12'b111111111111;

	// Bound constants
	parameter UPPER_BOUND = 5;

	// Position
	reg [2:0] row = 0;
	reg [2:0] col = 0;
	reg [2:0] tailRow = 0;
	reg [2:0] tailCol = 0;

	// Initialize ships
	reg [5:0] p1_ship_0_0 = SHIP_INIT;
	reg [5:0] p1_ship_0_1 = SHIP_INIT;
	reg [5:0] p1_ship_1_0 = SHIP_INIT;
	reg [5:0] p1_ship_1_1 = SHIP_INIT;
	reg [5:0] p1_ship_2_0 = SHIP_INIT;
	reg [5:0] p1_ship_2_1 = SHIP_INIT;
	reg [5:0] p2_ship_0_0 = SHIP_INIT;
	reg [5:0] p2_ship_0_1 = SHIP_INIT;
	reg [5:0] p2_ship_1_0 = SHIP_INIT;
	reg [5:0] p2_ship_1_1 = SHIP_INIT;
	reg [5:0] p2_ship_2_0 = SHIP_INIT;
	reg [5:0] p2_ship_2_1 = SHIP_INIT;

	// Initialize state
	reg [3:0] ships_placed = 0;
	reg [11:0] standing_ships = STANDING_SHIP_INIT;
	
	// Miss bitmaps
	reg [24:0] p1_miss = 0;
	reg [24:0] p2_miss = 0;

	// Rotation state
	reg horizontal = 0;
	
	// Initialize game
	initial begin
		// Initialize state
		turn = PLAYER_1;
		mode = PLACEMENT;
	end

	// Check for rotation
	always @(posedge rot) begin
		horizontal = ~horizontal;
	end
	
	// Check for button press
	always @(posedge sel or posedge rst) begin
		if (rst) begin
			// Reset state
			turn = PLAYER_1;
			mode = PLACEMENT;
			p1_ship_0_0 = SHIP_INIT;
			p1_ship_0_1 = SHIP_INIT;
			p1_ship_1_0 = SHIP_INIT;
			p1_ship_1_1 = SHIP_INIT;
			p1_ship_2_0 = SHIP_INIT;
			p1_ship_2_1 = SHIP_INIT;
			p2_ship_0_0 = SHIP_INIT;
			p2_ship_0_1 = SHIP_INIT;
			p2_ship_1_0 = SHIP_INIT;
			p2_ship_1_1 = SHIP_INIT;
			p2_ship_2_0 = SHIP_INIT;
			p2_ship_2_1 = SHIP_INIT;
			p1_miss = 0;
			p2_miss = 0;
			ships_placed = 0;
			standing_ships = STANDING_SHIP_INIT;
		end else begin
			// Check game mode
			if (mode == PLACEMENT) begin
				// P1, ship 1
				if (ships_placed == 0) begin
					// Horizontal placement
					if (horizontal) begin
						// Check bounds
						if (row < UPPER_BOUND && col < UPPER_BOUND - 1) begin
							// Place ship pivot
							p1_ship_0_0[2:0] = col;
							p1_ship_0_0[5:3] = row;
							// Place ship terminal
							p1_ship_0_1[2:0] = col + 1;
							p1_ship_0_1[5:3] = row;
							// Update count
							ships_placed = 1;
						end
					// Vertical placement
					end else begin
						// Check bounds
						if (row < UPPER_BOUND - 1 && col < UPPER_BOUND) begin
							// Place ship pivot
							p1_ship_0_0[2:0] = col;
							p1_ship_0_0[5:3] = row;
							// Place ship terminal
							p1_ship_0_1[2:0] = col;
							p1_ship_0_1[5:3] = row + 1;
							// Update count
							ships_placed = 1;
						end
					end
				// P1, ship 2
				end else if (ships_placed == 1 &&
							((p1_ship_0_0[2:0] != col) || (p1_ship_0_0[5:3] != row)) &&
							((p1_ship_0_1[2:0] != col) || (p1_ship_0_1[5:3] != row))) begin
					// Horizontal placement
					if (horizontal) begin
						// Check bounds and overlap
						if (row < UPPER_BOUND && col < UPPER_BOUND - 1 &&
							((p1_ship_0_0[2:0] != col + 1) || (p1_ship_0_0[5:3] != row)) &&
							((p1_ship_0_1[2:0] != col + 1) || (p1_ship_0_1[5:3] != row))) begin
							// Place ship pivot
							p1_ship_1_0[2:0] = col;
							p1_ship_1_0[5:3] = row;
							// Place ship terminal
							p1_ship_1_1[2:0] = col + 1;
							p1_ship_1_1[5:3] = row;
							// Update count
							ships_placed = 2;
						end
					// Vertical placement
					end else begin
						// Check bounds and overlap
						if (row < UPPER_BOUND - 1 && col < UPPER_BOUND &&
							((p1_ship_0_0[2:0] != col) || (p1_ship_0_0[5:3] != row + 1)) &&
							((p1_ship_0_1[2:0] != col) || (p1_ship_0_1[5:3] != row + 1))) begin
							// Place ship pivot
							p1_ship_1_0[2:0] = col;
							p1_ship_1_0[5:3] = row;
							// Place ship terminal
							p1_ship_1_1[2:0] = col;
							p1_ship_1_1[5:3] = row + 1;
							// Update count
							ships_placed = 2;
						end
					end
				// P1, ship 3
				end else if (ships_placed == 2 &&
							((p1_ship_0_0[2:0] != col) || (p1_ship_0_0[5:3] != row)) &&
							((p1_ship_0_1[2:0] != col) || (p1_ship_0_1[5:3] != row)) &&
							((p1_ship_1_0[2:0] != col) || (p1_ship_1_0[5:3] != row)) &&
							((p1_ship_1_1[2:0] != col) || (p1_ship_1_1[5:3] != row))) begin
					// Horizontal placement
					if (horizontal) begin
						// Check bounds and overlap
						if (row < UPPER_BOUND && col < UPPER_BOUND - 1 &&
							((p1_ship_0_0[2:0] != col + 1) || (p1_ship_0_0[5:3] != row)) &&
							((p1_ship_0_1[2:0] != col + 1) || (p1_ship_0_1[5:3] != row)) &&
							((p1_ship_1_0[2:0] != col + 1) || (p1_ship_1_0[5:3] != row)) &&
							((p1_ship_1_1[2:0] != col + 1) || (p1_ship_1_1[5:3] != row))) begin
							// Place ship pivot
							p1_ship_2_0[2:0] = col;
							p1_ship_2_0[5:3] = row;
							// Place ship terminal
							p1_ship_2_1[2:0] = col + 1;
							p1_ship_2_1[5:3] = row;
							// Update count
							ships_placed = 3;
							// Update turn
							turn = PLAYER_2;
						end
					// Vertical placement
					end else begin
						// Check bounds and overlap
						if (row < UPPER_BOUND - 1 && col < UPPER_BOUND &&
							((p1_ship_0_0[2:0] != col) || (p1_ship_0_0[5:3] != row + 1)) &&
							((p1_ship_0_1[2:0] != col) || (p1_ship_0_1[5:3] != row + 1)) &&
							((p1_ship_1_0[2:0] != col) || (p1_ship_1_0[5:3] != row + 1)) &&
							((p1_ship_1_1[2:0] != col) || (p1_ship_1_1[5:3] != row + 1))) begin
							// Place ship pivot
							p1_ship_2_0[2:0] = col;
							p1_ship_2_0[5:3] = row;
							// Place ship terminal
							p1_ship_2_1[2:0] = col;
							p1_ship_2_1[5:3] = row + 1;
							// Update count
							ships_placed = 3;
							// Update turn
							turn = PLAYER_2;
						end
					end
				// P2, ship 1
				end else if (ships_placed == 3) begin
					// Horizontal placement
					if (horizontal) begin
						// Check bounds
						if (row < UPPER_BOUND && col < UPPER_BOUND - 1) begin
							// Place ship pivot
							p2_ship_0_0[2:0] = col;
							p2_ship_0_0[5:3] = row;
							// Place ship terminal
							p2_ship_0_1[2:0] = col + 1;
							p2_ship_0_1[5:3] = row;
							// Update count
							ships_placed = 4;
						end
					// Vertical placement
					end else begin
						// Check bounds
						if (row < UPPER_BOUND - 1 && col < UPPER_BOUND) begin
							// Place ship pivot
							p2_ship_0_0[2:0] = col;
							p2_ship_0_0[5:3] = row;
							// Place ship terminal
							p2_ship_0_1[2:0] = col;
							p2_ship_0_1[5:3] = row + 1;
							// Update count
							ships_placed = 4;
						end
					end
				// P2, ship 2
				end else if (ships_placed == 4 &&
							((p2_ship_0_0[2:0] != col) || (p2_ship_0_0[5:3] != row)) &&
							((p2_ship_0_1[2:0] != col) || (p2_ship_0_1[5:3] != row))) begin
					// Horizontal placement
					if (horizontal) begin
						// Check bounds and overlap
						if (row < UPPER_BOUND && col < UPPER_BOUND - 1 &&
							((p2_ship_0_0[2:0] != col + 1) || (p2_ship_0_0[5:3] != row)) &&
							((p2_ship_0_1[2:0] != col + 1) || (p2_ship_0_1[5:3] != row))) begin
							// Place ship pivot
							p2_ship_1_0[2:0] = col;
							p2_ship_1_0[5:3] = row;
							// Place ship terminal
							p2_ship_1_1[2:0] = col + 1;
							p2_ship_1_1[5:3] = row;
							// Update count
							ships_placed = 5;
						end
					// Vertical placement
					end else begin
						// Check bounds and overlap
						if (row < UPPER_BOUND - 1 && col < UPPER_BOUND &&
							((p2_ship_0_0[2:0] != col) || (p2_ship_0_0[5:3] != row + 1)) &&
							((p2_ship_0_1[2:0] != col) || (p2_ship_0_1[5:3] != row + 1))) begin
							// Place ship pivot
							p2_ship_1_0[2:0] = col;
							p2_ship_1_0[5:3] = row;
							// Place ship terminal
							p2_ship_1_1[2:0] = col;
							p2_ship_1_1[5:3] = row + 1;
							// Update count
							ships_placed = 5;
						end
					end
				// P2, ship 3
				end else if (ships_placed == 5 &&
							((p2_ship_0_0[2:0] != col) || (p2_ship_0_0[5:3] != row)) &&
							((p2_ship_0_1[2:0] != col) || (p2_ship_0_1[5:3] != row)) &&
							((p2_ship_1_0[2:0] != col) || (p2_ship_1_0[5:3] != row)) &&
							((p2_ship_1_1[2:0] != col) || (p2_ship_1_1[5:3] != row))) begin
					// Horizontal placement
					if (horizontal) begin
						// Check bounds and overlap
						if (row < UPPER_BOUND && col < UPPER_BOUND - 1 &&
							((p2_ship_0_0[2:0] != col + 1) || (p2_ship_0_0[5:3] != row)) &&
							((p2_ship_0_1[2:0] != col + 1) || (p2_ship_0_1[5:3] != row)) &&
							((p2_ship_1_0[2:0] != col + 1) || (p2_ship_1_0[5:3] != row)) &&
							((p2_ship_1_1[2:0] != col + 1) || (p2_ship_1_1[5:3] != row))) begin
							// Place ship pivot
							p2_ship_2_0[2:0] = col;
							p2_ship_2_0[5:3] = row;
							// Place ship terminal
							p2_ship_2_1[2:0] = col + 1;
							p2_ship_2_1[5:3] = row;
							// Update mode
							mode = GAME;
							// Update turn
							turn = PLAYER_1;
						end
					// Vertical placement
					end else begin
						// Check bounds and overlap
						if (row < UPPER_BOUND - 1 && col < UPPER_BOUND &&
							((p2_ship_0_0[2:0] != col) || (p2_ship_0_0[5:3] != row + 1)) &&
							((p2_ship_0_1[2:0] != col) || (p2_ship_0_1[5:3] != row + 1)) &&
							((p2_ship_1_0[2:0] != col) || (p2_ship_1_0[5:3] != row + 1)) &&
							((p2_ship_1_1[2:0] != col) || (p2_ship_1_1[5:3] != row + 1))) begin
							// Place ship pivot
							p2_ship_2_0[2:0] = col;
							p2_ship_2_0[5:3] = row;
							// Place ship terminal
							p2_ship_2_1[2:0] = col;
							p2_ship_2_1[5:3] = row + 1;
							// Update mode
							mode = GAME;
							// Update turn
							turn = PLAYER_2;
						end
					end
				end
			// Game mode
			end else if (mode == GAME) begin
				if (turn == PLAYER_1) begin
					if (col == p2_ship_0_0[2:0] && row == p2_ship_0_0[5:3] && standing_ships[6] == 1)
						standing_ships[6] = 0;
					else if (col == p2_ship_0_1[2:0] && row == p2_ship_0_1[5:3] && standing_ships[7] == 1)
						standing_ships[7] = 0;
					else if (col == p2_ship_1_0[2:0] && row == p2_ship_1_0[5:3] && standing_ships[8] == 1)
						standing_ships[8] = 0;
					else if (col == p2_ship_1_1[2:0] && row == p2_ship_1_1[5:3] && standing_ships[9] == 1)
						standing_ships[9] = 0;
					else if (col == p2_ship_2_0[2:0] && row == p2_ship_2_0[5:3] && standing_ships[10] == 1)
						standing_ships[10] = 0;
					else if (col == p2_ship_2_1[2:0] && row == p2_ship_2_1[5:3] && standing_ships[11] == 1)
						standing_ships[11] = 0;
					else begin
						// Find the grid that was shot
						if (row == 0 && col == 0)
							p2_miss[0] = 1;
						else if (row == 0 && col == 1)
							p2_miss[1] = 1;
						else if (row == 0 && col == 2)
							p2_miss[2] = 1;
						else if (row == 0 && col == 3)
							p2_miss[3] = 1;
						else if (row == 0 && col == 4)
							p2_miss[4] = 1;
						else if (row == 1 && col == 0)
							p2_miss[5] = 1;
						else if (row == 1 && col == 1)
							p2_miss[6] = 1;
						else if (row == 1 && col == 2)
							p2_miss[7] = 1;
						else if (row == 1 && col == 3)
							p2_miss[8] = 1;
						else if (row == 1 && col == 4)
							p2_miss[9] = 1;
						else if (row == 2 && col == 0)
							p2_miss[10] = 1;
						else if (row == 2 && col == 1)
							p2_miss[11] = 1;
						else if (row == 2 && col == 2)
							p2_miss[12] = 1;
						else if (row == 2 && col == 3)
							p2_miss[13] = 1;
						else if (row == 2 && col == 4)
							p2_miss[14] = 1;
						else if (row == 3 && col == 0)
							p2_miss[15] = 1;
						else if (row == 3 && col == 1)
							p2_miss[16] = 1;
						else if (row == 3 && col == 2)
							p2_miss[17] = 1;
						else if (row == 3 && col == 3)
							p2_miss[18] = 1;
						else if (row == 3 && col == 4)
							p2_miss[19] = 1;
						else if (row == 4 && col == 0)
							p2_miss[20] = 1;
						else if (row == 4 && col == 1)
							p2_miss[21] = 1;
						else if (row == 4 && col == 2)
							p2_miss[22] = 1;
						else if (row == 4 && col == 3)
							p2_miss[23] = 1;
						else if (row == 4 && col == 4)
							p2_miss[24] = 1;
						turn = PLAYER_2;
					end
				end else begin
					if (col == p1_ship_0_0[2:0] && row == p1_ship_0_0[5:3] && standing_ships[0] == 1)
						standing_ships[0] = 0;
					else if (col == p1_ship_0_1[2:0] && row == p1_ship_0_1[5:3] && standing_ships[1] == 1)
						standing_ships[1] = 0;
					else if (col == p1_ship_1_0[2:0] && row == p1_ship_1_0[5:3] && standing_ships[2] == 1)
						standing_ships[2] = 0;
					else if (col == p1_ship_1_1[2:0] && row == p1_ship_1_1[5:3] && standing_ships[3] == 1)
						standing_ships[3] = 0;
					else if (col == p1_ship_2_0[2:0] && row == p1_ship_2_0[5:3] && standing_ships[4] == 1)
						standing_ships[4] = 0;
					else if (col == p1_ship_2_1[2:0] && row == p1_ship_2_1[5:3] && standing_ships[5] == 1)
						standing_ships[5] = 0;
					else begin
						// Find the grid that was shot
						if (row == 0 && col == 0)
							p1_miss[0] = 1;
						else if (row == 0 && col == 1)
							p1_miss[1] = 1;
						else if (row == 0 && col == 2)
							p1_miss[2] = 1;
						else if (row == 0 && col == 3)
							p1_miss[3] = 1;
						else if (row == 0 && col == 4)
							p1_miss[4] = 1;
						else if (row == 1 && col == 0)
							p1_miss[5] = 1;
						else if (row == 1 && col == 1)
							p1_miss[6] = 1;
						else if (row == 1 && col == 2)
							p1_miss[7] = 1;
						else if (row == 1 && col == 3)
							p1_miss[8] = 1;
						else if (row == 1 && col == 4)
							p1_miss[9] = 1;
						else if (row == 2 && col == 0)
							p1_miss[10] = 1;
						else if (row == 2 && col == 1)
							p1_miss[11] = 1;
						else if (row == 2 && col == 2)
							p1_miss[12] = 1;
						else if (row == 2 && col == 3)
							p1_miss[13] = 1;
						else if (row == 2 && col == 4)
							p1_miss[14] = 1;
						else if (row == 3 && col == 0)
							p1_miss[15] = 1;
						else if (row == 3 && col == 1)
							p1_miss[16] = 1;
						else if (row == 3 && col == 2)
							p1_miss[17] = 1;
						else if (row == 3 && col == 3)
							p1_miss[18] = 1;
						else if (row == 3 && col == 4)
							p1_miss[19] = 1;
						else if (row == 4 && col == 0)
							p1_miss[20] = 1;
						else if (row == 4 && col == 1)
							p1_miss[21] = 1;
						else if (row == 4 && col == 2)
							p1_miss[22] = 1;
						else if (row == 4 && col == 3)
							p1_miss[23] = 1;
						else if (row == 4 && col == 4)
							p1_miss[24] = 1;
						turn = PLAYER_1;
					end
				end
				// Check win conditions
				if (|standing_ships[5:0] == 0 || |standing_ships[11:6] == 0) 
					mode = WIN;
			end
		end
	end
    
	always @(posedge clk) begin
		// Get position
		row = { sw2, sw1, sw0 };
		col = { sw5, sw4, sw3 };
		// Place in valid location on border
		if (mode == PLACEMENT && horizontal && row < UPPER_BOUND && col == UPPER_BOUND - 1)
			col = UPPER_BOUND;
		else if (mode == PLACEMENT && ~horizontal && row == UPPER_BOUND -1 && col < UPPER_BOUND)
			row = UPPER_BOUND;
		// Player 1 ships
		if ((mode == PLACEMENT && turn == PLAYER_1) || (mode == GAME && turn == PLAYER_2)) begin
			ship_locs = { p1_ship_0_0, p1_ship_0_1, p1_ship_1_0, p1_ship_1_1, p1_ship_2_0, p1_ship_2_1 };
			ship_bitmap = standing_ships[5:0];
			miss_bitmap = p1_miss;
		
		// Player 2 ships
		end else begin
			ship_locs = { p2_ship_0_0, p2_ship_0_1, p2_ship_1_0, p2_ship_1_1, p2_ship_2_0, p2_ship_2_1 };
			ship_bitmap = standing_ships[11:6];
			miss_bitmap = p2_miss;
		end
		
		// Get tail pos
		if (mode == PLACEMENT) begin
			if (horizontal) begin
				tailRow = row;
				tailCol = col + 1;
			end else begin
				tailRow = row + 1;
				tailCol = col;
			end
		end else begin
			tailRow = UPPER_BOUND;
			tailCol = UPPER_BOUND;
		end
		// Send active ships
		active_ship = { row, col, tailRow, tailCol };
	end

endmodule
