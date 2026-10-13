module sync_fifo #(
    parameter WIDTH = 64;
    parameter DEPTH = 16;
)(
    logic input [WIDTH-1:0] i_data, // data we're receiving
    logic input             i_rst_n,

    logic output [WIDTH-1:0] o_data // data we're reading 
);

logic [WIDTH-1:0] mem [DEPTH-1:0];  // width = 64, depth 16
logic [$clog2(DEPTH)-1:0]  wr_ptr;  // Where in our memory data is being written to
logic [$clog2(DEPTH)-1:0]  rd_ptr;  // Which memory location is being processed 
logic [4:0]  counter;               // how many slots in our memory are open

logic push_valid; // Checks if you can write to memory
logic pop_valid;  // Checks if you can read from memory



endmodule