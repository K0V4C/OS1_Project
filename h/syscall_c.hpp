//
// Created by lazar on 5/15/23.
//

#ifndef SYS_CALLS_H
#define SYS_CALLS_H

#include "../lib/hw.h"

extern void* mem_alloc(size_t);
extern int mem_free(void*);

extern void* mem_alloc(uint64 size_in_bytes);

extern int mem_free(void* adr);

class TCB;
typedef TCB* thread_t;

extern int thread_create (
        thread_t * handle, // Sakriven pokazivac
        void(*start_routine)(void*),
        void* arg
);

extern int thread_exit();

extern void thread_dispatch();

extern void thread_join ( thread_t handle );

class KernelSemaphore;
typedef KernelSemaphore* sem_t;

extern int sem_open(
        sem_t* handle,
        unsigned int
);

extern int sem_close(sem_t handle);

extern int sem_wait(sem_t id);

extern int sem_signal(sem_t id);

typedef unsigned long time_t;

extern int time_sleep(time_t);

const int EOF = 1;
extern char getc();

extern void putc(char);


#endif //SYS_CALLS_H
