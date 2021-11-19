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
parameter R_BLANK = 3'b000; 		// Cyan
parameter G_BLANK = 3'b111;
parameter B_BLANK = 2'b11;
parameter R_SHIP = 3'b111; 			// White
parameter G_SHIP = 3'b111;
parameter B_SHIP = 2'b11;
parameter R_ACTIVE_SHIP = 3'b000; 	// Green
parameter G_ACTIVE_SHIP = 3'b111;
parameter B_ACTIVE_SHIP = 2'b00;
parameter R_OVERLAP_SHIP = 3'b111; 	// Red
parameter G_OVERLAP_SHIP = 3'b000;
parameter B_OVERLAP_SHIP = 2'b00;
parameter R_HIT = 3'b111; 			// Magenta
parameter G_HIT = 3'b000;
parameter B_HIT = 2'b11;
parameter R_MISS = 3'b111; 			// Yellow
parameter G_MISS = 3'b111;
parameter B_MISS = 2'b00;

// Game board bounds
parameter HEADER = 80;
parameter MARGIN = 120;
parameter BLOCK_SIZE = 40;
parameter OUT_OF_BOUNDS = 10;
