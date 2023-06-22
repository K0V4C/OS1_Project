//
// Created by lazar on 6/22/23.
//

#ifndef TCB_HPP
#define TCB_HPP

#include "../lib/hw.h"

class tcb {
public:
    using Body = void (*)();
private:

    Body body;
    uint64* stack;
    bool state;

public:

    void set_state(bool state) {this->state = state;}
    bool get_state() {return this->state;}

    static void yield();

    uint64 sp;

    static tcb* create_thread(Body body);


};

#endif // TCB_HPP
