#include "../h/abi.hpp"
#include "../h/memory_allocator.hpp"
#include "../h/output.hpp"

namespace ABI {

    void* mem_alloc (uint64 size) {
        kvc::print_str("Alokacija -> : ");
        kvc::print_uint64(MemoryAllocator::size_in_blocks(size));
        return MemoryAllocator::allocate_blocks(MemoryAllocator::size_in_blocks(size));
    } 

    int mem_free(void* address) {
        return MemoryAllocator::free_blocks(address);
    }

}
