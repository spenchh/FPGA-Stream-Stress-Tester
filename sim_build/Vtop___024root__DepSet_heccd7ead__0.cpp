// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.sync_fifo__DOT__i_clk = vlSelfRef.i_clk;
    vlSelfRef.sync_fifo__DOT__i_rst_n = vlSelfRef.i_rst_n;
    vlSelfRef.sync_fifo__DOT__i_data = vlSelfRef.i_data;
    vlSelfRef.sync_fifo__DOT__i_wr_en = vlSelfRef.i_wr_en;
    vlSelfRef.sync_fifo__DOT__i_rd_en = vlSelfRef.i_rd_en;
    vlSelfRef.o_data = vlSelfRef.sync_fifo__DOT__o_data;
    vlSelfRef.o_mem_full = (0x10U == (IData)(vlSelfRef.sync_fifo__DOT__counter));
    vlSelfRef.o_mem_empty = (0U == (IData)(vlSelfRef.sync_fifo__DOT__counter));
    vlSelfRef.sync_fifo__DOT__o_mem_full = vlSelfRef.o_mem_full;
    vlSelfRef.sync_fifo__DOT__push = ((~ (IData)(vlSelfRef.o_mem_full)) 
                                      & (IData)(vlSelfRef.i_wr_en));
    vlSelfRef.sync_fifo__DOT__o_mem_empty = vlSelfRef.o_mem_empty;
    vlSelfRef.sync_fifo__DOT__pop = ((~ (IData)(vlSelfRef.o_mem_empty)) 
                                     & (IData)(vlSelfRef.i_rd_en));
}

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtop___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vtop___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    QData/*63:0*/ __VdlyVal__sync_fifo__DOT__mem__v0;
    __VdlyVal__sync_fifo__DOT__mem__v0 = 0;
    CData/*3:0*/ __VdlyDim0__sync_fifo__DOT__mem__v0;
    __VdlyDim0__sync_fifo__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__sync_fifo__DOT__mem__v0;
    __VdlySet__sync_fifo__DOT__mem__v0 = 0;
    // Body
    __VdlySet__sync_fifo__DOT__mem__v0 = 0U;
    if (vlSelfRef.i_rst_n) {
        if (vlSelfRef.sync_fifo__DOT__push) {
            __VdlyVal__sync_fifo__DOT__mem__v0 = vlSelfRef.i_data;
            __VdlyDim0__sync_fifo__DOT__mem__v0 = vlSelfRef.sync_fifo__DOT__wr_ptr;
            __VdlySet__sync_fifo__DOT__mem__v0 = 1U;
            vlSelfRef.sync_fifo__DOT__wr_ptr = (0xfU 
                                                & ((IData)(1U) 
                                                   + (IData)(vlSelfRef.sync_fifo__DOT__wr_ptr)));
        }
        if (((IData)(vlSelfRef.sync_fifo__DOT__push) 
             ^ (IData)(vlSelfRef.sync_fifo__DOT__pop))) {
            vlSelfRef.sync_fifo__DOT__counter = (0x1fU 
                                                 & ((IData)(vlSelfRef.sync_fifo__DOT__push)
                                                     ? 
                                                    ((IData)(1U) 
                                                     + (IData)(vlSelfRef.sync_fifo__DOT__counter))
                                                     : 
                                                    ((IData)(vlSelfRef.sync_fifo__DOT__counter) 
                                                     - (IData)(1U))));
        }
        if (vlSelfRef.sync_fifo__DOT__pop) {
            vlSelfRef.sync_fifo__DOT__o_data = vlSelfRef.sync_fifo__DOT__mem
                [vlSelfRef.sync_fifo__DOT__rd_ptr];
            vlSelfRef.sync_fifo__DOT__rd_ptr = (0xfU 
                                                & ((IData)(1U) 
                                                   + (IData)(vlSelfRef.sync_fifo__DOT__rd_ptr)));
        }
    } else {
        vlSelfRef.sync_fifo__DOT__wr_ptr = 0U;
        vlSelfRef.sync_fifo__DOT__counter = 0U;
        vlSelfRef.sync_fifo__DOT__rd_ptr = 0U;
    }
    if (__VdlySet__sync_fifo__DOT__mem__v0) {
        vlSelfRef.sync_fifo__DOT__mem[__VdlyDim0__sync_fifo__DOT__mem__v0] 
            = __VdlyVal__sync_fifo__DOT__mem__v0;
    }
    vlSelfRef.o_mem_full = (0x10U == (IData)(vlSelfRef.sync_fifo__DOT__counter));
    vlSelfRef.o_mem_empty = (0U == (IData)(vlSelfRef.sync_fifo__DOT__counter));
    vlSelfRef.o_data = vlSelfRef.sync_fifo__DOT__o_data;
    vlSelfRef.sync_fifo__DOT__o_mem_full = vlSelfRef.o_mem_full;
    vlSelfRef.sync_fifo__DOT__push = ((~ (IData)(vlSelfRef.o_mem_full)) 
                                      & (IData)(vlSelfRef.i_wr_en));
    vlSelfRef.sync_fifo__DOT__o_mem_empty = vlSelfRef.o_mem_empty;
    vlSelfRef.sync_fifo__DOT__pop = ((~ (IData)(vlSelfRef.o_mem_empty)) 
                                     & (IData)(vlSelfRef.i_rd_en));
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtop___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vtop___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("/mnt/c/Users/HP/Documents/FPGA-Stream-Stress-Tester/sync_fifo.sv", 1, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vtop___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/mnt/c/Users/HP/Documents/FPGA-Stream-Stress-Tester/sync_fifo.sv", 1, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/mnt/c/Users/HP/Documents/FPGA-Stream-Stress-Tester/sync_fifo.sv", 1, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vtop___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vtop___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.i_clk & 0xfeU)))) {
        Verilated::overWidthError("i_clk");}
    if (VL_UNLIKELY(((vlSelfRef.i_rst_n & 0xfeU)))) {
        Verilated::overWidthError("i_rst_n");}
    if (VL_UNLIKELY(((vlSelfRef.i_wr_en & 0xfeU)))) {
        Verilated::overWidthError("i_wr_en");}
    if (VL_UNLIKELY(((vlSelfRef.i_rd_en & 0xfeU)))) {
        Verilated::overWidthError("i_rd_en");}
}
#endif  // VL_DEBUG
