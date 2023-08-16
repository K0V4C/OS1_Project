#include "../h/syscall_c.h"
#include "../h/bit_masks.hpp"
#include "../lib/console.h"

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
    void* arg) {

    void* stack = mem_alloc(DEFAULT_STACK_SIZE);
    asm volatile ("mv a0, %[stack]": : [stack] "r"  (stack));
    asm volatile ("mv a1, %[handle]": : [handle] "r"  (handle));
    asm volatile ("mv a2, %[function]": : [function] "r"  (start_routine));
    asm volatile ("mv a3, %[args]": : [args] "r"  (arg));
    set_and_ecall(OP_CODES::c_create_thread);
    int volatile ret;
    SET_RET(ret);
    return (int)ret;
}

int thread_exit () {
    set_and_ecall(OP_CODES::c_thread_exit);
    int volatile ret;
    SET_RET(ret);
    return (int)ret;
}

void thread_dispatch() {
    set_and_ecall(OP_CODES::c_thread_dispatch);
}

void thread_join ( thread_t handle ) {
    asm volatile ("mv a0, %[handle]": : [handle] "r"  (handle));
    set_and_ecall(OP_CODES::c_thread_join);
}

int sem_open(
        sem_t* handle,
        unsigned init) {
    asm volatile ("mv a0, %[handle]": : [handle] "r"  (handle));
    asm volatile ("mv a1, %[init]": : [init] "r"  (init));
    set_and_ecall(OP_CODES::c_sem_open);
    int volatile ret;
    SET_RET(ret);
    return (int)ret;
}

int sem_close(sem_t handle) {
    asm volatile ("mv a0, %[handle]": : [handle] "r"  (handle));
    set_and_ecall(OP_CODES::c_sem_close);
    int volatile ret;
    SET_RET(ret);
    return (int)ret;
}

int sem_wait(sem_t id) {
    asm volatile ("mv a0, %[id]": : [id] "r"  (id));
    set_and_ecall(OP_CODES::c_sem_wait);
    int volatile ret;
    SET_RET(ret);
    return (int)ret;
}

int sem_signal(sem_t id) {
    asm volatile ("mv a0, %[id]": : [id] "r"  (id));
    set_and_ecall(OP_CODES::c_sem_signal);
    int volatile ret;
    SET_RET(ret);
    return (int)ret;
}

int time_sleep(time_t time) {
    asm volatile ("mv a0, %[time]": : [time] "r"  (time));
    set_and_ecall(OP_CODES::c_time_sleep);
    int volatile ret;
    SET_RET(ret);
    return (int)ret;
}

char getc() {
    set_and_ecall(OP_CODES::c_getc);
    int volatile ret;
    SET_RET(ret);
    return (char)ret;
}

void putc(char a) {
    asm volatile ("mv a0, %[a]": : [a] "r"  (a));
    set_and_ecall(OP_CODES::c_putc);
}

void change_privilege() {
    set_and_ecall(OP_CODES::mode_switch);
}
