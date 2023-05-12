//
// Created by lazar on 5/12/23.
//

#ifndef TEST_MEM_ALLOCATOR
#define TEST_MEM_ALLOCATOR

#include "../h/MemoryAllocator.h"
#include "../lib/hw.h"
#include "../h/Utility.h"

#define PLUS_BLOCKS(x, offs) (void*)((char*)x + offs*MEM_BLOCK_SIZE)
#define MINUS_BLOCKS(x, offs) (void*)((char*)x - offs*MEM_BLOCK_SIZE)

auto print_allocated(uint64 i, void* adr) -> void {
    kvc::print_str("Actual memory allocated for block "); kvc::print_uint64(i);
    kvc::print_str(" is: "); kvc::print_void((void*)((char*)adr - (uint64)MEM_BLOCK_SIZE));
    kvc::print_str(" And ret value for that block is: "); kvc::print_void(adr); kvc::new_line();
}

auto memory_allocator_run() -> int {

    kvc::new_line();
    auto& instance = MemoryAllocator::get_instance();

    void *block_1, *block_2, *block_3, *block_4, *block_5, *block_6, *block_7, *block_8, *block_9, *block_10, *block11;

    kvc::print_str("Starting tests for Memory allocator: \n\n");
    // #################################################################################################################
    // Test 1
    block_1 = MemoryAllocator::allocate_blocks(7);
    void *first_addr = block_1;
    block_2 = MemoryAllocator::allocate_blocks(7);
    block_3 = MemoryAllocator::allocate_blocks(7);
    print_allocated(1, block_1);
    print_allocated(2, block_2);
    print_allocated(3, block_3);
    kvc::print_str("Free starts at: "); kvc::print_void((void*)((uint64)block_3 + 7*64)); kvc::new_line();
    // fff -> aaa -> afa -> aff -> fff
    kvc::__assert(PLUS_BLOCKS(block_1, 8), block_2);
    kvc::__assert(PLUS_BLOCKS(block_2, 8), block_3);
    MemoryAllocator::free_blocks(block_2);
    kvc::__assert(instance.get_start(), MINUS_BLOCKS(block_2, 1));
    MemoryAllocator::free_blocks(block_3);
    kvc::__assert(instance.get_start(), MINUS_BLOCKS(block_2, 1));
    MemoryAllocator::free_blocks(block_1);
    kvc::__assert(instance.get_start(), MINUS_BLOCKS(block_1, 1));
    kvc::print_str("Test 1 passed\n\n");
    // #################################################################################################################
    // Test 2
    // fff -> aaa -> afa -> aaa -> afa -> afaaf
    block_1 = MemoryAllocator::allocate_blocks(7);
    kvc::__assert(block_1, first_addr);
    block_2 = MemoryAllocator::allocate_blocks(7);
    block_3 = MemoryAllocator::allocate_blocks(7);

    print_allocated(1, block_1);
    print_allocated(2, block_2);
    print_allocated(3, block_3);

    MemoryAllocator::free_blocks(block_2);
    kvc::__assert(instance.get_start(), MINUS_BLOCKS(block_2, 1));
    block_2 = MemoryAllocator::allocate_blocks(7);
    print_allocated(2, block_2);
    kvc::__assert(MINUS_BLOCKS(instance.get_start(), 8), MINUS_BLOCKS(block_3, 1));
    MemoryAllocator::free_blocks(block_2);
    kvc::__assert(instance.get_start(), MINUS_BLOCKS(block_2, 1));
    block_2 = MemoryAllocator::allocate_blocks(15);
    print_allocated(2, block_2);
    kvc::__assert(PLUS_BLOCKS(instance.get_start(), 16), MINUS_BLOCKS(block_2, 1));
    MemoryAllocator::free_blocks(block_2);
    MemoryAllocator::free_blocks(block_1);
    MemoryAllocator::free_blocks(block_3);
    kvc::__assert(instance.get_start(), MINUS_BLOCKS(block_1, 1));
    kvc::print_str("Test 2 passed\n\n");
    // #################################################################################################################
    //Test 3

    block_1 = MemoryAllocator::allocate_blocks(7);
    kvc::__assert(block_1, first_addr);
    block_2 = MemoryAllocator::allocate_blocks(7);
    block_3 = MemoryAllocator::allocate_blocks(15);
    block_4 = MemoryAllocator::allocate_blocks(7);

    print_allocated(1, block_1);
    print_allocated(2, block_2);
    print_allocated(3, block_3);
    print_allocated(4, block_4);

    MemoryAllocator::free_blocks(block_1);
    kvc::__assert(instance.get_start(), MINUS_BLOCKS(block_1, 1));
    MemoryAllocator::free_blocks(block_3);
    block_3 = MemoryAllocator::allocate_blocks(15);

    MemoryAllocator::free_blocks(block_2);
    MemoryAllocator::free_blocks(block_3);
    MemoryAllocator::free_blocks(block_4);

    kvc::__assert(MINUS_BLOCKS(block_1, 1), instance.get_start());

    kvc::print_str("Test 3 passed\n\n");
    // #################################################################################################################
    // Test 4
    block_1 = MemoryAllocator::allocate_blocks(15);
    kvc::__assert(block_1, first_addr);
    block_2 = MemoryAllocator::allocate_blocks(15);
    block_3 = MemoryAllocator::allocate_blocks(15);
    block_4 = MemoryAllocator::allocate_blocks(15);
    kvc::new_line();
    print_allocated(1, block_1);
    print_allocated(1, block_2);
    print_allocated(1, block_3);
    print_allocated(1, block_4);

    kvc::print_str("Test 4 passed \n\n");

    // #################################################################################################################
    // Test 5


    return 0;
}

#endif //TEST_MEM_ALLOCATOR
