//
// Created by lazar on 5/15/23.
//

#include "../h/interrupt_handler.hpp"
#include "../h/utility.hpp"
#include "../h/output.hpp"
#include "../h/bit_masks.hpp"
#include "../h/abi.hpp"
#include "../lib/hw.h"

#define sys_call_code args[0]

//inline void get_args(uint64* arr){
//    __asm__ volatile("mv %[mem],  a0": [mem] "=r" (*arr));
//    __asm__ volatile("mv %[mem],  a1": [mem] "=r" (*(arr+1)));
//    __asm__ volatile("mv %[mem],  a2": [mem] "=r" (*(arr+2)));
//    __asm__ volatile("mv %[mem],  a3": [mem] "=r" (*(arr+3)));
//    __asm__ volatile("mv %[mem],  a4": [mem] "=r" (*(arr+4)));
//}

inline void set_return_value(uint64 ret) {
    __asm__ volatile ("mv a0, %[ret]": : [ret] "r"  (ret));
}

void print_status(uint64* arr) {
    kvc::print_str("+----------------------------------------+\n");

    kvc::print_void((void*)arr[0]);kvc::print_str("  <-- OP_CODE\n");
    kvc::print_void((void*)arr[1]);kvc::print_str("  <-- A0\n");
    kvc::print_void((void*)arr[2]);kvc::print_str("  <-- A1\n");
    kvc::print_void((void*)arr[3]);kvc::print_str("  <-- A2\n");
    kvc::print_void((void*)arr[4]);kvc::print_str("  <-- A3\n");

    kvc::print_str("+----------------------------------------+\n");
}

extern "C" void handle_supervisor_interrupt() {
    uint64 args[5];
    __asm__ volatile("mv %[mem],  a0": [mem] "=r" (*args));
    __asm__ volatile("mv %[mem],  a1": [mem] "=r" (*(args+1)));
    __asm__ volatile("mv %[mem],  a2": [mem] "=r" (*(args+2)));
    __asm__ volatile("mv %[mem],  a3": [mem] "=r" (*(args+3)));
    __asm__ volatile("mv %[mem],  a4": [mem] "=r" (*(args+4)));
    print_status(args);

    uint64 volatile scause = kvc::read_scause();
    kvc::print_void((void*)args[4]);kvc::print_str("  <-- SCAUSE\n");

    if(scause == TRAP_TYPE::software_interrupt_3rd_lv || scause == TRAP_TYPE::hardware_interrupt){
        switch (scause){
            case TRAP_TYPE::software_interrupt_3rd_lv:
                break;
            case TRAP_TYPE::hardware_interrupt:
                break;
            default:
                kvc::print_str("\n-------->This should not happen BNT\n");
        }
    }

    switch (scause) {
            case TRAP_TYPE::illegal_instruction:
                break;
            case TRAP_TYPE::illegal_read_address:
                break;
            case TRAP_TYPE::illegal_write_address:
                break;
            case TRAP_TYPE::user_ecall_interrupt:
                if(sys_call_code == OP_CODES::c_allocate_memory) {
                    uint64 ret = (uint64)ABI::mem_alloc(args[1]);
                     set_return_value(ret);
                    break;
                }

                if(sys_call_code == OP_CODES::c_free_memory) {
                    uint64 ret = ABI::mem_free((void*)args[1]);
                    set_return_value(ret);
                    break;
                }

                break;
            case TRAP_TYPE::system_ecall_interrupt:
                if(sys_call_code == OP_CODES::c_allocate_memory) {
                    uint64 ret = (uint64)ABI::mem_alloc(args[1]);
                     set_return_value(ret);
                    break;
                }

                if(sys_call_code == OP_CODES::c_free_memory) {
                    uint64 ret = ABI::mem_free((void*)args[1]);
                    set_return_value(ret);
                    break;
                }
            default:
                kvc::print_str("\n------>This should not happen\n");
                // panic!
    }
}


