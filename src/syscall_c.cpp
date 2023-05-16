//
// Created by lazar on 5/15/23.
//


#include "../h/syscall_c.hpp"
#include "../h/bit_masks.hpp"

inline void set_and_ecall(uint64 code) {
    __asm__  volatile("mv a4, a3");
    __asm__  volatile("mv a3, a2");
    __asm__  volatile("mv a2, a1");
    __asm__  volatile("mv a1, a0");
    __asm__ volatile ("mv a0, %[code]": : [code] "r"  (code));
    __asm__ volatile ("ecall");
}

void* mem_alloc (size_t size) {

    if(size <= 0)
        return nullptr;

    uint64 blocks = size / MEM_BLOCK_SIZE + ((size % MEM_BLOCK_SIZE) ? 1 : 0);

    uint64 volatile ptr;

    __asm__ volatile ("mv a0, %[blocks_size]": : [blocks_size] "r"  (blocks));
    
    set_and_ecall(OP_CODES::c_allocate_memory);

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
    set_and_ecall(OP_CODES::c_free_memory);

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