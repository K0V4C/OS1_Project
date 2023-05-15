
//
// Created by lazar on 5/12/23.
//

#ifndef UTILITY_H
#define UTILITY_H

#include "../lib/console.h"
#include "../lib/hw.h"

namespace kvc {

    void __assert(const void *a, const void *b);

    void __assert(const uint64 a, const uint64 b);

    void __assert(const int a, const int b);

    void print_int(int val);

    void print_uint64(uint64 val);

    void print_void(void *ptr);

    void print_str(const char*);

    void new_line();

    enum BitMasks{
        SSTATUS_SPIE= 0x020,
        SSTATUS_SPP = 0x100,
        SSTATUS_SIE = 0x001,

    };

    inline void write_sstatus(uint64 val){
        __asm__ volatile(
                "csrw sepc, %[val]"
                :
                : [val] "r" (val)
        );

    }

    inline uint64 read_scause(){
        uint64 volatile val;
        __asm__ (
                "csrr %[val], scause"
                : [val] "=r" (val)
        );
        return val;
    }
    inline void write_scause(uint64 val){
        __asm__ volatile(
                "csrw sepc, %[val]"
                :
                : [val] "r" (val)
        );

    }

    inline uint64 read_sepc(){
        uint64 volatile val;
        __asm__ (
                "csrr %[val], sepc"
                : [val] "=r" (val)
        );
        return val;
    }
    inline void write_sepc(uint64 val){
        __asm__ volatile(
                "csrw sepc, %[val]"
                :
                : [val] "r" (val)
        );

    }

    inline uint64 read_stvec(){
        uint64 volatile val;
        __asm__ (
                "csrr %[val], stvec"
                : [val] "=r" (val)
        );
        return val;
    }
    inline void write_stvec(uint64 val){
        __asm__ volatile(
                "csrw sepc, %[val]"
                :
                : [val] "r" (val)
        );

    }

    inline uint64 read_stval(){
        uint64 volatile val;
        __asm__ (
                "csrr %[val], stval"
                : [val] "=r" (val)
        );
        return val;
    }
    inline void write_stval(uint64 val){
        __asm__ volatile(
                "csrw sepc, %[val]"
                :
                : [val] "r" (val)
        );

    }
}


#endif // UTILITY_H
