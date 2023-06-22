//
// Created by lazar on 6/22/23.
//

#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include "TCB.hpp"

class Scheduler {
private:

    class scheduled_node {
    public:
        TCB* value;
        scheduled_node* next;
    };

    scheduled_node* head = nullptr;
    scheduled_node* tail = nullptr;

public:

    Scheduler(): head(nullptr){}

    static Scheduler& get_instance();

    static TCB* get();

    static int put(TCB*);

};

#endif // SCHEDULER_HPP
