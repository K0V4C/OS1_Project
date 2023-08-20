#ifndef KERNEL_CONSOLE_HPP
#define KERNEL_CONSOLE_HPP
#include "../lib/hw.h"
#include "../h/kernel_sem.hpp"

class KernelConsole {
private:

    struct Buffer{
    private:
        char* characters;
        uint64 len, head, tail;

    public:
        uint64 size;

        Buffer(uint64 len);
        void put(char);
        char get();

        KernelSemaphore *item_available, *space_available;

        void* operator new(size_t size);
        void operator delete (void* ptr);
    };

    Buffer *output_buffer, *input_buffer;

    KernelConsole();

    // todo add move and copy operators here

    static constexpr uint64 MAX_BUFFER_SIZE = 1024;

public:

    static KernelConsole& get_instance();

    static void flush_input();
    static void flush_output();

    static void output_put(char);
    static char output_get();

    static void input_put(char);
    static char input_get();

    static bool output_has_items();
    static bool input_not_full();

};


#endif // KERNEL_CONSOLE_HPP
