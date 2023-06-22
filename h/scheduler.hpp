//
// Created by lazar on 6/22/23.
//

#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "tcb.hpp"

class Scheduler {
private:

    struct scheduled_node {
    public:
        tcb* value;
        scheduled_node* next;
    };

    scheduled_node* head = nullptr;
    scheduled_node* tail = nullptr;

    static Scheduler& get_instance();

public:

    static tcb* get();

    static int put(tcb*);

};

#endif // SCHEDULER_HPP
