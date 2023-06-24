//
// Created by lazar on 5/15/23.
//

#include "../h/interrupt_handler.hpp"
#include "../h/utility.hpp"
#include "../h/output.hpp"
#include "../h/bit_masks.hpp"
#include "../h/abi.hpp"
#include "../lib/hw.h"
#include "../h/tcb.hpp"

#define sys_call_code args[0]

inline void set_return_value(uint64 ret) {
    asm volatile ("mv a0, %[ret]": : [ret] "r"  (ret));
}

void print_status(uint64* arr) {
    kvc::print_str("+----------------------------------------+\n");

    kvc::print_void((void*)arr[0]);kvc::print_str("  <-- OP_CODE\n");
    kvc::print_void((void*)arr[1]);kvc::print_str("  <-- A0\n");
    kvc::print_void((void*)arr[2]);kvc::print_str("  <-- A1\n");
    kvc::print_void((void*)arr[3]);kvc::print_str("  <-- A2\n");
    kvc::print_void((void*)arr[4]);kvc::print_str("  <-- A3\n");

    uint64 volatile scause = riscv::read_scause();
    kvc::print_uint64(scause);kvc::print_str("  <-- SCAUSE\n");

    uint64 volatile sepc = riscv::read_sepc();
    kvc::print_void((void*)sepc);kvc::print_str("  <-- SEPC\n");

    uint64 volatile stval = riscv::read_stval();
    kvc::print_uint64(stval);kvc::print_str("  <-- STVAL\n");

    kvc::print_str("+----------------------------------------+\n");
}

void panic(const char* msg) {
    kvc::print_str(msg);kvc::new_line();
    uint64 volatile scause = riscv::read_scause();
    kvc::print_uint64(scause);kvc::print_str("  <-- SCAUSE\n");

    uint64 volatile sepc = riscv::read_sepc();
    kvc::print_void((void*)sepc);kvc::print_str("  <-- SEPC\n");

    uint64 volatile stval = riscv::read_stval();
    kvc::print_uint64(stval);kvc::print_str("  <-- STVAL\n");
    volatile int stop = 0;
    while(true) {
        stop++;
    }

}

// remember to add a0, a1, a2, a3, a4 to args
extern "C" void handle_ecall_and_exception() {
    uint64 args[5];
    asm volatile("mv %[mem],  a0": [mem] "=r" (*args));
    asm volatile("mv %[mem],  a1": [mem] "=r" (*(args+1)));
    asm volatile("mv %[mem],  a2": [mem] "=r" (*(args+2)));
    asm volatile("mv %[mem],  a3": [mem] "=r" (*(args+3)));
    asm volatile("mv %[mem],  a4": [mem] "=r" (*(args+4)));
//    print_status(args);

    uint64 volatile scause = riscv::read_scause();
    uint64 sepc, sstatus;

    switch (scause) {
            case TRAP_TYPE::illegal_instruction:
                panic("Illegal instruction");
                break;
            case TRAP_TYPE::illegal_read_address:
                panic("Illegal read address");
                break;
            case TRAP_TYPE::illegal_write_address:
                panic("Illegal write address");
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

                sepc = riscv::read_sepc();
                sstatus = riscv::read_sstatus();
                TCB::time_slice_counter = 0;
                TCB::dispatch();
                riscv::write_sstatus(sstatus);
                riscv::write_sepc(sepc);

                break;
            default:
                kvc::print_str("\n------>This should not happen\n");
                print_status(args);

                panic("Unknown condition");
                // panic!
    }
}

extern "C" void handle_third_lv_interrupt() {
    // timer interrupt

    // sip -> supervisor interrupt pending
//    kvc::print_str("AAAAAA");
    TCB::time_slice_counter++;
    if(TCB::running->time_slice_counter >= TCB::running->get_time_slice()) {
//        kvc::print_str("EEEEEEE");
        uint64 sepc = riscv::read_sepc();
        uint64  sstatus = riscv::read_sstatus();
        TCB::time_slice_counter = 0;
        TCB::dispatch();
        riscv::write_sstatus(sstatus);
        riscv::write_sepc(sepc);
    }


    riscv::mask_clear_sip(SIP::SIP_SSIP); // Write 0 to signal interrupt finished


//    kvc::print_str("handle_third_lv_interrupt\n");
}

extern "C" void handle_hardware_interrupt() {
    // do this yourself
    console_handler();
//    kvc::print_str("handle hardware interrupt\n");
}


