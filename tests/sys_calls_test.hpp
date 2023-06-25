//
// Created by lazar on 5/16/23.
//

#ifndef OS1_PROJECT_SYS_CALLS_TEST_H
#define OS1_PROJECT_SYS_CALLS_TEST_H

#include "../h/utility.hpp"
#include "../h/syscall_c.hpp"
#include "../h/output.hpp"

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
    kvc::print_int(d->a);kvc::new_line();
    kvc::print_int(d->b);kvc::new_line();
    kvc::print_int(d->c);kvc::new_line();



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

//    thread_join(worker);
    thread_dispatch();
//    thread_dispatch();
//    thread_dispatch();
//    thread_dispatch();
//    thread_dispatch();
//    thread_dispatch();




    kvc::print_str("\nTest 1 done\n");
    kvc::print_str("\n ---------------- SYS CALLS PASSED ------------------- \n");
}

#endif //OS1_PROJECT_SYS_CALLS_TEST_H
