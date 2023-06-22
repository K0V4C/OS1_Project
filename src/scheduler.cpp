//
// Created by lazar on 6/22/23.
//

#include "../h/scheduler.hpp"
#include "../h/memory_allocator.hpp"

Scheduler &Scheduler::get_instance() {
    static Scheduler instance;
    return instance;
}

int Scheduler::put(tcb* tcb) {
    Scheduler instance = Scheduler::get_instance();

    scheduled_node* new_node = (scheduled_node*) MemoryAllocator::allocate_blocks(
            MemoryAllocator::size_in_blocks(sizeof(scheduled_node))
            );

    if(!new_node)
        return -1; // Exception // Should this panic?

    new_node->value = tcb;

    if(instance.head == nullptr) {
        instance.head = new_node;
        instance.tail = new_node;
    } else {
        instance.tail->next = new_node;
        instance.tail = new_node;
    }

    return 0;
}

tcb *Scheduler::get() {
    Scheduler instance = Scheduler::get_instance();

    if(instance.head == nullptr)
        return nullptr;

    scheduled_node* return_node = instance.head;
    instance.head = instance.head->next;

    if(instance.head == nullptr)
        instance.tail = nullptr;

    tcb* ret = return_node->value;
    MemoryAllocator::free_blocks((void*)return_node);

    return ret;
}


