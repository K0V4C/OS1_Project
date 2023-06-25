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
    enum State{
        NOT_FINISHED,
        FINISHED,
        BLOCKED,
    };
private:

    Body body;
    uint64* stack;
    uint64 time_slice;
    State state;

    struct Context {
        uint64 ra;
        uint64 sp;
    };

    Context context;

    TCB(Body body, uint64 time_slice);

    static void thread_wrapper();
    static uint64 const TIME_SLICE = DEFAULT_TIME_SLICE;
    static uint64  const SWITCH_CODE = 0xff;

public:

    static TCB* running;
    static  uint64 time_slice_counter;

    void set_state(State state) {
        this->state = state;
    }
    State get_state() const {
        return this->state;
    }

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
