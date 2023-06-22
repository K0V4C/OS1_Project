#include "../tests/memory_allocator_test.hpp"
#include "../tests/sys_calls_test.hpp"
#include "../h/syscall_c.hpp"
#include "../h/utility.hpp"

extern "C" void trap_supervisor();

inline void set_stvec(){
   riscv::write_stvec((uint64)((char*)&trap_supervisor + 1));
}

auto main() -> int {

    kvc::print_str("Poceo\n");

    set_stvec();

    // Uncomment to test timers
    // riscv::write_sstatus(0x02);

    memory_allocator_run();
    sys_calls_run();

    kvc::print_str("Uspeo\n");



    return 0;
}
