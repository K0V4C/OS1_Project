#ifndef ABI_SYSCALLS
#define ABI_SYSCALLS

#include "../lib/hw.h"

namespace ABI {

    void* mem_alloc (uint64 size);

    int mem_free(void* address);
}

#endif