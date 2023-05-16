//
// Created by lazar on 5/16/23.
//

#ifndef OS1_PROJECT_SYS_CALLS_TEST_H
#define OS1_PROJECT_SYS_CALLS_TEST_H

#include "../h/utility.hpp"
#include "../h/syscall_c.hpp"

void sys_calls_run(){

    void *mem_1, *mem_2, *mem_3, *mem_4, *mem_5, *mem_6;

    mem_1 = mem_alloc(1024);

    int* arr = (int*)mem_1;
    for(int i = 0; i < 256 ; i++){
        arr[i] = 5;
    }

    mem_free(mem_1);


}

#endif //OS1_PROJECT_SYS_CALLS_TEST_H
