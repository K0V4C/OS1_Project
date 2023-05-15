//
// Created by lazar on 5/11/23.
//

#include "../h/memory_allocator.hpp"
#include "../lib/console.h"
#include "../tests/memory_allocator_test.hpp"
#include "../h/utility.hpp"
#include "../h/interrupt_handler.hpp"
#include "../h/syscall_c.hpp"

extern "C" void trap_supervisor();

auto main() -> int {

    kvc::print_str("Poceo\n");

    __asm__ volatile("csrw stvec, %[addr]"
            :
            : [addr] "r" (&trap_supervisor)
            );

    void* t = mem_alloc(1024);

//    //__asm__ volatile("csrs sstatus, 0x02");
//
//    __asm__ volatile("ecall");

    kvc::print_str("Uspeo\n");

//    memory_allocator_run();
//
//    uint64 * arr = (uint64 *)MemoryAllocator::allocate_blocks(125);
//
//    for(int i = 0; i < 1000; i++)
//        arr[i] = i;
//
//    uint64 u = 0;
//    for(int i = 0; i < 1000; i++)
//        u += arr[i];
//
//    kvc::__assert((uint64)1000*999/2, (uint64)u);

    return 0;
}
