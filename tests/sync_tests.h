//
// Created by lazar on 6/23/23.
//

#ifndef OS1_PROJECT_SYNC_TESTS_H
#define OS1_PROJECT_SYNC_TESTS_H

#include "../h/tcb.hpp"
#include "../h/output.hpp"
#include "../h/memory_allocator.hpp"

int fib(int n, const char* a) {
    //kvc::print_str("\n");
    //kvc::print_str(a);

    if(n <= 1) return n;
    TCB::yield();
//    if(n % 4 == 0) TCB::yield();
    return fib(n-1, a) + fib(n-2, a);
}

void worker_a(void* a) {

    kvc::print_str("Worker staring");
    for(int i = 0; i < 3; i++) {
        kvc::print_str("A = ");
        kvc::print_int(i);
        kvc::new_line();
    }

    TCB::yield();

    int val = fib(20, "wa");
    kvc::print_str("Fibonaci A is: ");
    kvc::print_int(val);
    kvc::new_line();


    kvc::print_str("Worker stoping");
    for(int i = 0; i < 3; i++) {
        kvc::print_str("A = ");
        kvc::print_int(i);
        kvc::new_line();
    }
//
//    TCB::running->setFinished(true);
//    TCB::yield();
}

void worker_b(void* a) {

    kvc::print_str("Worker staring");
    for(int i = 0; i < 3; i++) {
        kvc::print_str("B = ");
        kvc::print_int(i);
        kvc::new_line();
    }

    TCB::yield();

    int val = fib(25, "wb");
    kvc::print_str("Fibonaci B is: ");
    kvc::print_int(val);
    kvc::new_line();


    kvc::print_str("\nWorker stoping\n");
    for(int i = 0; i < 3; i++) {
        kvc::print_str("B = ");
        kvc::print_int(i);
        kvc::new_line();
    }
//
//    TCB::running->setFinished(true);
//    TCB::yield();
}

void worker_c(void* a) {

    kvc::print_str("\nWorker staring\n");
    for(int i = 0; i < 3; i++) {
        kvc::print_str("C = ");
        kvc::print_int(i);
        kvc::new_line();
    }

    TCB::yield();

    int val = fib(30, "wc");
    kvc::print_str("Fibonaci C is: ");
    kvc::print_int(val);
    kvc::new_line();


    kvc::print_str("\nWorker stoping\n");
    for(int i = 0; i < 3; i++) {
        kvc::print_str("C = ");
        kvc::print_int(i);
        kvc::new_line();
    }
//
//    TCB::running->setFinished(true);
//    TCB::yield();
}

auto sync_test_run() -> void {

    kvc::print_str("\nSYNC TESTS\n");

    TCB* threads[5];

    // Delegating main thread
    threads[0] = TCB::create_thread(nullptr);
    TCB::running = threads[0];

    threads[1] = TCB::create_thread(worker_a);
    threads[2] = TCB::create_thread(worker_b);
    threads[3] = TCB::create_thread(worker_c);

    while(threads[1]->get_state() == TCB::State::NOT_FINISHED
        or threads[2]->get_state() == TCB::State::NOT_FINISHED
        or threads[3]->get_state() == TCB::State::NOT_FINISHED)
        TCB::yield();

    delete threads[1];
    delete threads[2];
    delete threads[3];

    kvc::print_str("\nTest 1 passed\n");

    TCB* threads2[100];

    for(int i = 0; i < 100; i++){
        threads2[i] = TCB::create_thread(worker_a);
    }

    while(true) {
        int cnt = 0;
        for(int i = 0; i < 100; i++) {
            if(threads2[i]->get_state() == TCB::State::FINISHED)
                cnt++;
        }
        if(cnt == 100)
            break;
        TCB::yield();
    }

    for(int i = 0; i < 100; i++){
        delete threads2[i];
    }

    kvc::print_str("\nTest 2 passed\n");
}

#endif //OS1_PROJECT_SYNC_TESTS_H
