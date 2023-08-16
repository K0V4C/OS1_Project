//
// Created by lazar on 6/24/23.
//

#ifndef KERNEL_SEMAPHORE_HPP
#define KERNEL_SEMAPHORE_HPP

#include "../lib/hw.h"
class TCB;

// Page 273 from Operating Systems 1 by Dragan Milicev Book

class KernelSemaphore {
private:

    struct blocked_node{
        TCB* value;
        blocked_node* next;

        void* operator new(size_t size);
        void operator delete (void* ptr);
    };

    blocked_node* blocked_queue_start = nullptr;
    blocked_node* blocked_queue_tail = nullptr;

    int sem_value = 0;

    void block();
    void unblock();

    KernelSemaphore(int val = 1): sem_value(val){}

public:

    int wait();

    void signal();

    int get_value () const {return sem_value; }

    static void release(KernelSemaphore*);

    static KernelSemaphore* create_semaphore(int val);

    void* operator new(size_t size);
    void operator delete (void* ptr);
};


#endif //KERNEL_SEMAPHORE_HPP
