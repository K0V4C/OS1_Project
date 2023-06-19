#include "../h/syscall_c.hpp"
#include "../h/bit_masks.hpp"

inline void set_and_ecall(uint64 code) {
    asm volatile("mv a4, a3");
    asm volatile("mv a3, a2");
    asm volatile("mv a2, a1");
    asm volatile("mv a1, a0");
    asm volatile("mv a0, %[code]": : [code] "r"  (code));
    asm volatile("ecall");
}

#define SET_RET(ret) asm volatile("mv %[mem],  a0": [mem] "=r" (ret))

void* mem_alloc (size_t size) {
    asm volatile ("mv a0, %[size_in_bytes]": : [size_in_bytes] "r"  (size));
    set_and_ecall(OP_CODES::c_allocate_memory);
    uint64 volatile ptr;
    SET_RET(ptr);    // asm volatile("mv %[mem],  a0": [mem] "=r" (ptr));
    return (void*)ptr;
}

int mem_free (void* adr) {
    set_and_ecall(OP_CODES::c_free_memory);
    uint64 volatile ret ;
    SET_RET(ret); // asm volatile("mv %[mem],  a0": [mem] "=r" (ret));
    return (int)ret;
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
