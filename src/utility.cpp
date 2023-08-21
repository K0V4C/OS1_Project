#include "../h/utility.hpp"
#include "../h/syscall_c.h"
#include "../h/bit_masks.hpp"
#include "../h/tcb.hpp"

extern "C" void trap_supervisor();
typedef TCB* thread_t;
void userMain();


void riscv::user_main_wrapper(void*) {
    userMain();
}

void riscv::idle_thread(void*) {
    while(true) {
        thread_dispatch();
    }
}

void riscv::setup_interrupt_routine() {
    riscv::write_stvec((uint64)((char*)&trap_supervisor + 1));
}

void riscv::set_main_and_idle() {
    thread_t main_thread, loop_thread;

    thread_create(&main_thread, nullptr, nullptr);
    thread_create(&loop_thread, idle_thread, nullptr);

    TCB::running = main_thread;
}

void riscv::enable_interrupts() {
    riscv::mask_set_sstatus(SStatus::SSTATUS_SIE);
}

void riscv::run_user_main() {
    thread_dispatch();
    TCB::set_user_mode(true);
    thread_t user_main;
    thread_create(&user_main, riscv::user_main_wrapper, nullptr);
    // Wait for user main to finish
    thread_join(user_main);
}

