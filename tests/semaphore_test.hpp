//
// Created by lazar on 6/24/23.
//

#ifndef OS1_PROJECT_SEMAPHORE_TEST_HPP
#define OS1_PROJECT_SEMAPHORE_TEST_HPP

#include "../h/output.hpp"
#include "../h/tcb.hpp"
#include "../h/kernel_sem.hpp"


KernelSemaphore* sem1;
KernelSemaphore* sem2;

auto player_one() -> void {
    for(int i =  0; i < 10; i++) {
        sem1->wait();
        kvc::print_str("Player one \n");
        for (uint64 i = 0; i < 100000; i++)
            for(uint64 j = 0; j < 1000; j++);
//        TCB::yield();
        sem2->signal();
    }
}

auto player_two() -> void  {
    for(int i = 0; i < 10; i++) {
        sem2->wait();
        kvc::print_str("Player two \n");
        for (uint64 i = 0; i < 100000; i++)
            for(uint64 j = 0; j < 1000; j++);
//        TCB::yield();
        sem1->signal();
    }
}


auto sem_run() -> void {

    TCB* threads[3];

    sem1 = KernelSemaphore::create_semaphore(1);
    sem2 = KernelSemaphore::create_semaphore(3);

    // Delegating main thread
    threads[0] = TCB::create_thread(nullptr);
    TCB::running = threads[0];

    threads[1] = TCB::create_thread(&player_one);
    threads[2] = TCB::create_thread(&player_two);

    riscv::mask_set_sstatus(SStatus::SSTATUS_SIE);
    while(threads[1]->get_state() == TCB::State::NOT_FINISHED
        or threads[2]->get_state() == TCB::State::NOT_FINISHED)
        TCB::yield();

    delete threads[1];
    delete threads[2];



}

#endif //OS1_PROJECT_SEMAPHORE_TEST_HPP
