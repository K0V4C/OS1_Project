
//
// Created by lazar on 5/12/23.
//

#ifndef UTILITY_H
#define UTILITY_H

#include "../lib/console.h"
#include "../lib/hw.h"

namespace kvc {

    inline void ms_sstatus(uint64 mask){
        asm volatile(
                "csrs sstatus, %[mask]"
                :
                : [mask] "r" (mask)
        );
    }
    // mask clear?
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

}


#endif // UTILITY_H
