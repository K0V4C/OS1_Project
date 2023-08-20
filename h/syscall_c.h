#ifndef SYS_CALLS_H
#define SYS_CALLS_H

#include "../lib/hw.h"

void* mem_alloc(size_t);
int mem_free(void*);

void* mem_alloc(uint64 size_in_bytes);

int mem_free(void* adr);

class TCB;
typedef TCB* thread_t;

int thread_create (
        thread_t * handle, // Sakriven pokazivac
        void(*start_routine)(void*),
        void* arg
);

int thread_exit();

void thread_dispatch();

void thread_join ( thread_t handle );

class KernelSemaphore;
typedef KernelSemaphore* sem_t;

int sem_open(
        sem_t* handle,
        unsigned int
);

int sem_close(sem_t handle);

int sem_wait(sem_t id);

int sem_signal(sem_t id);

typedef unsigned long time_t;

int time_sleep(time_t);

const int EOF = 1;
char getc();

void putc(char);

void change_privilege();


#endif //SYS_CALLS_H
