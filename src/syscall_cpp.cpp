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

Thread::Thread(void (*body)(void *), void *arg) : body(body), arg(arg){}

Thread::~Thread() {
    // Sta ovde treba?
}

int Thread::start() {
    return thread_create(&myHandle, body, arg);
}

void Thread::join() {
    // TODO
}

void Thread::dispatch() {
    thread_dispatch();
}

int Thread::sleep(time_t) {
    // todo
    return 0;
}

Thread::Thread():body(nullptr), arg(nullptr){}

Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle, init);
}

Semaphore::~Semaphore() {
    sem_close(myHandle);
}

int Semaphore::wait() {
    return sem_wait(myHandle);
}

int Semaphore::signal() {
    return sem_signal(myHandle);
}

#endif

