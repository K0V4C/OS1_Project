//
// Created by lazar on 6/24/23.
//

#include "../h/kernel_sem.hpp"
#include "../h/output.hpp"

// Semaphore node

void *KernelSemaphore::blocked_node::operator new(size_t size) {
    return MemoryAllocator::allocate_blocks(
            MemoryAllocator::size_in_blocks(size)
    );
}

void KernelSemaphore::blocked_node::operator delete(void* ptr) {
    MemoryAllocator::free_blocks(ptr);
}

// Semaphore
void *KernelSemaphore::operator new(size_t size) {
    return MemoryAllocator::allocate_blocks(
            MemoryAllocator::size_in_blocks(size)
    );
}

void KernelSemaphore::operator delete(void* ptr) {
    MemoryAllocator::free_blocks(ptr);
}

KernelSemaphore* KernelSemaphore::create_semaphore(int val) {
    return new KernelSemaphore(val);
}

void KernelSemaphore::block() {

    blocked_node* new_node = new blocked_node();

    new_node->next = nullptr;
    new_node->value = TCB::running;

    if(blocked_queue_start == nullptr) {
        blocked_queue_start = new_node;
        blocked_queue_tail = new_node;
    } else {
        blocked_queue_tail->next = new_node;
        blocked_queue_tail = new_node;
    }

    //  has to be yield
    TCB::running->set_state(TCB::State::BLOCKED);
    TCB::yield();
}

void KernelSemaphore::unblock() {

    if(blocked_queue_start == nullptr)
        kvc::print_str("\n+++++++++++ PANIC! ++++++++++\n");

    blocked_node* scheduled_node = blocked_queue_start;
    blocked_queue_start = blocked_queue_start->next;

    if(blocked_queue_start == nullptr)
        blocked_queue_tail = nullptr;

    scheduled_node->value->set_state(TCB::State::NOT_FINISHED);
    Scheduler::put(scheduled_node->value);
    delete scheduled_node;

}

void KernelSemaphore::wait() {
//    kvc::print_str("ULAZAK U WAIT: ");kvc::print_int(sem_value);kvc::new_line();
    if(--sem_value < 0 ) block();
//    kvc::print_str("IZLAZAK IZ WAIT: ");kvc::print_int(sem_value);kvc::new_line();
    //    kvc::print_int(sem_value);kvc::new_line();
}

void KernelSemaphore::signal() {
//    kvc::print_str("ULAZAK U SIGNAL: ");kvc::print_int(sem_value);kvc::new_line();
    if(++sem_value <= 0) unblock();
//    kvc::print_str("IZLAZAL IZ SIGNAL: ");kvc::print_int(sem_value);kvc::new_line();
//    kvc::print_int(sem_value);kvc::new_line();
}