//
// Created by lazar on 6/22/23.
//

// Inspired by circiulums and practices

#include "../h/tcb.hpp"
#include "../h/utility.hpp"
#include "../h/output.hpp"
#include "../h/scheduler.hpp"
#include "../h/memory_allocator.hpp"
#include "../h/syscall_c.h"
#include "../h/bit_masks.hpp"

TCB* TCB::running = 0;
uint64 TCB::time_slice_counter = 0;

void TCB::pop_spp_spie() {
    asm volatile ("csrw sepc, ra");
    asm volatile ("sret");
}

TCB *TCB::create_thread(TCB::Body body, void* stack, void* arg) {
    return new TCB(body, TIME_SLICE, stack, arg);
}
void TCB::yield() {
    // todo zasto moram da pamtim sepc i sstatus
    uint64 volatile sepc = riscv::read_sepc();
    uint64 volatile sstatus = riscv::read_sstatus();
    TCB::dispatch();
    riscv::write_sstatus(sstatus);
    riscv::write_sepc(sepc);
}

void TCB::dispatch() {
    TCB* old = TCB::running;

    if(old != nullptr
        && old->get_state() != State::FINISHED
        && old->get_state() != State::BLOCKED
        && old->get_state() != State::SLEEPING)  Scheduler::put(old);

    TCB::running = Scheduler::get();

    // Dealocation, beware
    if(old->get_state() == FINISHED) delete old;

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
    thread_exit();
}


TCB::TCB(TCB::Body body, uint64 time_slice, void *stack, void *arg):
    body(body), time_slice(time_slice), arg(arg) {

        if(body == nullptr) {
            this->stack = body != nullptr ? (char*) MemoryAllocator::allocate_blocks(MemoryAllocator::size_in_blocks(
                    DEFAULT_STACK_SIZE)): nullptr;
        } else {
            this->stack = (char *) stack;
        }

        uint64 sp_start = this->stack != nullptr ? (uint64) &this->stack[DEFAULT_STACK_SIZE] : 0;
        context = {
                (uint64)&thread_wrapper,
                sp_start
        };

        state = State::NOT_FINISHED;

        join_queue = KernelSemaphore::create_semaphore(0);
        sem_return = 0;

        if(body) Scheduler::put(this);
}

void TCB::unblock() {
    while(join_queue->get_value() < 0)
        join_queue->signal();
}

void TCB::add_blocked(TCB *tcb) {
   // Add deadlock guard
   if(get_state() != TCB::State::FINISHED)
       join_queue->wait();
}

TCB::~TCB() {
    MemoryAllocator::free_blocks(stack);
}

TCB::sleep_node* TCB::sleep_list_first = nullptr;
// For thread sleep
void TCB::tick() {
    if(TCB::sleep_list_first == nullptr)
        return;

    sleep_list_first->timer--;
    
    while(sleep_list_first != nullptr && sleep_list_first->timer == 0){
        sleep_node* to_delete = sleep_list_first;

        sleep_list_first->sleeping_tcb->set_state(State::NOT_FINISHED);
        Scheduler::put(sleep_list_first->sleeping_tcb);
        sleep_list_first = sleep_list_first->next;

        delete to_delete;
    }
}

void TCB::put_to_sleep(uint64 time) {

    if(time == 0) return;

    sleep_node* new_node = new sleep_node(time, TCB::running);
    new_node->next = nullptr;

    if(sleep_list_first == nullptr){
        sleep_list_first = new_node;
    } else {

        sleep_node *iter_current, *iter_prev;

        iter_current = sleep_list_first;
        iter_prev = nullptr;

        while(iter_current != nullptr && (new_node->timer >= iter_current->timer )) {
            new_node->timer -= iter_current->timer;
            iter_prev = iter_current;
            iter_current = iter_current->next;
        }

        if(iter_current == sleep_list_first) {
            // Insert at the start
            sleep_list_first->timer -= new_node->timer;
            new_node->next = sleep_list_first;
            sleep_list_first = new_node;
        } else if (iter_current == nullptr) {
            // Insert at the end
            iter_prev->next = new_node;
        } else {
            // Insert in the middle
            iter_prev->next = new_node;
            new_node->next = iter_current;
        }

    }

    TCB::running->set_state(State::SLEEPING);
    TCB::yield();
}


void *TCB::sleep_node::operator new(size_t size) {
    return MemoryAllocator::allocate_blocks(MemoryAllocator::size_in_blocks(size));
}

void TCB::sleep_node::operator delete(void *ptr) {
    MemoryAllocator::free_blocks(ptr);
}
