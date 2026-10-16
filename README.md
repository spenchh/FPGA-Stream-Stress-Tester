# FPGA Stream Stress Tester

A SystemVerilog project for testing how streaming hardware handles bursts, backpressure, missing records, and corrupted data. The goal is to build a programmable traffic generator and fault injector with FIFO buffering, verify the design using Python/cocotb, and demonstrate it on a Basys 3 FPGA.

## Current status

The synchronous FIFO RTL is implemented, and its cocotb testbench has expanded beyond the initial single-word test to include ordering, full/empty conditions, simultaneous operations, wraparound, reset with queued data, and idle retention. Additional directed checks have been written for simultaneous requests at full/empty boundaries and registered output holding.

The latest combined testbench still needs a confirmed simulation run after correcting the appended tests' indentation and increasing the timeout to 5 microseconds. Test descriptions below identify written scenarios, not a claim of exhaustive verification.

The next module is `traffic_gen.sv`. The asynchronous FIFO, fault injector, programmable sink, and FPGA integration are planned.

## Architecture

| Block | Purpose | Status |
| --- | --- | --- |
| `sync_fifo.sv` | Buffer data within one clock domain | RTL implemented; directed testbench written |
| `traffic_gen.sv` | Generate numbered records with configurable bursts and gaps | Next module |
| Asynchronous FIFO | Transfer records between clock domains | Planned |
| Fault injector | Intentionally drop records or flip selected payload bits | Planned |
| Programmable sink | Create receiver stalls and check received traffic | Planned |
| Statistics and host control | Configure runs and report accepted records, faults, and errors | Planned |

The first integrated version will use one clock. A later version will add an asynchronous FIFO between the generator and processing clock domains.

## Repository organization

| Path | Contents |
| --- | --- |
| `rtl/sync_fifo.sv` | Synchronous FIFO RTL |
| `rtl/traffic_gen.sv` | Planned traffic generator |
| `verif/sync_fifo_tb.py` | Cocotb FIFO testbench |
| `make/Makefile` | Simulator build and test configuration |
| `make/results.xml` | Generated test results; exclude from version control |
| `README.md` | Project overview, current status, and usage |

## Synchronous FIFO

Default configuration: **64-bit words, 16 entries**. The current pointer implementation requires a power-of-two depth of at least 2.

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

During normal operation, a write is accepted on a rising edge when `i_wr_en` is high and the FIFO is not full. A read is accepted when `i_rd_en` is high and the FIFO is not empty. Both acceptance decisions use the state before that edge. The producer must request a write only when it intends to store the value on `i_data`.

When both operations are accepted, both pointers advance and occupancy stays unchanged. At full, simultaneous requests accept only the read. At empty, simultaneous requests accept only the write; there is no same-edge bypass.

Reset takes priority over requests and clears the pointers and occupancy counter. Memory and `o_data` are not reset. After reset, output data becomes meaningful following an accepted read and holds until another accepted read. Reading the final entry makes the FIFO empty while leaving that entry's value on `o_data`.

## FIFO verification

The directed cocotb testbench includes:

- Reset and single-word write/read checks.
- Multiple-word ordering and simultaneous read/write at partial occupancy.
- Filling to capacity and draining to empty.
- Rejected writes when full and reads when empty.
- Pointer wraparound through continued traffic.
- Reset with unread entries, followed by new writes and reads.
- Retaining queued data while requests are disabled.
- Added checks for simultaneous requests while full and while empty.
- Added checks that `o_data` holds during idle cycles and rejected reads.

The current directed sequence assumes `DEPTH = 16`. An independent reference queue, seeded randomized tests, parameter sweeps, and SystemVerilog Assertions are future verification work.

## Running simulation

Use **cocotb 2.x, Verilator, and GNU Make** in the same working environment.

For the folder layout above, `make/Makefile` contains:

```makefile
SIM = verilator
TOPLEVEL_LANG = verilog

VERILOG_SOURCES = $(abspath ../rtl/sync_fifo.sv)
COCOTB_TOPLEVEL = sync_fifo
COCOTB_TEST_MODULES = sync_fifo_tb

export PYTHONPATH := $(abspath ../verif):$(PYTHONPATH)

include $(shell cocotb-config --makefiles)/Makefile.sim
```

From the project root:

```bash
cd make
make
```

Tests drive inputs on falling edges and check outputs after `RisingEdge` followed by `ReadOnly`. Use a **5 microsecond timeout** for the combined directed sequence. Keep the added boundary tests outside the preceding read loop.

Exclude generated files from version control:

```gitignore
sim_build/
__pycache__/
*.pyc
results.xml
*.vcd
*.fst
```

## Next module

Implement `traffic_gen.sv` as a source of numbered words for the FIFO. Start with continuous generation and full handling: advance the sequence only after an accepted write, and retain the pending word while blocked. Then add configurable burst lengths and gaps between bursts.

Verify the generator independently before connecting it to the FIFO in a top-level module.

## Planned hardware demonstration

Use the Basys 3 to run the generator, FIFO, and sequence checker inside the FPGA. Switches will control generation and receiver stalls; LEDs will show full, empty, and a latched error indication. Synchronize external controls and debounce buttons where needed. UART configuration and result reporting can follow later.

## Next steps

- [x] Implement synchronous FIFO storage, pointers, and occupancy logic.
- [x] Write directed tests for reset, ordering, boundaries, simultaneous operations, and wraparound.
- [x] Write additional boundary-request and output-hold checks.
- [ ] Confirm the complete corrected testbench passes simulation.
- [ ] Add a reference queue, seeded randomized traffic, and parameter sweeps.
- [ ] Add SVA for occupancy and state-update invariants.
- [ ] Implement and verify the traffic generator.
- [ ] Integrate the generator, FIFO, and receiver with correct read timing.
- [ ] Add burst/gap control, sink stalls, and fault injection.
- [ ] Implement the asynchronous FIFO and review CDC constraints.
- [ ] Collect post-route timing/resource reports and demonstrate operation on Basys 3.

## Connection to market-data research

The tester is intended to become reusable infrastructure for the market-data datapath project. Controlled traffic and stalls will help exercise queues, check record ordering, and measure congestion. Symbol-targeted workloads and feedback-guided generation are later extensions; the current FIFO is not yet integrated into that datapath.
