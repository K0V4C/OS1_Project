//
// Created by lazar on 5/16/23.
//

#ifndef OUTPUT_H
#define OUTPUT_H

#include "../lib/hw.h"
#include "../lib/console.h"

namespace  kvc {
    void __assert(const void *a, const void *b);

    void __assert(const uint64 a, const uint64 b);

    void __assert(const int a, const int b);

    void print_int(int val);

    void print_uint64(uint64 val);

    void print_void(void *ptr);

    void print_str(const char*);

    void new_line();
}
#endif // OUTPUT_H
