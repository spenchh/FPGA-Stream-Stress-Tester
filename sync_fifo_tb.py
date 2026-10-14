import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, FallingEdge, ReadOnly

"""
Set the inputs: Assert active-low reset with i_rst_n = 0, and disable read/write requests.
Start the clock: A 10 ns period means a 100 MHz clock, starting low.
Wait for a rising edge: Your FIFO’s synchronous reset executes on that edge, clearing its pointers and counter.
Wait for ReadOnly(): Let the HDL updates settle so you can inspect the resulting outputs.
"""
@cocotb.test(timeout_time=1, timeout_unit="us") # Max sim time allowed
async def test(dut):
    dut.i_clk.value = 0
    dut.i_rst_n.value = 0

    dut.i_data.value = 0
    dut.i_wr_en.value = 0
    dut.i_rd_en.value = 0

    clock = Clock(dut.i_clk, 10, unit="ns") # Clock timing - 10ns clock period
    clock.start(start_high=False)

    await RisingEdge(dut.i_clk)
    await ReadOnly() # Allows NBA region to settle


    