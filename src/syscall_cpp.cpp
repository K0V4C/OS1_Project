#include "../h/syscall_c.h"
#include "../h/syscall_cpp.hpp"
#include "../lib/console.h"

void* operator new (size_t obj) {
    return mem_alloc(obj);
}
void operator delete (void* ptr) {
    mem_free(ptr);
}

Thread::Thread(void (*body)(void *), void *arg) : myHandle(nullptr), body(body), arg(arg){}

Thread::~Thread() {}

void Thread::wrapper(void *arg) {
    if(arg)((Thread*)arg)->run();
}

int Thread::start() {

    if(myHandle != nullptr)
        return -1;

    if(body == nullptr ){
        return thread_create(&myHandle, Thread::wrapper, this);
    } else {
        return thread_create(&myHandle, body, arg);
    }
}

void Thread::join() {
    thread_join(this->myHandle);
}

void Thread::dispatch() {
    thread_dispatch();
}

int Thread::sleep(time_t time) {
    return time_sleep(time);
}

Thread::Thread():myHandle(nullptr), body(nullptr), arg(nullptr){}

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

void PeriodicThread::terminate() {
    period = 0;
}

PeriodicThread::PeriodicThread(time_t period)
    : period(period) {}

void PeriodicThread::run() {
    while(period != 0) {
        periodicActivation();
        time_sleep(period);
    }
}

char Console::getc() {
    return ::getc();
}

void Console::putc(char a) {
    ::putc(a);
}
