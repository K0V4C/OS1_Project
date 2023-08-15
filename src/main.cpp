#include "../h/tcb.hpp"
#include "../h/utility.hpp"
#include "../h/output.hpp"
#include "../h/syscall_c.h"
#include "../h/bit_masks.hpp"

typedef TCB* thread_t;

void userMain();
extern "C" void trap_supervisor();

inline void set_stvec(){
   riscv::write_stvec((uint64)((char*)&trap_supervisor + 1));
}

void dummy_thread(void*) {
    while(true) {
//        kvc::print_str("==loop thread==\n");
        TCB::yield();
    }
}

inline void thread_setup(){
    thread_t main_thread, loop_thread;

    thread_create(&main_thread, nullptr, nullptr);
    thread_create(&loop_thread, dummy_thread, nullptr);

    TCB::running = main_thread;
}

void user_main_wrapper(void*){
    userMain();
}

//TODO MAKE SEM_CLOSE WORK WITH -1

auto main() -> int {

    set_stvec();
    // Delegating main and idle thread
    thread_setup();
    riscv::mask_set_sstatus(SStatus::SSTATUS_SIE);
    thread_t user_main;
//    userMain();
    change_privilege();
    thread_create(&user_main, user_main_wrapper, nullptr);
//    userMain();
    thread_exit();
    return 0;
}


// ++++++++++++++++++++++ OLD TESTS  +++++++++++++++++++++++++=
//#include "../tests/sync_tests.h"
//#include "../tests/async_tests.hpp"
//#include "../tests/semaphore_test.hpp"
//#include "../tests/memory_allocator_test.hpp"
//#include "../tests/sys_calls_test.hpp"
//    sys_calls_run1();
//    sys_calls_run2();
//    sync_test_run();
//    async_run();
//    sem_run();
//    memory_allocator_run();
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++