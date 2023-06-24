//
// Created by lazar on 6/24/23.
//

#ifndef OS1_PROJECT_ASYNC_TESTS_HPP
#define OS1_PROJECT_ASYNC_TESTS_HPP

#include "../h/tcb.hpp"
#include "../h/output.hpp"
#include "../h/utility.hpp"
#include "../h/memory_allocator.hpp"
#include "../h/bit_masks.hpp"
void worker_A() {
    kvc::print_str("\nA start\n");

    for(uint64 i = 0; i < 10; i++ ){
        kvc::print_str("A: i= ");
        kvc::print_int(i);
        kvc::new_line();
        for(uint64 j = 0; j < 30000; j ++){
            for(uint64 k = 0; k < 3000; k++){
                // we waitin
            }
        }
    }

    kvc::print_str("\nA end\n");
}

void worker_B() {
    kvc::print_str("\nB start\n");

    for(uint64 i = 0; i < 10; i++ ){
        kvc::print_str("B: i= ");
        kvc::print_int(i);
        kvc::new_line();
        for(uint64 j = 0; j < 10000; j ++){
            for(uint64 k = 0; k < 3000; k++) {
                // we waitin
            }
        }
    }

    kvc::print_str("\nB end\n");
}

void worker_C() {
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


    kvc::print_str("\nC end\n");
}

void worker_D() {
    kvc::print_str("\nD start\n");
    for(uint64 i = 0; i < 10; i++ ){
        kvc::print_str("D: i= ");
        kvc::print_int(i);
        kvc::new_line();
        for(uint64 j = 0; j < 1000; j ++){
            for(uint64 k = 0; k < 30000; k++){
                // we waitin
            }
        }
    }
    kvc::print_str("\nD end\n");
}


auto async_run() -> void {

    kvc::print_str("\n------------- Startin async tests -------------\n");

    TCB* threads[5];

    threads[0] = TCB::create_thread(nullptr);
    TCB::running = threads[0];

    riscv::mask_set_sstatus(SStatus::SSTATUS_SIE);

    threads[1] = TCB::create_thread(worker_A);
    threads[2] = TCB::create_thread(worker_B);
    threads[3] = TCB::create_thread(worker_C);
    threads[4] = TCB::create_thread(worker_D);


    while(threads[1]->get_state() == TCB::State::NOT_FINISHED
        or threads[2]->get_state() == TCB::State::NOT_FINISHED
        or threads[3]->get_state() == TCB::State::NOT_FINISHED
        or threads[4]->get_state() == TCB::State::NOT_FINISHED)
        TCB::yield();

    delete threads[1];
    delete threads[2];
    delete threads[3];
    delete threads[4];



    kvc::print_str("\n------------- Ending async tests ---------------\n");
}

#endif //OS1_PROJECT_ASYNC_TESTS_HPP
