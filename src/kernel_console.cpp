#include "../h/kernel_console.hpp"
#include "../h/memory_allocator.hpp"

KernelConsole::Buffer::Buffer(uint64 len)
    : len(KernelConsole::MAX_BUFFER_SIZE), head(0), tail(0), size(0) {

   this->characters = (char*) MemoryAllocator::allocate_blocks(
            MemoryAllocator::size_in_blocks(len));

    item_available = KernelSemaphore::create_semaphore(0);
    space_available = KernelSemaphore::create_semaphore(KernelConsole::MAX_BUFFER_SIZE);

}

void KernelConsole::Buffer::put(char a) {
    space_available->wait();

    characters[tail++] = a;
    tail %= len;
    size++;

    item_available->signal();
}

char KernelConsole::Buffer::get() {
    item_available->wait();

    char ret = characters[head++];
    head %= len;
    size--;

    space_available->signal();
    return ret;
}

void *KernelConsole::Buffer::operator new(size_t size) {
    return MemoryAllocator::allocate_blocks(MemoryAllocator::size_in_blocks(size));
}

void KernelConsole::Buffer::operator delete(void *ptr) {
    MemoryAllocator::free_blocks(ptr);
}

KernelConsole &KernelConsole::get_instance() {
    static KernelConsole instance;
    return instance;
}

void KernelConsole::output_put(char a) {
    KernelConsole::get_instance().output_buffer->put(a);
}

char KernelConsole::output_get() {
    return KernelConsole::get_instance().output_buffer->get();
}

void KernelConsole::input_put(char a) {
    KernelConsole::get_instance().input_buffer->put(a);
}

char KernelConsole::input_get() {
    return KernelConsole::get_instance().input_buffer->get();
}

bool KernelConsole::output_has_items() {
    return KernelConsole::get_instance().output_buffer->size != 0;
}

bool KernelConsole::input_not_full() {
    return KernelConsole::get_instance().input_buffer->size != KernelConsole::MAX_BUFFER_SIZE;
}

KernelConsole::KernelConsole() {
    input_buffer = new Buffer(KernelConsole::MAX_BUFFER_SIZE);
    output_buffer = new Buffer(KernelConsole::MAX_BUFFER_SIZE);
}

void KernelConsole::flush_input() {
    // Input stream
    char volatile console_status = *((char*)CONSOLE_STATUS);
    while((console_status & CONSOLE_RX_STATUS_BIT) && input_not_full()) {
        char* volatile console_rx = (char*)CONSOLE_RX_DATA;
        char volatile data = *console_rx;

        KernelConsole::input_put(data);
        console_status = *((char*)CONSOLE_STATUS);
    }
}

void KernelConsole::flush_output() {
    // Output stream
    char volatile console_status = *((char*)CONSOLE_STATUS);
    while((console_status & CONSOLE_TX_STATUS_BIT) && output_has_items()) {
        char to_send = KernelConsole::output_get();

        *((uint64*)CONSOLE_TX_DATA) = to_send;
        console_status = *((char*)CONSOLE_STATUS);
    }
}
