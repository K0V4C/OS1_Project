//
// Created by lazar on 5/15/23.
//


#include "../h/syscall_c.hpp"

enum OP_CODES{
    MEM_ALLOC       = 0x01,
    MEM_FREE        = 0x02,
    THREAD_CREATE   = 0x11,
    THREAD_EXIT     = 0x12,
    THREAD_DISPATCH = 0x13,
    THREAD_JOIN     = 0x14,
    SEM_OPEN        = 0x21,
    SEM_CLOSE       = 0x22,
    SEM_WAIT        = 0x23,
    SEM_SIGNAL      = 0x24,
    TIME_SLEEP      = 0x31,
    GETC            = 0x41,
    PUTC            = 0x42
};

inline void set_and_call(uint64 code){
    __asm__  volatile("mv a3, a4");
    __asm__  volatile("mv a2, a3");
    __asm__  volatile("mv a1, a2");
    __asm__  volatile("mv a0, a1");
    __asm__ volatile(
            "li a0, %[code]"
            :
            : [code] "i"  (code)
    );
    __asm__ volatile ("ecall");
}

void* mem_alloc (size_t size) {

    if(size <= 0)
        return nullptr;

    uint64 blocks = size / MEM_BLOCK_SIZE + (size % MEM_BLOCK_SIZE) ? 1 : 0;

    uint64 volatile ptr;

    set_and_call(MEM_ALLOC);

    __asm__ volatile(
            "mv %[mem],  a0"
            : [mem] "=r" (ptr)
            );

    return (void*)ptr;
}

int mem_free (void* adr) {

    if(adr == nullptr)
        return -1;

    uint64 volatile ret;
    set_and_call(MEM_FREE);

    __asm__ volatile(
            "mv %[mem],  a0"
            : [mem] "=r" (ret)
    );

    return ret;
}

int thread_create (
    thread_t * handle, // Sakriven pokazivac
    void(*start_routine)(void*),
    void* arg
);

int thread_exit ();

void thread_dispatch();

void thread_join ( thread_t handle );

int sem_open(
        sem_t* handle,
        unsigned int
        );

int sem_close(sem_t handle);

int sem_wait(sem_t id);

int sem_signal(sem_t id);

int time_sleep(time_t);

char getc();

void putc(char);