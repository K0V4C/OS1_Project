#ifndef UTILITY_H
#define UTILITY_H

#include "../lib/console.h"
#include "../lib/hw.h"

// Inspired by videos

namespace riscv {

    // ========================================= Main setup functions ==================================================

    void user_main_wrapper(void*);
    void setup_interrupt_routine();
    void set_main_and_idle();
    void idle_thread(void*);
    void enable_interrupts();
    void run_user_main();

    // =================================================================================================================

    // ========================================= Register functions ====================================================

    inline void mask_set_sstatus(uint64 mask){
        asm volatile(
                "csrs sstatus, %[mask]"
                :
                : [mask] "r" (mask)
        );
    }

    inline void mask_clear_sstatus(uint64 mask){
        asm volatile(
                "csrc sstatus, %[mask]"
                :
                : [mask] "r" (mask)
                );
    }

    inline uint64 read_sstatus(){
        uint64 volatile val;
        asm (
                "csrr %[val], sstatus"
                : [val] "=r" (val)
        );
        return val;
    }
    inline void write_sstatus(uint64 val){
        asm volatile(
                "csrw sstatus, %[val]"
                :
                : [val] "r" (val)
        );

    }

    inline void mask_set_sip(uint64 mask){
        asm volatile(
                "csrs sip, %[mask]"
                :
                : [mask] "r" (mask)
        );
    }

    inline void mask_clear_sip(uint64 mask){
        asm volatile(
                "csrc sip, %[mask]"
                :
                : [mask] "r" (mask)
        );
    }

    inline uint64 read_sip(){
        uint64 volatile val;
        asm (
                "csrr %[val], sip"
                : [val] "=r" (val)
        );
        return val;
    }
    inline void write_sip(uint64 val){
        asm volatile(
                "csrw sip, %[val]"
                :
                : [val] "r" (val)
        );

    }

    inline uint64 read_scause(){
        uint64 volatile val;
        asm (
                "csrr %[val], scause"
                : [val] "=r" (val)
        );
        return val;
    }
    inline void write_scause(uint64 val){
        asm volatile(
                "csrw scause, %[val]"
                :
                : [val] "r" (val)
        );

    }

    inline uint64 read_sepc(){
        uint64 volatile val;
        asm (
                "csrr %[val], sepc"
                : [val] "=r" (val)
        );
        return val;
    }
    inline void write_sepc(uint64 val){
        asm volatile(
                "csrw sepc, %[val]"
                :
                : [val] "r" (val)
        );

    }

    inline uint64 read_stvec(){
        uint64 volatile val;
        asm (
                "csrr %[val], stvec"
                : [val] "=r" (val)
        );
        return val;
    }
    inline void write_stvec(uint64 val){
        asm volatile(
                "csrw stvec, %[val]"
                :
                : [val] "r" (val)
        );

    }

    inline uint64 read_stval(){
        uint64 volatile val;
        asm (
                "csrr %[val], stval"
                : [val] "=r" (val)
        );
        return val;
    }
    inline void write_stval(uint64 val){
        asm volatile(
                "csrw stval, %[val]"
                :
                : [val] "r" (val)
        );

    }

    // =================================================================================================================

}


#endif // UTILITY_H
