
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
}


#endif // UTILITY_H
