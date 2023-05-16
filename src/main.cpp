//
// Created by lazar on 5/11/23.
//

#include "../h/memory_allocator.hpp"
#include "../tests/memory_allocator_test.hpp"
#include "../h/syscall_c.hpp"
#include "../h/utility.hpp"

extern "C" void trap_supervisor();

inline void set_stvec(){
   kvc::write_stvec((uint64)&trap_supervisor);
}

auto main() -> int {

    kvc::print_str("Poceo\n");

    set_stvec();
    void *t = nullptr;
    t = mem_alloc(512);
    mem_free(t);
    kvc::print_void(t);

    kvc::print_str("Uspeo\n");

    memory_allocator_run();


    return 0;
}
