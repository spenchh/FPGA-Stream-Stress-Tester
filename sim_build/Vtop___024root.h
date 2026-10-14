// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(i_clk,0,0);
    VL_IN8(i_rst_n,0,0);
    VL_IN8(i_wr_en,0,0);
    VL_IN8(i_rd_en,0,0);
    VL_OUT8(o_mem_full,0,0);
    VL_OUT8(o_mem_empty,0,0);
    CData/*0:0*/ sync_fifo__DOT__i_clk;
    CData/*0:0*/ sync_fifo__DOT__i_rst_n;
    CData/*0:0*/ sync_fifo__DOT__i_wr_en;
    CData/*0:0*/ sync_fifo__DOT__i_rd_en;
    CData/*0:0*/ sync_fifo__DOT__o_mem_full;
    CData/*0:0*/ sync_fifo__DOT__o_mem_empty;
    CData/*3:0*/ sync_fifo__DOT__wr_ptr;
    CData/*3:0*/ sync_fifo__DOT__rd_ptr;
    CData/*4:0*/ sync_fifo__DOT__counter;
    CData/*0:0*/ sync_fifo__DOT__push;
    CData/*0:0*/ sync_fifo__DOT__pop;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__i_clk__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VL_IN64(i_data,63,0);
    VL_OUT64(o_data,63,0);
    QData/*63:0*/ sync_fifo__DOT__i_data;
    QData/*63:0*/ sync_fifo__DOT__o_data;
    VlUnpacked<QData/*63:0*/, 16> sync_fifo__DOT__mem;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // PARAMETERS
    static constexpr IData/*31:0*/ sync_fifo__DOT__WIDTH = 0x00000040U;
    static constexpr IData/*31:0*/ sync_fifo__DOT__DEPTH = 0x00000010U;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
