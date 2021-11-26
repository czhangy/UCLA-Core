`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    11:51:42 11/16/2021 
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
	input btnC,
	input btnL,
	input btnR,
	input btnU,
	input btnD,
	input sw0,
	input sw1,
	input sw2,
	input sw3,
	input sw4,
	input sw5,
	input sw6,
	input sw7,
	// Outputs
	output [BOARD_SIZE - 1:0] p1_board,
	output [BOARD_SIZE - 1:0] p2_board,
	output [2:0] p1_ships,
	output [2:0] p2_ships,
	output mode,
	output turn
);

	// Get constants
	`include "battleship_definitions.v"
	
	// Initialize game boards
	integer i;
	reg [BOARD_SIZE - 1:0] p1_board;
	reg [BOARD_SIZE - 1:0] p2_board;
	initial begin
		for (i = 0; i < BOARD_SIZE; i = i + 3) begin
			p1_board[i +: 3] = ARR_BLANK;
			p2_board[i +: 3] = ARR_BLANK;
		end
	end
	
	// Ship location info
	reg [3:0] ships_placed = 0;
	reg [2:0] ship_size = 5;
	reg [39:0] ship_coords;
	reg [ALL_SHIP_COORDS - 1:0] all_ship_coords;
	reg [3:0] row;
	reg [3:0] col;
	reg [2:0] spot_type;
	reg [9:0] ship_counter;
	reg [2:0] p1_ship_counter;
	reg [2:0] p2_ship_counter;
	integer c_i;
	
	// Initialize Player 1's 5 length ship
	initial begin
		for (i = 0; i < ship_size; i = i + 1) begin
			// Initial placement is horizontal
			if (sw0 == 0) begin
				ship_coords[i*8 +: 4] = 0;
				ship_coords[(i*8) + 4 +: 4] = i;
			
			// Initial placement is vertical
			end else begin
				ship_coords[i*8 +: 4] = i;
				ship_coords[(i*8) + 4 +: 4] = 0;
			end
		end
		for (i = 0; i < ship_size; i = i + 1) begin
			row = ship_coords[i*8 +: 4];
			col = ship_coords[(i*8) + 4 +: 4];
			p1_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
		end
	end
	
	always @(posedge btnC) begin
		// Placement mode -- attempt place ship
		if (mode == 0) begin
			reg valid_placement = 1'b1;
			
			// Check to see if there are any overlapping ships
			for (i = 0; i < BOARD_SIZE; i = i + 3) begin
				if (p1_board[i +: 3] == ARR_OVERLAP_SHIP or p2_board[i +: 3] == ARR_OVERLAP_SHIP)
					valid_placement = 0;
			end
			
			// Place the ship and select the next one
			if (valid_placement) begin
				
				// Solidify ship placement
				for (i = 0; i < BOARD_SIZE; i = i + 3) begin
					if (p1_board[i +: 3] == ARR_ACTIVE_SHIP)
						p1_board[i +: 3] == ARR_SHIP;
					if (p2_board[i +: 3] == ARR_ACTIVE_SHIP)
						p2_board[i +: 3] == ARR_SHIP;
				end
								
				ships_placed += 1;
				
				// Changing the current player
				if (ships_placed % 5 == 0)
					turn = ~turn;
				
				// Add coordinates to ship coordinate list
				for (i = 0; i < ship_size; i = i + 1) begin
					row = ship_coords[i*8 +: 4];
					col = ship_coords[(i*8) + 4 +: 4];
					
					// Player 1 ship length 5
					if (ships_placed == 1) begin
						all_ship_coords[(i*8) +: 4] = row;
						all_ship_coords[(i*8) + 4 +: 4] = col;
					// Player 1 ship length 4
					end else if (ships_placed == 2) begin
						all_ship_coords[(5*8) + (i*8) +: 4] = row;
						all_ship_coords[(5*8) + (i*8) + 4 +: 4] = col;
					// Player 1 ship length 3 (1)
					end else if (ships_placed == 3) begin
						all_ship_coords[(9*8) + (i*8) +: 4] = row;
						all_ship_coords[(9*8) + (i*8) + 4 +: 4] = col;
					// Player 1 ship length 3 (2)
					end else if (ships_placed == 4) begin
						all_ship_coords[(12*8) + (i*8) +: 4] = row;
						all_ship_coords[(12*8) + (i*8) + 4 +: 4] = col;
					// Player 1 ship length 2
					end else if (ships_placed  == 5) begin
						all_ship_coords[(15*8) + (i*8) +: 4] = row;
						all_ship_coords[(15*8) + (i*8) + 4 +: 4] = col;
					// Player 2 ship length 5
					end else if (ships_placed == 6) begin
						all_ship_coords[(17*8) + (i*8) +: 4] = row;
						all_ship_coords[(17*8) + (i*8) + 4 +: 4] = col;
					// Player 2 ship length 4
					end else if (ships_placed == 7) begin
						all_ship_coords[(22*8) + (i*8) +: 4] = row;
						all_ship_coords[(22*8) + (i*8) + 4 +: 4] = col;
					// Player 2 ship length 3 (1)
					end else if (ships_placed == 8) begin
						all_ship_coords[(26*8) + (i*8) +: 4] = row;
						all_ship_coords[(26*8) + (i*8) + 4 +: 4] = col;
					// Player 2 ship length 3 (2)
					end else if (ships_placed == 9) begin
						all_ship_coords[(29*8) + (i*8) +: 4] = row;
						all_ship_coords[(29*8) + (i*8) + 4 +: 4] = col;
					// Player 2 ship length 2
					end else if (ships_placed  == 10) begin
						all_ship_coords[(32*8) + (i*8) +: 4] = row;
						all_ship_coords[(32*8) + (i*8) + 4 +: 4] = col;
					end
				end
				
				// Last ship is placed
				if (ships_placed == 10) begin
					mode = 1;
					ships_placed = 0;
					
				// More ships left to place
				end else begin
				
					// Length 5 ship (1 each)
					if (ships_placed % 5 == 0)
						ship_size = 5;
						
					// Length 4 ship (1 each)
					else if (ships_placed % 5 == 1)
						ship_size = 4;
						
					// Length 3 ship (2 each)
					else if (ships_placed % 5 == 2 or ships_placed % 5 == 3)
						ship_size = 3;
						
					// Length 2 ship (1 each)
					else if (ships_placed % 5 == 4)
						ship_size = 2;
					
					// Initial ship placement
					for (i = 0; i < ship_size; i = i + 1) begin
						// Initial placement is horizontal
						if (sw0 == 0) begin
							ship_coords[i*8 +: 4] = 0;
							ship_coords[(i*8) + 4 +: 4] = i;
						
						// Initial placement is vertical
						end else begin
							ship_coords[i*8 +: 4] = i;
							ship_coords[(i*8) + 4 +: 4] = 0;
						end
						
						// Place ship for Player 1
						if (turn == 0) begin
							spot_type = p1_board[(row * 30) + (col * 3) +: 3];
							if (spot_type == SHIP)
								p1_board[(row * 30) + (col * 3) +: 3] = OVERLAP_SHIP;
							else
								p1_board[(row * 30) + (col * 3) +: 3] = ACTIVE_SHIP;
						
						// Place ship for Player 2						
						end else begin
							spot_type = p2_board[(row * 30) + (col * 3) +: 3];
							if (spot_type == SHIP)
								p2_board[(row * 30) + (col * 3) +: 3] = OVERLAP_SHIP;
							else
								p2_board[(row * 30) + (col * 3) +: 3] = ACTIVE_SHIP;
						end
					end				
				end
			end

		// Game mode -- strike
		end else begin
			row = {sw7, sw6, sw5, sw4};
			col = {sw3, sw2, sw1, sw0};
			
			// Player 1 attacking Player 2
			if (turn == 0) begin
				spot_type = p2_board[(row * 30) + (col * 3) +: 3];
				if (spot_type == ARR_BLANK) begin
					p2_board[(row * 30) + (col * 3) +: 3] = ARR_MISS;					
				end else if (spot_type == ARR_SHIP) begin
					p2_board[(row * 30) + (col * 3) +: 3] = ARR_HIT;
				end
				
			// Player 2 attacking Player 1
			end else begin
				spot_type = p1_board[(row * 30) + (col * 3) +: 3];
				if (spot_type == ARR_BLANK) begin
					p1_board[(row * 30) + (col * 3) +: 3] = ARR_MISS;					
				end else if (spot_type == ARR_SHIP) begin
					p1_board[(row * 30) + (col * 3) +: 3] = ARR_HIT;
				end
			end
			
			turn = ~turn;
			
		end
	end
	
	always @(posedge btnL) begin
		// Placement mode -- move ship left
		if (mode == 0) begin
		
			// Make sure the move is valid
			if (ship_coords[0 +: 4] != 0) begin
				
				// Remove the active ship
				for (i = 0; i < ship_size; i = i + 1) begin
					row = ship_coords[i*8 +: 4];
					col = ship_coords[(i*8) + 4 +: 4];
					
					// Player 1
					if (turn == 0) begin
						spot_type = p1_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_ACTIVE_SHIP)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_BLANK;
						else if (spot_type == ARR_OVERLAP_SHIP)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_SHIP;
						
					// Player 2
					end else begin
						spot_type = p2_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_ACTIVE_SHIP)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_BLANK;
						else if (spot_type == ARR_OVERLAP_SHIP)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_SHIP;

					end
				end
				
				// Update the coordinates
				for (i = 0; i < ship_size; i = i + 1) begin
					row = ship_coords[i*8 +: 4];
					row = row - 1;
					ship_coords[i*8 +: 4] = row;
				end
				
				// Replace the active ship with new position
				for (i = 0; i < ship_size; i = i + 1) begin
					row = ship_coords[i*8 +: 4];
					col = ship_coords[(i*8) + 4 +: 4];
					
					// Player 1
					if (turn == 0) begin
						spot_type = p1_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_BLANK)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
						else if (spot_type == ARR_SHIP)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_OVERLAP_SHIP;
						
					// Player 2
					end else begin
						spot_type = p2_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_BLANK)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
						else if (spot_type == ARR_SHIP)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_OVERLAP_SHIP;

					end
				end
			end

		//Game mode -- reset
		end else begin
			for (i = 0; i < BOARD_SIZE; i = i + 3) begin
				p1_board[i +: 3] = ARR_BLANK;
				p2_board[i +: 3] = ARR_BLANK;
			end
			mode = 0;
			ships_placed = 0;
			ship_size = 5;
			for (i = 0; i < ship_size; i = i + 1) begin
				ship_coords[i*8 +: 4] = 0;
				ship_coords[(i*8) + 4 +: 4] = i;
			end
			for (i = 0; i < ship_size; i = i + 1) begin
				row = ship_coords[i*8 +: 4];
				col = ship_coords[(i*8) + 4 +: 4];
				p1_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
			end
		end
	end
	
	always @(posedge btnR) begin
		// Placement mode -- move ship right
		if (mode == 0) begin
			
			// Make sure the move is valid
			if (ship_coords[(ship_size-1) * 8 +: 4] != 9) begin
				
				// Remove the active ship
				for (i = 0; i < ship_size; i = i + 1) begin
					row = ship_coords[i*8 +: 4];
					col = ship_coords[(i*8) + 4 +: 4];
					
					// Player 1
					if (turn == 0) begin
						spot_type = p1_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_ACTIVE_SHIP)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_BLANK;
						else if (spot_type == ARR_OVERLAP_SHIP)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_SHIP;
						
					// Player 2
					end else begin
						spot_type = p2_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_ACTIVE_SHIP)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_BLANK;
						else if (spot_type == ARR_OVERLAP_SHIP)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_SHIP;

					end
				end
				
				// Update the coordinates
				for (i = 0; i < ship_size; i = i + 1) begin
					row = ship_coords[i*8 +: 4];
					row = row + 1;
					ship_coords[i*8 +: 4] = row;
				end
				
				// Replace the active ship with new position
				for (i = 0; i < ship_size; i = i + 1) begin
					row = ship_coords[i*8 +: 4];
					col = ship_coords[(i*8) + 4 +: 4];
					
					// Player 1
					if (turn == 0) begin
						spot_type = p1_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_BLANK)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
						else if (spot_type == ARR_SHIP)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_OVERLAP_SHIP;
						
					// Player 2
					end else begin
						spot_type = p2_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_BLANK)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
						else if (spot_type == ARR_SHIP)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_OVERLAP_SHIP;

					end
				end
			end
		end
	end
	
	always @(posedge btnU) begin
		// Placement mode -- move ship up
		if (mode == 0) begin
			
			// Make sure the move is valid
			if (ship_coords[4 +: 4] != 0) begin
				
				// Remove the active ship
				for (i = 0; i < ship_size; i = i + 1) begin
					row = ship_coords[i*8 +: 4];
					col = ship_coords[(i*8) + 4 +: 4];
					
					// Player 1
					if (turn == 0) begin
						spot_type = p1_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_ACTIVE_SHIP)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_BLANK;
						else if (spot_type == ARR_OVERLAP_SHIP)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_SHIP;
						
					// Player 2
					end else begin
						spot_type = p2_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_ACTIVE_SHIP)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_BLANK;
						else if (spot_type == ARR_OVERLAP_SHIP)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_SHIP;

					end
				end
				
				// Update the coordinates
				for (i = 0; i < ship_size; i = i + 1) begin
					col = ship_coords[(i*8) + 4 +: 4];
					col = col - 1;
					ship_coords[(i*8) + 4 +: 4] = col;
				end
				
				// Replace the active ship with new position
				for (i = 0; i < ship_size; i = i + 1) begin
					row = ship_coords[i*8 +: 4];
					col = ship_coords[(i*8) + 4 +: 4];
					
					// Player 1
					if (turn == 0) begin
						spot_type = p1_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_BLANK)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
						else if (spot_type == ARR_SHIP)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_OVERLAP_SHIP;
						
					// Player 2
					end else begin
						spot_type = p2_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_BLANK)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
						else if (spot_type == ARR_SHIP)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_OVERLAP_SHIP;

					end
				end
			end
		end
	end
	
	always @(posedge btnD) begin
		// Placement mode -- move ship down
		if (mode == 0) begin
			
			// Make sure the move is valid
			if (ship_coords[(ship_size-1) * 8 + 4 +: 4] != 9) begin
				
				// Remove the active ship
				for (i = 0; i < ship_size; i = i + 1) begin
					row = ship_coords[i*8 +: 4];
					col = ship_coords[(i*8) + 4 +: 4];
					
					// Player 1
					if (turn == 0) begin
						spot_type = p1_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_ACTIVE_SHIP)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_BLANK;
						else if (spot_type == ARR_OVERLAP_SHIP)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_SHIP;
						
					// Player 2
					end else begin
						spot_type = p2_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_ACTIVE_SHIP)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_BLANK;
						else if (spot_type == ARR_OVERLAP_SHIP)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_SHIP;

					end
				end
				
				// Update the coordinates
				for (i = 0; i < ship_size; i = i + 1) begin
					col = ship_coords[(i*8) + 4 +: 4];
					col = col + 1;
					ship_coords[(i*8) + 4 +: 4] = col;
				end
				
				// Replace the active ship with new position
				for (i = 0; i < ship_size; i = i + 1) begin
					row = ship_coords[i*8 +: 4];
					col = ship_coords[(i*8) + 4 +: 4];
					
					// Player 1
					if (turn == 0) begin
						spot_type = p1_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_BLANK)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
						else if (spot_type == ARR_SHIP)
							p1_board[(row * 30) + (col * 3) +: 3] = ARR_OVERLAP_SHIP;
						
					// Player 2
					end else begin
						spot_type = p2_board[(row * 30) + (col * 3) +: 3];
						if (spot_type == ARR_BLANK)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
						else if (spot_type == ARR_SHIP)
							p2_board[(row * 30) + (col * 3) +: 3] = ARR_OVERLAP_SHIP;

					end
				end
			end
		end
	end
	
	always @(posedge sw0) begin
		// Placement mode -- orient ship vertically
		if (mode == 0) begin
			// Remove the active ship
			for (i = 0; i < ship_size; i = i + 1) begin
				row = ship_coords[i*8 +: 4];
				col = ship_coords[(i*8) + 4 +: 4];
				
				// Player 1
				if (turn == 0) begin
					spot_type = p1_board[(row * 30) + (col * 3) +: 3];
					if (spot_type == ARR_ACTIVE_SHIP)
						p1_board[(row * 30) + (col * 3) +: 3] = ARR_BLANK;
					else if (spot_type == ARR_OVERLAP_SHIP)
						p1_board[(row * 30) + (col * 3) +: 3] = ARR_SHIP;
					
				// Player 2
				end else begin
					spot_type = p2_board[(row * 30) + (col * 3) +: 3];
					if (spot_type == ARR_ACTIVE_SHIP)
						p2_board[(row * 30) + (col * 3) +: 3] = ARR_BLANK;
					else if (spot_type == ARR_OVERLAP_SHIP)
						p2_board[(row * 30) + (col * 3) +: 3] = ARR_SHIP;

				end
			end
			
			// Update the coordinates
			row = ship_coords[0 +: 4];
			col = ship_coords[4 +: 4];
			// Shift upwards so there is room to rotate
			if ((row + ship_size) > 10) begin
				for (i = 0; i < ship_size; i = i + 1) begin
					ship_coords[(i*8) +: 4] = 10 - ship_size;
				end
				row = 10 - ship_size;
			end
			// Rotate row vertically
			for (i = 0; i < ship_size; i = i + 1) begin
				ship_coords[(i*8) +: 4] = row + i;
				ship_coords[(i*8) + 4 +: 4] = col;
			end
			
			// Replace the active ship with new position
			for (i = 0; i < ship_size; i = i + 1) begin
				row = ship_coords[i*8 +: 4];
				col = ship_coords[(i*8) + 4 +: 4];
				
				// Player 1
				if (turn == 0) begin
					spot_type = p1_board[(row * 30) + (col * 3) +: 3];
					if (spot_type == ARR_BLANK)
						p1_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
					else if (spot_type == ARR_SHIP)
						p1_board[(row * 30) + (col * 3) +: 3] = ARR_OVERLAP_SHIP;
					
				// Player 2
				end else begin
					spot_type = p2_board[(row * 30) + (col * 3) +: 3];
					if (spot_type == ARR_BLANK)
						p2_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
					else if (spot_type == ARR_SHIP)
						p2_board[(row * 30) + (col * 3) +: 3] = ARR_OVERLAP_SHIP;
				end
			end
		end
	end
	
	always @(negedge sw0) begin
		// Placement mode -- orient ship horizontally
		if (mode == 0) begin
			// Remove the active ship
			for (i = 0; i < ship_size; i = i + 1) begin
				row = ship_coords[i*8 +: 4];
				col = ship_coords[(i*8) + 4 +: 4];
				
				// Player 1
				if (turn == 0) begin
					spot_type = p1_board[(row * 30) + (col * 3) +: 3];
					if (spot_type == ARR_ACTIVE_SHIP)
						p1_board[(row * 30) + (col * 3) +: 3] = ARR_BLANK;
					else if (spot_type == ARR_OVERLAP_SHIP)
						p1_board[(row * 30) + (col * 3) +: 3] = ARR_SHIP;
					
				// Player 2
				end else begin
					spot_type = p2_board[(row * 30) + (col * 3) +: 3];
					if (spot_type == ARR_ACTIVE_SHIP)
						p2_board[(row * 30) + (col * 3) +: 3] = ARR_BLANK;
					else if (spot_type == ARR_OVERLAP_SHIP)
						p2_board[(row * 30) + (col * 3) +: 3] = ARR_SHIP;

				end
			end
			
			// Update the coordinates
			row = ship_coords[0 +: 4];
			col = ship_coords[4 +: 4];
			// Shift upwards so there is room to rotate
			if ((col + ship_size) > 10) begin
				for (i = 0; i < ship_size; i = i + 1) begin
					ship_coords[(i*8) +: 4] = 10 - ship_size;
				end
				col = 10 - ship_size;
			end
			// Rotate column horizontally
			for (i = 0; i < ship_size; i = i + 1) begin
				ship_coords[(i*8) +: 4] = row;
				ship_coords[(i*8) + 4 +: 4] = col + i;
			end
			
			// Replace the active ship with new position
			for (i = 0; i < ship_size; i = i + 1) begin
				row = ship_coords[i*8 +: 4];
				col = ship_coords[(i*8) + 4 +: 4];
				
				// Player 1
				if (turn == 0) begin
					spot_type = p1_board[(row * 30) + (col * 3) +: 3];
					if (spot_type == ARR_BLANK)
						p1_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
					else if (spot_type == ARR_SHIP)
						p1_board[(row * 30) + (col * 3) +: 3] = ARR_OVERLAP_SHIP;
					
				// Player 2
				end else begin
					spot_type = p2_board[(row * 30) + (col * 3) +: 3];
					if (spot_type == ARR_BLANK)
						p2_board[(row * 30) + (col * 3) +: 3] = ARR_ACTIVE_SHIP;
					else if (spot_type == ARR_SHIP)
						p2_board[(row * 30) + (col * 3) +: 3] = ARR_OVERLAP_SHIP;

				end
			end
		end
	end
	
	// Update the number of ships for each player
	always @(*) begin
		ship_counter = 0;
		p1_ship_counter = 0;
		p2_ship_counter = 0;
		
		// Check for the ships that are hit
		for (c_i = 0; c_i < 34; c_i = c_i + 1) begin
			row = all_ship_coords[(c_i*8) +: 4];
			col = all_ship_coords[(c_i*8) + 4 +: 4];
			
			// Checking ships for Player 1
			if (c_i < 17) begin
				spot_type = p1_board[(row * 30) + (col * 3) +: 3];
			
				// Length 5 ship
				if (c_i < 5 && spot_type == SHIP)
					ship_counter[0] = 1'b1;
				// Length 4 ship
				else if (c_i < 9 && spot_type == SHIP)
					ship_counter[1] = 1'b1;
				// Length 3 ship (1)
				else if (c_i < 12 && spot_type == SHIP)
					ship_counter[2] = 1'b1;
				// Length 3 ship (2)
				else if (c_i < 15 && spot_type == SHIP)
					ship_counter[3] = 1'b1;
				// Length 2 ship
				else if (spot_type == SHIP)
					ship_counter[4] = 1'b1;
			
			// Checking ships for Player 2
			end else begin
				spot_type = p2_board[(row * 30) + (col * 3) +: 3];
			
				// Length 5 ship
				if ((c_i % 17) < 5 && spot_type == SHIP)
					ship_counter[5] = 1'b1;
				// Length 4 ship
				else if ((c_i % 17) < 9 && spot_type == SHIP)
					ship_counter[6] = 1'b1;
				// Length 3 ship (1)
				else if ((c_i % 17) < 12 && spot_type == SHIP)
					ship_counter[7] = 1'b1;
				// Length 3 ship (2)
				else if ((c_i % 17) < 15 && spot_type == SHIP)
					ship_counter[8] = 1'b1;
				// Length 2 ship
				else if (spot_type == SHIP)
					ship_counter[9] = 1'b1;
				
			end
		end
		
		// Find the number of active ships
		for (c_i = 0; c_i < 10; c_i = c_i + 1) begin
			if (c_i < 5)
				p1_ship_counter += ship_counter[c_i];
			else
				p2_ship_counter += ship_counter[c_i];
		end
		
		// Placement mode
		if (mode == 0) begin
			if (ships_placed < 5) begin
				p1_ships = ships_placed;
				p2_ships = 0;
			end else begin
				p1_ships = 5;
				p2_ships = ships_placed - 5;
			end
			
		// Game mode
		end else begin
			p1_ships = p1_ship_counter;
			p2_ships = p2_ship_counter;
		end
	end

endmodule
