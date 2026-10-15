import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, FallingEdge, ReadOnly

# For a word do: dut.i_data.value = int.from_bytes(b"Hello", byteorder="big")

"""
Set the inputs: Assert active-low reset with i_rst_n = 0, and disable read/write requests.
Start the clock: A 10 ns period means a 100 MHz clock, starting low.
Wait for a rising edge: Your FIFO’s synchronous reset executes on that edge, clearing its pointers and counter.
Wait for ReadOnly(): Let the HDL updates settle so you can inspect the resulting outputs.
"""
@cocotb.test(timeout_time=1, timeout_unit="us") # Max sim time allowed
async def test(dut):
    # Reset Test
    dut.i_clk.value = 0
    dut.i_rst_n.value = 0

    dut.i_data.value = 0
    dut.i_wr_en.value = 0
    dut.i_rd_en.value = 0

    clock = Clock(dut.i_clk, 10, unit="ns") # Clock timing - 10ns clock period
    clock.start(start_high=False)

    await RisingEdge(dut.i_clk)
    await ReadOnly() # Allows NBA region to settle

    assert int(dut.o_mem_full.value)  == 0, "memory shouldn't be full"
    assert int(dut.o_mem_empty.value) == 1, "memory should be empty"

    # Writing 1 value into memory, counter = 1
    await FallingEdge(dut.i_clk)
    dut.i_rst_n.value = 1
    dut.i_data.value = 1234567890123456
    dut.i_wr_en.value = 1

    await RisingEdge(dut.i_clk)
    await ReadOnly()

    assert int(dut.o_mem_empty.value) == 0, "memory shouldn't be empty"

    # Write another value to memory, counter = 2
    await FallingEdge(dut.i_clk)
    dut.i_data.value = 321654987
    dut.i_wr_en.value = 1
    dut.i_rd_en.value = 0

    await RisingEdge(dut.i_clk)
    await ReadOnly()

    
    # Reading one value from memory, counter = 1
    await FallingEdge(dut.i_clk)
    dut.i_data.value = 0
    dut.i_wr_en.value = 0
    dut.i_rd_en.value = 1

    await RisingEdge(dut.i_clk)
    await ReadOnly()

    assert int(dut.o_mem_empty.value) == 0, "memory shouldn't be empty"
    assert int(dut.o_data.value) == 1234567890123456, "invalid data pop"

    # Write + read from memory, counter = 1
    await FallingEdge(dut.i_clk)
    Hello = int.from_bytes(b"Hello", byteorder="big")
    dut.i_data.value = Hello
    dut.i_wr_en.value = 1
    dut.i_rd_en.value = 1

    await RisingEdge(dut.i_clk)
    await ReadOnly()

    assert int(dut.o_data.value) == 321654987, "invalid data pop"

    # Writes values till FIFO is full
    for value in range(2, 17): # Writes 2 through 16
        await FallingEdge(dut.i_clk)
        dut.i_data.value = value
        dut.i_wr_en.value = 1
        dut.i_rd_en.value = 0

        await RisingEdge(dut.i_clk)
        await ReadOnly()

        assert int(dut.o_mem_full.value) == (value == 16), f"Incorrect full flag after writing {value}"

    assert int(dut.o_mem_empty.value) == 0, "full FIFO shouldn't be empty"


    # Write one more to FIFO
    await FallingEdge(dut.i_clk)
    dut.i_data.value = int.from_bytes(b"Extra", byteorder="big")
    dut.i_wr_en.value = 1
    dut.i_rd_en.value = 0

    await RisingEdge(dut.i_clk)
    await ReadOnly()

    assert int(dut.o_mem_full.value) == 1, "FIFO should be full"

    # Read data
    await FallingEdge(dut.i_clk)
    dut.i_data.value = 0
    dut.i_wr_en.value = 0
    dut.i_rd_en.value = 1

    await RisingEdge(dut.i_clk)
    await ReadOnly()

    assert int(dut.o_data.value) == Hello, "FIFO should output Hello"
    assert int(dut.o_mem_full.value) == 0, "FIFO shouldn't be full"

    # Read loop for 2-16
    for read in range(2, 17):
        await FallingEdge(dut.i_clk)
        dut.i_data.value = 0
        dut.i_wr_en.value = 0
        dut.i_rd_en.value = 1

        await RisingEdge(dut.i_clk)
        await ReadOnly()

        assert int(dut.o_data.value) == read, f"FIFO should output {read}"
        assert int(dut.o_mem_empty.value) == (read == 16), f"Incorrect empty flag after reaching {read}"

    # Read extra 
    await FallingEdge(dut.i_clk)
    dut.i_data.value = 0
    dut.i_wr_en.value = 0
    dut.i_rd_en.value = 1

    await RisingEdge(dut.i_clk)
    await ReadOnly()

    assert int(dut.o_mem_empty.value) == 1, "Should be empty"
    assert int(dut.o_mem_full.value) == 0, "Shouldn't be full"

    # Write data
    await FallingEdge(dut.i_clk)
    dut.i_data.value = 1
    dut.i_wr_en.value = 1
    dut.i_rd_en.value = 0

    await RisingEdge(dut.i_clk)
    await ReadOnly()

    assert int(dut.o_mem_empty.value) == 0, "Shouldn't be empty"
    assert int(dut.o_mem_full.value) == 0, "Shouldn't be full"

    # Reads data
    await FallingEdge(dut.i_clk)
    dut.i_data.value = 0
    dut.i_wr_en.value = 0
    dut.i_rd_en.value = 1
    
    await RisingEdge(dut.i_clk)
    await ReadOnly()
    
    assert int(dut.o_data.value) == 1, "Should read 1"
    assert int(dut.o_mem_empty.value) == 1, "Should be empty"
    assert int(dut.o_mem_full.value) == 0, "Shouldn't be full"

    # Write two times
    for value in (1,3):
        await FallingEdge(dut.i_clk)
        dut.i_data.value = value
        dut.i_wr_en.value = 1
        dut.i_rd_en.value = 0

        await RisingEdge(dut.i_clk)
        await ReadOnly()

    # Reset
    await FallingEdge(dut.i_clk)
    dut.i_rst_n.value = 0
    dut.i_data.value = 0
    dut.i_wr_en.value = 0
    dut.i_rd_en.value = 0

    await RisingEdge(dut.i_clk)
    await ReadOnly()

    assert int(dut.o_mem_empty.value) == 1, "FIFO should be empty"
    assert int(dut.o_mem_full.value) == 0, "FIFO shouldn't be full"

    # Write then Read again
    await FallingEdge(dut.i_clk)
    dut.i_rst_n.value = 1
    dut.i_data.value = 99
    dut.i_wr_en.value = 1
    dut.i_rd_en.value = 0

    await RisingEdge(dut.i_clk)
    await ReadOnly()

    assert int(dut.o_mem_empty.value) == 0, "FIFO shouldn't be empty"

    await FallingEdge(dut.i_clk)
    dut.i_data.value = 0
    dut.i_wr_en.value = 0
    dut.i_rd_en.value = 1

    await RisingEdge(dut.i_clk)
    await ReadOnly()

    assert int(dut.o_data.value) == 99, "Should read 99"
    assert int(dut.o_mem_empty.value) == 1, "FIFO should be empty"

    # Check holding queued data while reads are disabled
    for value in range(1,3):
        await FallingEdge(dut.i_clk)
        dut.i_data.value = value
        dut.i_wr_en.value = 1
        dut.i_rd_en.value = 0

        await RisingEdge(dut.i_clk)
        await ReadOnly()

        assert int(dut.o_mem_empty.value) == 0, "FIFO shouldn't be empty"

    for value in range(1,6): # Hold value for 5 cycles
        await FallingEdge(dut.i_clk)
        dut.i_data.value = 0
        dut.i_wr_en.value = 0
        dut.i_rd_en.value = 0

        await RisingEdge(dut.i_clk)
        await ReadOnly()

        assert int(dut.o_mem_empty.value) == 0, "FIFO shouldn't be empty"
        assert int(dut.o_mem_full.value) == 0, "FIFO shouldn't be full"

    for value in range(1,3): # Read both values
        await FallingEdge(dut.i_clk)
        dut.i_data.value = 0
        dut.i_wr_en.value = 0
        dut.i_rd_en.value = 1

        await RisingEdge(dut.i_clk)
        await ReadOnly()

        assert int(dut.o_data.value) == value, f"Should output {value}"
        assert int(dut.o_mem_empty.value) == (value == 2), f"Incorrect empty flag after reading {value}"
        assert int(dut.o_mem_full.value) == 0, "FIFO shouldn't be full"
