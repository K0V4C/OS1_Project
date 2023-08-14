//
// Created by lazar on 5/15/23.
//

#include "../h/interrupt_handler.hpp"
#include "../h/utility.hpp"
#include "../h/output.hpp"
#include "../h/bit_masks.hpp"
#include "../h/tcb.hpp"
#include "../lib/hw.h"
#include "../h/memory_allocator.hpp"
#include "../h/kernel_sem.hpp"

#define sys_call_code args[0]

typedef TCB* thread_t;
typedef KernelSemaphore* sem_t;

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

inline void sync_dispatch() {
    uint64 volatile sepc = riscv::read_sepc() + 4;
    uint64 volatile sstatus = riscv::read_sstatus();
    TCB::dispatch();
    riscv::write_sstatus(sstatus);
    riscv::write_sepc(sepc);
}

// remember to add a0, a1, a2, a3, a4 to args
extern "C" void handle_ecall_and_exception() {

    // ============================================= SAVE REGS =========================================================
    uint64 args[5];
    asm volatile("mv %[mem],  a0": [mem] "=r" (*args));
    asm volatile("mv %[mem],  a1": [mem] "=r" (*(args+1)));
    asm volatile("mv %[mem],  a2": [mem] "=r" (*(args+2)));
    asm volatile("mv %[mem],  a3": [mem] "=r" (*(args+3)));
    asm volatile("mv %[mem],  a4": [mem] "=r" (*(args+4)));
    // =================================================================================================================

    // print_status(args);

    // ============================================= ERROR CONTROL =====================================================
    uint64 volatile scause = riscv::read_scause();

    if(scause == TRAP_TYPE::illegal_instruction)
        panic("Illegal instruction");

    if (scause == TRAP_TYPE::illegal_read_address)
        panic("Illegal read address");

    if (scause == TRAP_TYPE::illegal_write_address)
        panic("Illegal write address");

    if(scause != TRAP_TYPE::user_ecall_interrupt && scause != TRAP_TYPE::system_ecall_interrupt) {
        kvc::print_str("\n------>This should not happen\n");
        print_status(args);
        panic("Unknown condition");
    }
    // =================================================================================================================

    // ============================================= SYSTEM CALLS ======================================================
    if(sys_call_code == OP_CODES::c_allocate_memory) {
        // memory size args[1]
        uint64 ret = (uint64) MemoryAllocator::allocate_blocks(MemoryAllocator::size_in_blocks(args[1]));
        set_return_value(ret);

    }

    else if(sys_call_code == OP_CODES::c_free_memory) {
        // free pointer args[1]
        uint64 ret = MemoryAllocator::free_blocks((void*)args[1]);
        set_return_value(ret);

    }

    else if(sys_call_code == OP_CODES::c_create_thread) {
        // stack args[1]
        // handle args[2]
        // start routine args[3]
        // args args[4]
        int ret;
        TCB* new_tcb = TCB::create_thread((TCB::Body)args[3], (void*)args[1], (void*)args[4]);
        thread_t* handle = (thread_t*)args[2];
        *handle = new_tcb;

        if(new_tcb == nullptr) {
            ret = -1;
        } else {
            ret = 0;
        }
        set_return_value(ret);
    }

    else if(sys_call_code == OP_CODES::c_thread_exit) {
        // Only op code
        if(TCB::running == nullptr) {
            set_return_value(-1);
        } else {
            TCB::running->set_state(TCB::State::FINISHED);
            // todo may couse errors
            sync_dispatch();
            set_return_value(1);
        }
    }

    else if(sys_call_code == OP_CODES::c_thread_dispatch) {
        // Only op code
        // todo Should it be dispatch here?
        TCB::yield();

    }

    else if(sys_call_code == OP_CODES::c_thread_join) {
        //  handle args[1]
        thread_t handle = (thread_t)args[1];
        handle->add_blocked(TCB::running);
        // Edit to make it work
//            TCB::yield();

    }

    else if(sys_call_code == OP_CODES::c_sem_open) {
        // handle args[1]
        // init args[2]
        int ret;
        sem_t *handle = (sem_t*)args[1];
        uint64 init = (uint64)args[2];
        KernelSemaphore* new_sem = KernelSemaphore::create_semaphore(init);
        *handle = new_sem;

        if(new_sem == nullptr){
            ret = -1;
        } else {
            ret = 0;
        }
        set_return_value(ret);

    }

    else if(sys_call_code == OP_CODES::c_sem_close) {
        // handle args[1]
        int ret;
        sem_t handle = (sem_t)args[1];

        if(handle == nullptr) {
            ret = -1;
        } else {
            KernelSemaphore::release(handle);
            delete handle;
            ret = 0;
        }
        set_return_value(ret);

    }

    else if(sys_call_code == OP_CODES::c_sem_wait) {
        // id args[1]
        int ret;
        sem_t handle = (sem_t)args[1];

        if(handle == nullptr){
            ret = -1;
        } else {
            ret = 0;
            handle->wait();
        }
        set_return_value(ret);

    }

    else if(sys_call_code == OP_CODES::c_sem_signal) {
        // id args[2]
        int ret;
        sem_t handle = (sem_t)args[1];

        if(handle == nullptr){
            ret = -1;
        } else {
            ret = 0;
            handle->signal();
        }
        set_return_value(ret);

    }

    else if(sys_call_code == OP_CODES::c_time_sleep) {

    }

    else if(sys_call_code == OP_CODES::c_putc) {
        // TODO TEMP
        // char args[1]
        __putc((char)args[1]);
    }

    else if(sys_call_code == OP_CODES::c_getc) {
        // TODO TEMP
        char ret = __getc();
        set_return_value(ret);
    }

    else if (sys_call_code == OP_CODES::sync_switch) {
        // todo may couse errors
        sync_dispatch();

    }

    else if (sys_call_code == OP_CODES::mode_switch) {
        //change to user mode
        uint64 volatile sstatus =  riscv::read_sstatus();
        sstatus = sstatus & (~SStatus::SSTATUS_SPP);
        riscv::write_sstatus(sstatus);
    }
    // =================================================================================================================
}

extern "C" void handle_third_lv_interrupt() {
    // timer interrupt

    // sip -> supervisor interrupt pending
    TCB::time_slice_counter++;
    if(TCB::running->time_slice_counter >= TCB::running->get_time_slice()) {
//        kvc::print_str("Timer\n");
        uint64 sepc = riscv::read_sepc();
        uint64  sstatus = riscv::read_sstatus();
        TCB::time_slice_counter = 0;
        TCB::dispatch();
        riscv::write_sstatus(sstatus);
        riscv::write_sepc(sepc);
    }


    riscv::mask_clear_sip(SIP::SIP_SSIP); // Write 0 to signal interrupt finished
}

extern "C" void handle_hardware_interrupt() {
    // do this yourself
    console_handler();

}


