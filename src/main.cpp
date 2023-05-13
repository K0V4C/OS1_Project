//
// Created by lazar on 5/11/23.
//

#include "../h/MemoryAllocator.hpp"
#include "../lib/console.h"
#include "../tests/MemoryAllocatorTest.hpp"
#include "../h/Utility.hpp"

auto main() -> int {

    memory_allocator_run();

    uint64 * arr = (uint64 *)MemoryAllocator::allocate_blocks(125);

    for(int i = 0; i < 1000; i++)
        arr[i] = i;

    uint64 u = 0;
    for(int i = 0; i < 1000; i++)
        u += arr[i];

    kvc::__assert((uint64)1000*999/2, (uint64)u);

    return 0;
}
