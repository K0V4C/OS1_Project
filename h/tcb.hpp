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
    uint64 time_slice;

    static uint64 const TIME_SLICE = DEFAULT_TIME_SLICE;
    static  uint64 time_slice_counter;

    struct Context {
        uint64 ra;
        uint64 sp;
    };

    Context context;

    TCB(Body body, uint64 time_slice);

public:

    static TCB* running;

    void setFinished(bool finished) {this->finished = finished;}
    bool isFinished() const {return finished;}

    static void yield();
    static void dispatch();
    static void context_switch(Context* old_context, Context* new_context);

    static TCB* create_thread(Body body);

    void* operator new(size_t size);
    void operator delete (void* ptr);

    ~TCB();
};

#endif // TCB_HPP
