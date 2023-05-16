
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


    // These are not inline so they can nullfiy register a0
    void ms_sstatus(uint64 mask);
    // mask clear?
    uint64 read_sstatus();
    void write_sstatus(uint64 val);

    uint64 read_scause();
    void write_scause(uint64 val);

    uint64 read_sepc();
    void write_sepc(uint64 val);

    uint64 read_stvec();
    void write_stvec(uint64 val);

    uint64 read_stval();
    void write_stval(uint64 val);

}


#endif // UTILITY_H
