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

auto player_one(void* a) -> void {
    for(int i =  0; i < 10; i++) {
        sem1->wait();
        kvc::print_str("Player one \n");
        for (uint64 i = 0; i < 100000; i++)
            for(uint64 j = 0; j < 1000; j++);
//        TCB::yield();
        sem2->signal();
    }
}

auto player_two(void* a) -> void  {
    for(int i = 0; i < 10; i++) {
        sem2->wait();
        kvc::print_str("Player two \n");
        for (uint64 i = 0; i < 100000; i++)
            for(uint64 j = 0; j < 1000; j++);
//        TCB::yield();
        sem1->signal();
    }
}

KernelSemaphore* mutex;
int buffer[5];
int in = 0;
int out = 0;

KernelSemaphore *empty;  // Semaphore to track empty slots in the buffer
KernelSemaphore *full;

KernelSemaphore *bafer;

void f1(void* a)
{
    //wait
    mutex->wait();
    kvc::print_str("\nEntered..\n");
    for(int i=0;i<3909280;i++) {}
    kvc::print_str("\nJust Exiting...\n");
    mutex->signal();
}
void producer(void* a) {
    int item = 1;
    while (1) {
        // Wait for an empty slot in the buffer
        empty->wait();

        // Produce item
        buffer[in] = item;
        kvc::print_str("Produced: ");
        kvc::print_int(item); kvc::new_line();
        if(item>7) break;
        for(uint64 i = 0; i < 1000000; i++);
        item++;
        in = (in + 1) % 5;

        // Signal that a slot in the buffer is now filled
        full->signal();
    }
}

void consumer(void* a) {
    while (1) {
        // Wait for a filled slot in the buffer
        full->wait();

        // Consume item
        int item = buffer[out];
        if(item>=7)break;
        kvc::print_str("Consumed: ");
        for(uint64 i = 0; i < 1000000; i++);
        kvc::print_int(item); kvc::new_line();
        out = (out + 1) % 5;

        // Signal that a slot in the buffer is now empty
        empty->signal();
    }
}
void producer2(void* a) {
    int item = 1;
    while (1) {
        // Wait for available space in the buffer
        bafer->wait();
        // Produce item
        buffer[in] = item;
        kvc::print_str("Produced: ");
        kvc::print_int(item); kvc::new_line();
        if(item > 10)break;
        for(int i=0;i<39090280;i++) {}
        item++;
        in = (in + 1) % 5;
        // Signal that an item has been produced
        bafer->signal();
    }
}

void consumer2(void* a) {
    while (1) {
        // Wait for an item to be available in the buffer
        bafer->wait();
        // Consume item
        int item = buffer[out];
        if(item >= 10) break;
        kvc::print_str("Consumed: ");
        kvc::print_int(item); kvc::new_line();
        for(int i=0;i<39090280;i++) {}
        out = (out + 1) % 5;
        // Signal that an item has been consumed
        bafer->signal();
    }
}



auto sem_run() -> void {

    kvc::print_str("\n-------------- Starting tests for  SEMAPHORES -------------\n");

    TCB* threads[10];
    // Delegating main thread
    threads[0] = TCB::create_thread(nullptr);
    TCB::running = threads[0];

#if 0
    sem1 = KernelSemaphore::create_semaphore(1);
    sem2 = KernelSemaphore::create_semaphore(3);

    threads[1] = TCB::create_thread(&player_one);
    threads[2] = TCB::create_thread(&player_two);

//    riscv::mask_set_sstatus(SStatus::SSTATUS_SIE);
    while(threads[1]->get_state() == TCB::State::NOT_FINISHED
        or threads[2]->get_state() == TCB::State::NOT_FINISHED)
        TCB::yield();

    delete threads[1];
    delete threads[2];

    delete sem1;
    delete sem2;

    kvc::print_str("Test 1 passed \n");
#endif

#if 0
    mutex = KernelSemaphore::create_semaphore(1);
//    threads[0] = TCB::CreateThread(nullptr);
//    TCB::running = threads[0];
    riscv::mask_set_sstatus(SStatus::SSTATUS_SIE);
    threads[1] = TCB::create_thread(f1);
    threads[2] = TCB::create_thread(f1);
    while(threads[1]->get_state() != TCB::State::FINISHED
        or threads[2]->get_state() != TCB::State::FINISHED)
        TCB::yield();
//    delete threads[0];
    delete threads[1];
    delete threads[2];
    delete mutex;

    kvc::print_str("Test 2 passed \n");
#endif

#if 0

    TCB* producerThread, *consumerThread;

    empty = KernelSemaphore::create_semaphore(5);
    full = KernelSemaphore::create_semaphore(0);

//    mainThread = TCB::create_thread(nullptr);
//    TCB::running = mainThread;
    riscv::mask_set_sstatus(SStatus::SSTATUS_SIE);
    producerThread = TCB::create_thread(producer);
    consumerThread = TCB::create_thread(consumer);
    while(producerThread->get_state() != TCB::State::FINISHED
        or consumerThread->get_state() != TCB::State::FINISHED)
        TCB::yield();
//    delete mainThread;
    delete producerThread;
    delete consumerThread;

    delete empty;
    delete full;


    kvc::print_str("Test 3 passed \n");
#endif

#if 0

    TCB* producer_thread, *consumer_thread;

    bafer = KernelSemaphore::create_semaphore(5);

//    mainThread = TCB::CreateThread(nullptr);
//    TCB::running = mainThread;
//    riscv::mask_set_sstatus(SStatus::SSTATUS_SIE);
    producer_thread = TCB::create_thread(producer2);
    consumer_thread = TCB::create_thread(consumer2);
    while(producer_thread->get_state() != TCB::State::FINISHED
        or consumer_thread->get_state() != TCB::State::FINISHED)
        TCB::yield();
//    delete mainThread;
    delete producer_thread;
    delete consumer_thread;

    delete bafer;



    kvc::print_str("Test 4 passed \n");
#endif
    kvc::print_str("\n--------------- SEMAPHORES DONE ----------------\n");

    delete threads[0];




}

#endif //OS1_PROJECT_SEMAPHORE_TEST_HPP
