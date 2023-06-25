#include "../tests/memory_allocator_test.hpp"
#include "../tests/sys_calls_test.hpp"
#include "../h/tcb.hpp"
//#include "../tests/sync_tests.h"
//#include "../tests/async_tests.hpp"
//#include "../tests/semaphore_test.hpp"

extern "C" void trap_supervisor();

inline void set_stvec(){
   riscv::write_stvec((uint64)((char*)&trap_supervisor + 1));
}

void dummy_thread(void*) {
    uint64 volatile dummy = 0;
    while(true) {
//        dummy++;
        TCB::yield();
    }
}

auto main() -> int {

    kvc::print_str("Poceo\n");

    set_stvec();

    TCB* main_thread = TCB::create_thread(nullptr);
    TCB::running = main_thread;

    TCB* loop_thread = TCB::create_thread(dummy_thread);

    sys_calls_run1();



//    sync_test_run();
//    async_run();
//    sem_run();
//    memory_allocator_run();

    kvc::print_str("Uspeo\n");

    return 0;
}
