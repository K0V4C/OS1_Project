//
// Created by lazar on 6/22/23.
//

// Whole class inspired by videos from practices

#ifndef TCB_HPP
#define TCB_HPP

#include "../lib/hw.h"

class TCB {
public:
    using Body = void (*)();
private:

    Body body;
    uint64* stack;
    bool finished;
    bool blocked;
    uint64 time_slice;

    struct Context {
        uint64 ra;
        uint64 sp;
    };

    Context context;

    TCB(Body body, uint64 time_slice);

    static void thread_wrapper();
    static uint64 const TIME_SLICE = DEFAULT_TIME_SLICE;

public:

    static TCB* running;
    static  uint64 time_slice_counter;

    void setFinished(bool finished) {this->finished = finished;}
    bool isFinished() const {return finished;}

    void set_blocked(bool blocked) {this->blocked = blocked;}
    bool is_blocked() const {return blocked;}

    uint64 get_time_slice() {return time_slice; }

    static void yield();
    static void dispatch();
    static void context_switch(Context* old_context, Context* new_context);

    static TCB* create_thread(Body body);

    // Helper function for wrapper method
    static void pop_spp_spie();

    void* operator new(size_t size);
    void operator delete (void* ptr);

    ~TCB();
};

#endif // TCB_HPP
