# FPGA Stream Stress Tester

A SystemVerilog project for testing how streaming hardware handles bursts, backpressure, missing records, and corrupted data. The goal is to build a programmable traffic source and fault injector with FIFO buffering, then verify the system using Python/cocotb and demonstrate it on an FPGA.

## Current status

The first synchronous FIFO is implemented. The initial cocotb test checks reset, a single write, and a single read with a data comparison. This is an early functional milestone; full boundary and randomized verification are still in progress.

The traffic generator, asynchronous FIFO, fault injector, programmable sink, and board integration are planned.

## Planned architecture

| Block | Purpose | Status |
| --- | --- | --- |
| Synchronous FIFO | Buffer data within one clock domain | Implemented, initial test written |
| Traffic generator | Generate numbered records with configurable bursts and gaps | Planned |
| Asynchronous FIFO | Move records between clock domains | Planned |
| Fault injector | Intentionally drop records or flip selected payload bits | Planned |
| Programmable sink | Create receiver stalls and check received traffic | Planned |
| Statistics and host control | Report results and configure hardware tests | Planned |

The first integrated version will use one clock. A later version will cross from the generator clock domain to the processing clock domain through an asynchronous FIFO.

## Synchronous FIFO

Default configuration: **64-bit words, 16 entries**. The current pointer implementation assumes a power-of-two depth of at least 2.

| Signal | Direction | Meaning |
| --- | --- | --- |
| `i_clk` | Input | Clock |
| `i_rst_n` | Input | Synchronous active-low reset |
| `i_data` | Input | Word presented for writing |
| `i_wr_en` | Input | Write request |
| `i_rd_en` | Input | Read request |
| `o_data` | Output | Registered result of the last accepted read |
| `o_mem_full` | Output | All entries are occupied |
| `o_mem_empty` | Output | No unread entries remain |

A write is accepted on a rising edge when `i_wr_en` is high and the FIFO is not full. A read is accepted when `i_rd_en` is high and the FIFO is not empty. The producer must request a write only when it intends to store the value on `i_data`.

Accepted writes and reads can occur on the same edge; occupancy then stays unchanged. At full, simultaneous requests accept only the read. At empty, simultaneous requests accept only the write.

Reset clears the pointers and occupancy counter. Memory and `o_data` are not reset. Output data becomes meaningful after an accepted read and remains unchanged until another accepted read. Reading the final entry makes the FIFO empty while leaving that entry's value on `o_data`.

## Simulation

The intended toolchain is **cocotb 2.x, Verilator, and GNU Make**. Keep the Python testbench, RTL, and Makefile in the paths specified by the Makefile.

From the directory containing the Makefile:

```bash
make
```

Set `COCOTB_TOPLEVEL` to `sync_fifo` and `COCOTB_TEST_MODULES` to the Python test filename without `.py`. Set `VERILOG_SOURCES` to the actual RTL path. Run in the environment where cocotb, Verilator, and Make are installed.

Tests drive inputs on falling edges and check registered results after `RisingEdge` followed by `ReadOnly`.

## Next steps

- [x] Implement synchronous FIFO storage, pointers, and occupancy logic.
- [x] Write a reset and single-write/read cocotb test.
- [ ] Verify multiple words are returned in order.
- [ ] Test full/empty boundaries, blocked requests, and simultaneous operations.
- [ ] Exercise pointer wraparound and reset during traffic.
- [ ] Add an independent scoreboard and seeded randomized tests.
- [ ] Add SVA for occupancy and state-update invariants.
- [ ] Implement burst generation, fault injection, and sink stalls.
- [ ] Implement and review the asynchronous FIFO and CDC constraints.
- [ ] Collect post-route timing/resource results and run an FPGA demonstration.

## Completion target

Demonstrate repeatable fault scenarios, correct buffering and ordering, and a test that catches an intentionally introduced receiver bug. Measure throughput, latency, resource usage, and the effect of FIFO depth on burst tolerance. Report measured results as each milestone is completed.

Estimated effort: **30–45 hours for the simulation version**, or **45–70 hours including FPGA bring-up and implementation review**. Most development can be done on a laptop; the board is needed for the final hardware validation.
