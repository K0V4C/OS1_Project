//
// Created by lazar on 5/16/23.
//
#ifndef _syscall_cpp
#define _syscall_cpp
#include "../h/syscall_c.hpp"

void* operator new (size_t obj) {
    return mem_alloc(obj);
}
void operator delete (void* ptr) {
    mem_free(ptr);
}

#endif