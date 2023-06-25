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
    /*C like way
    TCB* new_tcb = (TCB*) MemoryAllocator::allocate_blocks(
            MemoryAllocator::size_in_blocks(sizeof (TCB))
            );

    if (!new_tcb) return nullptr;

    new_tcb->body = body;
    new_tcb->stack = body != nullptr ? (uint64*) MemoryAllocator::allocate_blocks(MemoryAllocator::size_in_blocks(sizeof(uint64)* DEFAULT_STACK_SIZE)) : nullptr;

    uint64 sp_start = new_tcb->stack != nullptr ? (uint64) &new_tcb->stack[DEFAULT_STACK_SIZE] : 0;
    new_tcb->context = {
            (uint64)body, sp_start
    };

    new_tcb->finished = false;

    if(body) Scheduler::put(new_tcb);

    return new_tcb;
     */
    return new TCB(body, TIME_SLICE);

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
    running->body();
    running->set_state(State::FINISHED);
    TCB::yield();
}



TCB::TCB(TCB::Body body, uint64 time_slice ):
    body(body), time_slice(time_slice) {

    stack = body != nullptr ? (uint64*) MemoryAllocator::allocate_blocks(
            MemoryAllocator::size_in_blocks(
                    DEFAULT_STACK_SIZE)
                    ): nullptr;

    uint64 sp_start = stack != nullptr ? (uint64) &stack[DEFAULT_STACK_SIZE] : 0;
    context = {
            (uint64)&thread_wrapper, sp_start
    };

    state = State::NOT_FINISHED;

    if(body) Scheduler::put(this);

}

TCB::~TCB() {
    MemoryAllocator::free_blocks(stack);
}