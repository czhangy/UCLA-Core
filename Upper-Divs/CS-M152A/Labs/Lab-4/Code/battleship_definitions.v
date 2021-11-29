// Debouncing limit
parameter DB_COUNT = 65535;

// Clock divider limits
parameter CLK_SSD_COUNT = 200000;
parameter CLK_VGA_COUNT = 2;

// Clock divider bits
parameter SSD_BIT = 16;
parameter VGA_BIT = 1;

// SSD cathodes
parameter ST_000 = 7'b1000000;
parameter ST_001 = 7'b1111001;
parameter ST_010 = 7'b0100100;
parameter ST_011 = 7'b0110000;
parameter ST_100 = 7'b0011001;
parameter ST_101 = 7'b0010010;
parameter ST_OFF = 7'b1111111;
parameter ST_P = 7'b0001100;

// SSD anodes
parameter P1_LEFT = 4'b0111;
parameter P1_RIGHT = 4'b1011;
parameter P2_LEFT = 4'b1101;
parameter P2_RIGHT = 4'b1110;

// VGA constants
parameter HPIXELS = 800;
parameter VLINES = 521;
parameter HPULSE = 96;
parameter VPULSE = 2;
parameter HBP = 144;
parameter HFP = 784;
parameter VBP = 31;
parameter VFP = 511;

// Array codes
parameter ARR_BLANK = 0;
parameter ARR_SHIP = 1;
parameter ARR_ACTIVE_SHIP = 2;
parameter ARR_OVERLAP_SHIP = 3;
parameter ARR_HIT = 4;
parameter ARR_MISS = 5;

// Game board colors
parameter BLACK = 0;
parameter BLANK = 8'b00011111; 		    // Cyan
parameter SHIP = 8'b11111111; 	        // White
parameter ACTIVE_SHIP = 8'b00011100; 	// Green
parameter OVERLAP_SHIP = 8'b11100000; 	// Red
parameter HIT = 8'b11100011; 			// Magenta
parameter MISS = 8'b11111100; 			// Yellow

// Game board bounds
parameter BOARD_SIZE = 300;
parameter OUT_OF_BOUNDS = 10;
parameter HEADER = 80;
parameter MARGIN = 120;
parameter BLOCK_SIZE = 40;
parameter TOP_BORDER = 0;
parameter LEFT_BORDER = 0
parameter BOTTOM_BORDER = BLOCK_SIZE - 1;
parameter RIGHT_BORDER = BLOCK_SIZE - 1;

// Ship coordinates
parameter ALL_SHIP_COORDS = 272;
