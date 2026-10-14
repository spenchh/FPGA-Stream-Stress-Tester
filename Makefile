SIM           = verilator
TOPLEVEL_LANG = verilog

VERILOG_SOURCES = $(PWD)/sync_fifo.sv
COCOTB_TOPLEVEL = sync_fifo
COCOTB_TEST_MODULES = sync_fifo_tb

include $(shell cocotb-config --makefiles)/Makefile.sim