//
// Created by lazar on 6/24/23.
//

#include "../h/kernel_sem.hpp"
#include "../h/output.hpp"
#include "../h/scheduler.hpp"
#include "../h/tcb.hpp"
#include "../h/utility.hpp"
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

void KernelSemaphore::release(KernelSemaphore* sem) {
    // release all threads blocked on this semaphore
    // TODO: add -1 for all unblocked by this
    while(sem->blocked_queue_start != nullptr) {
        sem->unblock();
    }
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
    uint64 volatile sepc = riscv::read_sepc() + 4;
    uint64 volatile sstatus = riscv::read_sstatus();
    TCB::dispatch();
    riscv::write_sstatus(sstatus);
    riscv::write_sepc(sepc);
//    TCB::yield();
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
    if(--sem_value < 0 ) block();
}

void KernelSemaphore::signal() {
    if(++sem_value <= 0) unblock();
}