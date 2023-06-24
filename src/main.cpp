#include "../tests/memory_allocator_test.hpp"
#include "../tests/sys_calls_test.hpp"
#include "../h/tcb.hpp"
#include "../tests/sync_tests.h"
#include "../tests/async_tests.hpp"

extern "C" void trap_supervisor();

inline void set_stvec(){
   riscv::write_stvec((uint64)((char*)&trap_supervisor + 1));
}

auto main() -> int {

    kvc::print_str("Poceo\n");

    set_stvec();

    // Uncomment to test timers
    // riscv::write_sstatus(0x02);
//    sys_calls_run();
//    sync_test_run();
    async_run();

    memory_allocator_run();

    kvc::print_str("Uspeo\n");

    return 0;
}
