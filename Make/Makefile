SIM = verilator
TOPLEVEL_LANG = verilog

VERILOG_SOURCES = $(abspath ../rtl/sync_fifo.sv)
COCOTB_TOPLEVEL = sync_fifo
COCOTB_TEST_MODULES = sync_fifo_tb

export PYTHONPATH := $(abspath ../verif):$(PYTHONPATH)

include $(shell cocotb-config --makefiles)/Makefile.sim