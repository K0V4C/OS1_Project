//
// Created by lazar on 5/11/23.
//

#include "../h/memory_allocator.hpp"
#include "../lib/console.h"
#include "../tests/memory_allocator_test.hpp"
#include "../h/interrupt_handler.hpp"
#include "../h/syscall_c.hpp"
#include "../h/utility.hpp"

extern "C" void trap_supervisor();

inline void set_stvec(){
    __asm__ volatile("csrw stvec, %[addr]"
            :
            : [addr] "r" (&trap_supervisor)
    );
}

auto main() -> int {

    kvc::print_str("Poceo\n");

    set_stvec();
    void* t = mem_alloc(1024);

//    //__asm__ volatile("csrs sstatus, 0x02");
//
//    __asm__ volatile("ecall");

    kvc::print_str("Uspeo\n");

    memory_allocator_run();


    return 0;
}
