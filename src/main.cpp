#include "../tests/memory_allocator_test.hpp"
#include "../tests/sys_calls_test.hpp"
#include "../h/tcb.hpp"
#include "../tests/sync_tests.h"
#include "../tests/async_tests.hpp"
#include "../tests/semaphore_test.hpp"

void userMain();

extern "C" void trap_supervisor();

inline void set_stvec(){
   riscv::write_stvec((uint64)((char*)&trap_supervisor + 1));
}

void dummy_thread(void*) {
    while(true) {
//        kvc::print_str("==lood thread==\n");
        TCB::yield();
    }
}

//TODO MAKE SEM_CLOSE WORK WITH -1

auto main() -> int {

    kvc::print_str("Poceo\n");
    set_stvec();

    // Delegating main and idle thread
    TCB* main_thread = TCB::create_thread(nullptr);
    TCB::running = main_thread;
    TCB* loop_thread = TCB::create_thread(dummy_thread);

    riscv::mask_set_sstatus(SStatus::SSTATUS_SIE);
    change_privilege();
    userMain();

//    sys_calls_run1();
//    sys_calls_run2();
//    sync_test_run();
//    async_run();
//    sem_run();
//    memory_allocator_run();

    kvc::print_str("Uspeo\n");

    return 0;
}
