module sync_fifo #(
    parameter WIDTH = 64,
    parameter DEPTH = 16
)(
    input logic              i_clk,
    input logic              i_rst_n,

    input logic [WIDTH-1:0]  i_data, // data we're receiving
    input logic              i_wr_en, // if we're writing to mem
    input logic              i_rd_en, // if we're reading from mem

    output logic [WIDTH-1:0] o_data, // data we're reading 
    output logic             o_mem_full, // Tells user mem is full
    output logic             o_mem_empty // Tells user mem is empty
);

logic [WIDTH-1:0] mem [DEPTH-1:0];  // width = 64, depth 16

logic [$clog2(DEPTH)-1:0]  wr_ptr;  // Where in our memory data is being written to
logic [$clog2(DEPTH)-1:0]  rd_ptr;  // Which memory location is being processed 

logic [$clog2(DEPTH):0]  counter;   // how many slots in our memory are taken

logic push; // Checks if you can write to memory  (!o_mem_full   && i_wt_en)
logic pop;  // Checks if you can read from memory (!o_mem_empty && i_rd_en)

assign o_mem_full = (counter == DEPTH);
assign o_mem_empty = (counter == 0);

assign push = (!o_mem_full && i_wr_en);
assign pop  = (!o_mem_empty && i_rd_en);



endmodule