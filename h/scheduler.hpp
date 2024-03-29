#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

class TCB;
#include "memory_allocator.hpp"

class Scheduler {
private:

    // REDACTED
    Scheduler(Scheduler&) = delete;
    Scheduler(Scheduler&&) = delete;

    // todo add move and copy operators here

    // DEFAULT
    Scheduler() {}

    class scheduled_node {
    public:
        TCB* value;
        scheduled_node* next;

        void* operator new(size_t size);
        void operator delete (void* ptr);
    };

    scheduled_node* head = nullptr;
    scheduled_node* tail = nullptr;

    static Scheduler& get_instance();

public:

    static TCB* get();

    static int put(TCB*);

};

#endif // SCHEDULER_HPP
