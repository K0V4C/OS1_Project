//
// Created by lazar on 5/16/23.
//

#ifndef OS1_PROJECT_SYS_CALLS_TEST_H
#define OS1_PROJECT_SYS_CALLS_TEST_H

#include "../h/utility.hpp"
#include "../h/syscall_c.h"
#include "../h/output.hpp"
#include "../h/bit_masks.hpp"

struct Data {
    int a;
    int b;
    int c;
};

int fib(int n) {
    if(n <= 1) return n;
    return fib(n-1) + fib(n-2);
}

void worker_thread(void* arg) {
    kvc::print_str("Printing args\n\n");
    Data* d = (Data*)arg;

//    thread_exit();
    kvc::print_int(fib(25));
    kvc::print_int(d->a);kvc::new_line();
    kvc::print_int(d->b);kvc::new_line();
    kvc::print_int(d->c);kvc::new_line();
}

void A(void* arg) {
    kvc::print_str("A\n");
    kvc::print_int(fib(25));
}

void B(void* arg) {
    kvc::print_str("B\n");
    thread_join((thread_t)arg);
    kvc::print_int(fib(20));
}

void C(void* arg) {
    kvc::print_str("C\n");
    thread_join((thread_t)arg);
    kvc::print_int(fib(15));
}


void sys_calls_run1(){

    kvc::print_str("\n ---------------- SYS CALLS TEST ------------------- \n");
    kvc::print_str("\nTest 1 start\n");

    thread_t worker;

    Data* args = (Data*) mem_alloc(sizeof (Data));
    args->a = 5;
    args->b = 22;
    args->c = 100;

    int val = thread_create(&worker, &worker_thread, (void*)args );
    riscv::mask_set_sstatus(SStatus::SSTATUS_SIE);
    thread_join(worker);
//    thread_dispatch();

    kvc::print_str("\nTest 1 done\n");
}



void sys_calls_run2() {
    kvc::print_str("\nTest 2 start\n");

    thread_t a, b, c;

    int aa = thread_create(&a, &A, nullptr);
    int bb = thread_create(&b, &B, a);
    int cc = thread_create(&c, &C, b);
//    riscv::mask_set_sstatus(SStatus::SSTATUS_SIE);
    thread_join(c);

    kvc::print_str("\nTest 2 done\n");
}

void sys_calls_run3() {
    kvc::print_str("\nTest 3 start\n");


    kvc::print_str("\nTest 3 done\n");
}

#endif //OS1_PROJECT_SYS_CALLS_TEST_H
