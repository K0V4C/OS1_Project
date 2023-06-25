//
// Created by lazar on 6/22/23.
//

#include "../h/scheduler.hpp"
#include "../h/memory_allocator.hpp"
#include "../h/output.hpp"
#include "../h/tcb.hpp"

Scheduler &Scheduler::get_instance() {
    static Scheduler instance;
    return instance;
}

int Scheduler::put(TCB* tcb) {
    Scheduler& instance = Scheduler::get_instance();

//    scheduled_node* new_node = (scheduled_node*) MemoryAllocator::allocate_blocks(
//            MemoryAllocator::size_in_blocks(sizeof(scheduled_node))
//            );

    scheduled_node* new_node = new scheduled_node();

    if(!new_node)
        return -1; // Exception // Should this panic?

    new_node->value = tcb;
    new_node->next = nullptr;

    if(instance.head == nullptr) {
        instance.head = new_node;
        instance.tail = new_node;
    } else {
        instance.tail->next = new_node;
        instance.tail = new_node;
    }

    return 0;
}

TCB *Scheduler::get() {
    Scheduler& instance = Scheduler::get_instance();

    if(instance.head == nullptr)
        return nullptr;

    scheduled_node* return_node = instance.head;
    instance.head = instance.head->next;

    if(instance.head == nullptr)
        instance.tail = nullptr;

    TCB* ret = return_node->value;
    delete return_node;

    return ret;
}


void *Scheduler::scheduled_node::operator new(size_t size) {
    return MemoryAllocator::allocate_blocks(
            MemoryAllocator::size_in_blocks(size)
            );
}

void Scheduler::scheduled_node::operator delete(void* ptr) {
    MemoryAllocator::free_blocks(ptr);
}
