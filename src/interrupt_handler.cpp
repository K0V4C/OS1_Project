//
// Created by lazar on 5/15/23.
//

#include "../h/interrupt_handler.hpp"

extern "C" void handle_supervisor_interrupt(){

    uint64 volatile scause;
    __asm__ volatile (
            "csrr %[scause], scause"
            : [scause] "=r" (scause)
    );

    uint64 volatile sepc;
    __asm__ volatile(
            "csrr %[sepc], sepc"
            : [sepc] "=r" (sepc)
    );
    sepc += 4;
    __asm__ volatile(
            "csrw sepc, %[val]"
            :
            : [val] "r" (sepc)
    );
};

