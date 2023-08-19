//
// Created by lazar on 5/16/23.
//

#ifndef SYSCALL_CPP_H
#define SYSCALL_CPP_H

#include "../lib/hw.h"

void* operator new (size_t);
void operator delete  (void*);

class TCB;
typedef TCB* thread_t;
class Thread {
public:
    Thread (void (*body)(void*), void* arg);
    virtual ~Thread ();
    int start ();
    void join();
    static void dispatch ();
    static int sleep (time_t);
protected:
    Thread ();
    virtual void run () {}
private:
    static void wrapper(void* arg);
    thread_t myHandle;
    void (*body)(void*); void* arg;
};

class KernelSemaphore;
typedef KernelSemaphore* sem_t;
class Semaphore {
public:
    Semaphore (unsigned init = 1);
    virtual ~Semaphore ();
    int wait ();
    int signal ();
private:
    sem_t myHandle;
};

class PeriodicThread : public Thread {
public:
    void terminate ();
protected:
    PeriodicThread (time_t period);
    virtual void periodicActivation () {}
    void run() override;
private:
    time_t period;
    bool die;
};

class Console {
public:
    static char getc ();
    static void putc (char);
};

#endif //SYSCALL_CPP_H
