

//
// Created by lazar on 5/10/23.
//

#ifndef MEMORYALLOCATOR_H
#define MEMORYALLOCATOR_H

#include "../lib/hw.h"

class MemoryAllocator {
private:

    struct FreeMem{
        FreeMem* next;
        FreeMem* prev;
        size_t size;
    };

    FreeMem* start_free_mem;

    //Default ctor
    MemoryAllocator();

    //REDACTED
    MemoryAllocator(MemoryAllocator&) = delete;
    MemoryAllocator(MemoryAllocator&&) = delete;

    static void join(FreeMem*);
    static void init_header(void*, uint64);

    bool inline static overlaps(FreeMem* iter , void* raw) {
        return (raw >= (void*)iter && raw < (void*)((char*)iter + iter->size*MEM_BLOCK_SIZE));
    }

public:

    static uint64 size_in_blocks(uint64 size_in_bytes) {
        return size_in_bytes / MEM_BLOCK_SIZE + ((size_in_bytes % MEM_BLOCK_SIZE) ? 1 : 0);
    }

    const void* get_start() const {
        return (void*)start_free_mem;
    }

    static MemoryAllocator& get_instance();

    static void* allocate_blocks(uint64);
    static int free_blocks(void*);
};


#endif //MEMORYALLOCATOR_H
