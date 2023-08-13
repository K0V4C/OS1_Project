//
// Created by lazar on 5/16/23.
//
#ifndef _syscall_cpp
#define _syscall_cpp

#include "../h/syscall_c.h"
#include "../h/syscall_cpp.hpp"


void* operator new (size_t obj) {
    return mem_alloc(obj);
}
void operator delete (void* ptr) {
    mem_free(ptr);
}

Thread::Thread(void (*body)(void *), void *arg) {

}

Thread::~Thread() {

}

int Thread::start() {
    return 0;
}

void Thread::join() {

}

void Thread::dispatch() {

}

int Thread::sleep(time_t) {
    return 0;
}

Thread::Thread() {

}

#endif


