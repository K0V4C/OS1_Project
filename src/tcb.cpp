//
// Created by lazar on 6/22/23.
//

#include "../h/tcb.hpp"
#include "../h/utility.hpp"
#include "../h/output.hpp"
#include "../h/scheduler.hpp"

// I dont know how to this without name mangling
extern "C" void push_registers();
extern "C" void pop_registers();

TCB *TCB::create_thread(TCB::Body body) {
    return nullptr;
}

void TCB::yield() {

    push_registers();
    TCB::dispatch();
    pop_registers();
}

void TCB::dispatch() {
    TCB* old = TCB::running;
    if(old->isFinished())  Scheduler::put(old);
    TCB::running = Scheduler::get();

    TCB::context_switch(&old->context, &running->context);
}

