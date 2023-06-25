//
// Created by lazar on 6/22/23.
//

// Inspired by circiulums and practices

#include "../h/tcb.hpp"
#include "../h/utility.hpp"
#include "../h/output.hpp"
#include "../h/scheduler.hpp"
#include "../h/memory_allocator.hpp"

TCB* TCB::running = 0;
uint64 TCB::time_slice_counter = 0;

void TCB::pop_spp_spie() {
    asm volatile ("csrw sepc, ra");
    asm volatile ("sret");
}


TCB *TCB::create_thread(TCB::Body body) {
    return new TCB(body, TIME_SLICE);
}

TCB *TCB::create_thread(TCB::Body body, void* stack, void* arg) {
    return new TCB(body, TIME_SLICE, stack, arg);
}

void TCB::yield() {
    asm volatile ("mv a0, %[code]": : [code] "r"  (TCB::SWITCH_CODE));
    asm volatile("ecall");
}

void TCB::dispatch() {
    TCB* old = TCB::running;

    if(old != nullptr
        && old->get_state() != State::FINISHED
        && old->get_state() != State::BLOCKED)  Scheduler::put(old);

    TCB::running = Scheduler::get();

    TCB::context_switch(&old->context, &running->context);
}

void *TCB::operator new(size_t size) {
    return MemoryAllocator::allocate_blocks(
            MemoryAllocator::size_in_blocks(size)
            );
}


void TCB::operator delete(void *ptr) {
    MemoryAllocator::free_blocks(ptr);
}

void TCB::thread_wrapper() {
    TCB::pop_spp_spie();
    running->body(running->arg);
    running->set_state(State::FINISHED);
    running->unblock();
    TCB::yield();
}


TCB::TCB(TCB::Body body, uint64 time_slice, void *stack, void *arg):
    body(body), time_slice(time_slice), arg(arg) {

        this->stack =(uint64*)stack;
        uint64 sp_start = stack != nullptr ? (uint64) &this->stack[DEFAULT_STACK_SIZE] : 0;

        context = {
                (uint64)&thread_wrapper,
                sp_start
        };

        state = State::NOT_FINISHED;

        join_queue = KernelSemaphore::create_semaphore(0);

        if(body) Scheduler::put(this);
}

TCB::TCB(TCB::Body body, uint64 time_slice ):
    body(body), time_slice(time_slice) {

    stack = body != nullptr ? (uint64*) MemoryAllocator::allocate_blocks(MemoryAllocator::size_in_blocks(
                    DEFAULT_STACK_SIZE)): nullptr;

    uint64 sp_start = stack != nullptr ? (uint64) &stack[DEFAULT_STACK_SIZE] : 0;
    context = {
            (uint64)&thread_wrapper,
            sp_start
    };

    state = State::NOT_FINISHED;

    join_queue = KernelSemaphore::create_semaphore(0);

    if(body) Scheduler::put(this);

}

void TCB::unblock() {
    while(join_queue->get_value() < 0)
        join_queue->signal();
}

void TCB::add_blocked(TCB *tcb) {
   // Add deadlock guard
   if(tcb->get_state() != TCB::State::FINISHED)
       join_queue->wait();
}

TCB::~TCB() {
    MemoryAllocator::free_blocks(stack);
}



