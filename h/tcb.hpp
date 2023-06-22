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

    static TCB* running;

    class Context {
    public:
        uint64 ra;
        uint64 sp;
    };

    Context context;

public:

    void setFinished(bool finished) {this->finished = finished;}
    bool isFinished() {return this->finished;}

    static void yield();
    static void dispatch();
    static void context_switch(Context* old_context, Context* new_context);

    static TCB* create_thread(Body body);

};

#endif // TCB_HPP