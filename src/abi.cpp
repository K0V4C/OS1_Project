#include "../h/abi.hpp"
#include "../h/memory_allocator.hpp"

namespace ABI {

    void* mem_alloc (uint64 size) {
        return MemoryAllocator::allocate_blocks(size);
    } 

    int mem_free(void* address) {
        return MemoryAllocator::free_blocks(address);
    }

}
