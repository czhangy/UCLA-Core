// Cathode values
parameter ST_0000 = 7'b0000001;
parameter ST_0001 = 7'b1001111;
parameter ST_0010 = 7'b0010010;
parameter ST_0011 = 7'b0000110;
parameter ST_0100 = 7'b1001100;
parameter ST_0101 = 7'b0100100;
parameter ST_0110 = 7'b0100000;
parameter ST_0111 = 7'b0001111;
parameter ST_1000 = 7'b0000000;
parameter ST_1001 = 7'b0000100;
parameter ST_OFF = 7'b1111111;

// Anode values
parameter MINUTES_TENS_DIGIT = 4'b0111;
parameter MINUTES_ONES_DIGIT = 4'b1011;
parameter SECONDS_TENS_DIGIT = 4'b1101;
parameter SECONDS_ONES_DIGIT = 4'b1110;

// Limits
parameter MAX_ONES = 9;
parameter MAX_TENS = 5;

// Counters
parameter TWO_HZ_COUNT = 25000000;
parameter ONE_HZ_COUNT = 50000000;
parameter FAST_COUNT = 200000;
parameter BLINK_COUNT = 37500000;
parameter DB_COUNT = 65535;
