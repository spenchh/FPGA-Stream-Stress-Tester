// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtop__pch.h"
#include "Vtop.h"
#include "Vtop___024root.h"

// FUNCTIONS
Vtop__Syms::~Vtop__Syms()
{

    // Tear down scope hierarchy
    __Vhier.remove(0, &__Vscope_sync_fifo);

}

Vtop__Syms::Vtop__Syms(VerilatedContext* contextp, const char* namep, Vtop* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(45);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscope_TOP.configure(this, name(), "TOP", "TOP", "<null>", 0, VerilatedScope::SCOPE_OTHER);
    __Vscope_sync_fifo.configure(this, name(), "sync_fifo", "sync_fifo", "sync_fifo", -9, VerilatedScope::SCOPE_MODULE);

    // Set up scope hierarchy
    __Vhier.add(0, &__Vscope_sync_fifo);

    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
        __Vscope_TOP.varInsert(__Vfinal,"i_clk", &(TOP.i_clk), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_data", &(TOP.i_data), false, VLVT_UINT64,VLVD_IN|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_rd_en", &(TOP.i_rd_en), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_rst_n", &(TOP.i_rst_n), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_wr_en", &(TOP.i_wr_en), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_data", &(TOP.o_data), false, VLVT_UINT64,VLVD_OUT|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_mem_empty", &(TOP.o_mem_empty), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_mem_full", &(TOP.o_mem_full), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"DEPTH", const_cast<void*>(static_cast<const void*>(&(TOP.sync_fifo__DOT__DEPTH))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.sync_fifo__DOT__WIDTH))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"counter", &(TOP.sync_fifo__DOT__counter), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,4,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"i_clk", &(TOP.sync_fifo__DOT__i_clk), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"i_data", &(TOP.sync_fifo__DOT__i_data), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"i_rd_en", &(TOP.sync_fifo__DOT__i_rd_en), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"i_rst_n", &(TOP.sync_fifo__DOT__i_rst_n), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"i_wr_en", &(TOP.sync_fifo__DOT__i_wr_en), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"mem", &(TOP.sync_fifo__DOT__mem), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,1,1 ,15,0 ,63,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"o_data", &(TOP.sync_fifo__DOT__o_data), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"o_mem_empty", &(TOP.sync_fifo__DOT__o_mem_empty), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"o_mem_full", &(TOP.sync_fifo__DOT__o_mem_full), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"pop", &(TOP.sync_fifo__DOT__pop), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"push", &(TOP.sync_fifo__DOT__push), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"rd_ptr", &(TOP.sync_fifo__DOT__rd_ptr), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,3,0);
        __Vscope_sync_fifo.varInsert(__Vfinal,"wr_ptr", &(TOP.sync_fifo__DOT__wr_ptr), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,3,0);
    }
}
