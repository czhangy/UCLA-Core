// Debouncing limit
parameter DB_COUNT = 65535;

// Clock divider limits
parameter CLK_SSD_COUNT = 200000;
parameter CLK_VGA_COUNT = 2;

// SSD values
parameter ST_000 = 7'b1000000;
parameter ST_001 = 7'b1111001;
parameter ST_010 = 7'b0100100;
parameter ST_011 = 7'b0110000;
parameter ST_100 = 7'b0011001;
parameter ST_101 = 7'b0010010;
parameter ST_OFF = 7'b1111111;
parameter P1_LEFT = 4'b0111;
parameter P1_RIGHT = 4'b1011;
parameter P2_LEFT = 4'b1101;
parameter P2_RIGHT = 4'b1110;

// VGA values
parameter HPIXELS = 1160;	// horizontal pixels per line
parameter VLINES = 1024; 	// vertical lines per frame
parameter HPULSE = 96; 		// hsync pulse length
parameter VPULSE = 2; 		// vsync pulse length
parameter HBP = 140; 		// end of horizontal back porch
parameter HFP = 1140; 		// beginning of horizontal front porch
parameter VBP = 12; 		// end of vertical back porch
parameter VFP = 1012; 		// beginning of vertical front porch

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
parameter ROW_0_MIN = 12;
parameter ROW_0_MAX = 111;
parameter ROW_1_MIN = 112;
parameter ROW_1_MAX = 211;
parameter ROW_2_MIN = 212;
parameter ROW_2_MAX = 311;
parameter ROW_3_MIN = 312;
parameter ROW_3_MAX = 411;
parameter ROW_4_MIN = 412;
parameter ROW_4_MAX = 511;
parameter ROW_5_MIN = 512;
parameter ROW_5_MAX = 611;
parameter ROW_6_MIN = 612;
parameter ROW_6_MAX = 711;
parameter ROW_7_MIN = 712;
parameter ROW_7_MAX = 811;
parameter ROW_8_MIN = 812;
parameter ROW_8_MAX = 911;
parameter ROW_9_MIN = 912;
parameter ROW_9_MAX = 1011;
parameter COL_0_MIN = 140;
parameter COL_0_MAX = 239;
parameter COL_1_MIN = 240;
parameter COL_1_MAX = 339;
parameter COL_2_MIN = 340;
parameter COL_2_MAX = 439;
parameter COL_3_MIN = 440;
parameter COL_3_MAX = 539;
parameter COL_4_MIN = 540;
parameter COL_4_MAX = 639;
parameter COL_5_MIN = 640;
parameter COL_5_MAX = 739;
parameter COL_6_MIN = 740;
parameter COL_6_MAX = 839;
parameter COL_7_MIN = 840;
parameter COL_7_MAX = 939;
parameter COL_8_MIN = 940;
parameter COL_8_MAX = 1039;
parameter COL_9_MIN = 1040;
parameter COL_9_MAX = 1139;
