
#include "../h/MemoryAllocator.hpp"

//Inspired by curriculums and practices

MemoryAllocator::MemoryAllocator() {
    start_free_mem = (FreeMem*)HEAP_START_ADDR;

    start_free_mem->next = nullptr;
    start_free_mem->prev = nullptr;
    start_free_mem->size = ((uint64)HEAP_END_ADDR - (uint64)HEAP_START_ADDR) / MEM_BLOCK_SIZE;
}

//Joins 2 memory segments together if their addresses continue one another
auto MemoryAllocator::join(FreeMem* obj) -> void {

    if(!obj)
        return;

    if( (((char*)obj) + obj->size * MEM_BLOCK_SIZE) != ((char*)obj->next))
        return;

    //Link backwards
    if(obj->next->next){
        obj->next->next->prev = obj;
    }
    //Ignore one in the middle
    obj->size += obj->next->size;
    obj->next = obj->next->next;


}

auto MemoryAllocator::init_header(void * adr , uint64 size) -> void {
    *(uint64 *)adr = size;

    uint32 * start = (uint32*)adr + 2;
    for(int i = 0; i < 14; i++){
            start[i] = 0xDEADBEEF;
    }
}

auto MemoryAllocator::get_instance() -> MemoryAllocator& {
    static MemoryAllocator instance;
    return instance;
}

auto MemoryAllocator::allocate_blocks(uint64 size)  -> void* {

    if(size < 1) {
        return nullptr;
    }

    size += 1; // Waste one block until I find a better way

    MemoryAllocator& instance = MemoryAllocator::get_instance();

    if (!instance.start_free_mem) {
        return nullptr;
        //Allocations BOOM, no memory
    }

    FreeMem* iter;
    for(iter = instance.start_free_mem; iter  && iter->size < size; iter = iter->next);

    //Blocks of this size can not be found
    FreeMem* first_valid = iter;

    void* ret = nullptr;

    //Blocks of this size can not be found
    if(first_valid == nullptr)
        return ret;

    //Find next location and init struct
    uint64 offset = (uint64)(size * MEM_BLOCK_SIZE);
    //Test if next location is at the exact distance as the size
    FreeMem* next_location ;
    if(first_valid->size != size) {
        next_location = (FreeMem *) (((char *) first_valid) + offset);
    } else {
        next_location = first_valid->next;
    }

    //Get return address
    ret = (void*)(((char*)first_valid) + MEM_BLOCK_SIZE);

    //Potential problem if memory is full
    if(first_valid->size == size){

        first_valid->next->prev = first_valid->prev;
        if(first_valid->prev)
            first_valid->prev->next = first_valid->next;
        else
            instance.start_free_mem = first_valid->next;

        init_header(first_valid, size);


        return ret;
    }

    //Allocate start
    if(!first_valid->prev) {
        //If next block exists link it
        if(first_valid->next) {
            first_valid->next->prev = next_location;
        }
        next_location->next = first_valid->next;
        next_location->prev = nullptr;
        next_location->size = first_valid->size - size;

        //Move start pointer
        instance.start_free_mem = next_location;

    } else if(first_valid->next && first_valid->prev) { //Allocate middle
        next_location->next = first_valid->next;
        next_location->prev = first_valid->prev;
        first_valid->prev->next = next_location;
        first_valid->next->prev = next_location;
        next_location->size = first_valid->size - size;

    } else if(!first_valid->next){ //Allocate end
        next_location->next = nullptr;
        first_valid->prev->next = next_location;
        next_location->prev = first_valid->prev;
        next_location->size = first_valid->size - size;

    }

    //Prepare allocated memory
    init_header(first_valid, size);

    return ret;
}

auto MemoryAllocator::free_blocks(void* adr) -> int {

    //Tried to free null
    if(adr == nullptr){
        return -1;
    }

    //Offset adr back one block
    adr = (void*)(((char*)adr) - MEM_BLOCK_SIZE);
    //From first block read how many blocks is needed to be dealloc
    uint64 size = *((uint64 *)adr);

    MemoryAllocator& instance = MemoryAllocator::get_instance();

    FreeMem* iter = instance.start_free_mem;

    // Find first that is AFTER segment to dealloc
    for(; (void*)iter < adr && iter->next; iter = iter->next);

    // Independent if inserting at start or later
    FreeMem* new_location = (FreeMem*)adr;
    new_location->size = size;
    new_location->next = iter;

    // At start
    if(!instance.start_free_mem || iter == instance.start_free_mem) {
        new_location->prev = nullptr;

        if(instance.start_free_mem) {
            new_location->next = instance.start_free_mem;
            instance.start_free_mem->prev = new_location;
        }

        instance.start_free_mem = new_location;

    } else { // Somewhere else
        new_location->prev = iter->prev;
        if(iter->prev) {
            iter->prev->next = new_location;
            iter->prev = new_location;
        }
    }

    // Join 2 segments together
    join(new_location);
    join(new_location->prev);


    return 0;
}
