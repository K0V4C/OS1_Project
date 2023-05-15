//
// Created by lazar on 5/15/23.
//

#include "../h/interrupt_handler.hpp"
#include "../h/utility.hpp"

enum TRAP_TYPE {
    SOFTWARE_INTR_3RD_LV = 0x80000001,
    HARDWARE_INTR        = 0x80000009,
    ILLEGAL_INSTRUCTION  = 0x00000002,
    ILLEGAL_READ_ADDR    = 0x00000005,
    ILLEGAL_WRITE_ADDR   = 0x00000007,
    ECALL_USR            = 0x00000008,
    ECALL_SYS            = 0x00000009,

};

extern "C" void handle_supervisor_interrupt() {
    uint64 volatile scause = kvc::read_scause();

    uint64 volatile sepc = kvc::read_sepc();
    sepc += 4;
    kvc::write_sepc(sepc);

    if(scause == SOFTWARE_INTR_3RD_LV || scause == HARDWARE_INTR){
        switch (scause){
            case SOFTWARE_INTR_3RD_LV:
                break;
            case HARDWARE_INTR:
                break;
            default:
                kvc::print_str("\n-------->This should not happen BNT\n");
        }
    }

    switch (scause) {
            case ILLEGAL_INSTRUCTION:
                break;
            case ILLEGAL_READ_ADDR:
                break;
            case ILLEGAL_WRITE_ADDR:
                break;
            case ECALL_USR:
                break;
            case ECALL_SYS:
                break;
            default:
                kvc::print_str("\n------>This should not happen\n");
                // panic!
        }
    }


