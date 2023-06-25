#include "../tests/memory_allocator_test.hpp"
#include "../tests/sys_calls_test.hpp"
#include "../h/tcb.hpp"
#include "../tests/sync_tests.h"
#include "../tests/async_tests.hpp"
#include "../tests/semaphore_test.hpp"

extern "C" void trap_supervisor();

inline void set_stvec(){
   riscv::write_stvec((uint64)((char*)&trap_supervisor + 1));
}

auto main() -> int {

    kvc::print_str("Poceo\n");

    set_stvec();





//    sync_test_run();
//    async_run();
    sem_run();
    memory_allocator_run();

    kvc::print_str("Uspeo\n");

    return 0;
}
