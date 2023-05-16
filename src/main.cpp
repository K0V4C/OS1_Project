#include "../tests/memory_allocator_test.hpp"
#include "../tests/sys_calls_test.hpp"
#include "../h/syscall_c.hpp"
#include "../h/utility.hpp"

extern "C" void trap_supervisor();

inline void set_stvec(){
   kvc::write_stvec((uint64)&trap_supervisor);
}

auto main() -> int {

    kvc::print_str("Poceo\n");
    set_stvec();

    memory_allocator_run();
    sys_calls_run();

    kvc::print_str("Uspeo\n");



    return 0;
}
