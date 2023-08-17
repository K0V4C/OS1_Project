//
// Created by lazar on 5/16/23.
//

#include "../h/output.hpp"
#include "../h/utility.hpp"

namespace kvc {
    void __assert(const void* a,const void* b) {
        if(a == b)
            return;

        volatile int dummy = 0;
        while(true){
            dummy++;
        }
    }

    void __assert(const uint64  a,const uint64 b) {
        if(a == b)
            return;

        volatile int dummy = 0;
        while(true){
            dummy++;
        }
    }

    void __assert(const int a,const int b) {
        if(a == b)
            return;

        volatile int dummy = 0;
        while(true){
            dummy++;
        }
    }

    void print_int(int val)  {

        if (val < 0) {
            __putc('-');
            val = -val;
        }

        int temp = 0;
        uint64 zeros = 0;
        bool flag = true;
        while (val != 0) {
            if(flag && val%10 == 0) {
                zeros++;
            } else {
                flag = false;
            }
            temp = temp * 10 + (val % 10);
            val /= 10;
        }

        val = temp;

        while (val / 10) {
            __putc('0' + val % 10);
            val = val / 10;
        }

        __putc('0' + val);

        for(; zeros > 0; zeros--)
            __putc('0');

    }

    void print_uint64(uint64 val) {

        uint64 temp = 0;
        bool flag = true;
        uint64 zeros = 0;
        while (val != 0) {
            if(flag && val%10 == 0) {
                zeros++;
            } else {
                flag = false;
            }
            temp = temp * 10 + (val % 10);
            val /= 10;
        }

        val = temp;

        while (val / 10) {
            __putc('0' + val % 10);
            val = val / 10;
        }

        __putc('0' + val);

        for(; zeros > 0; zeros--)
            __putc('0');

    }

    void print_void(const void *ptr)  {

        const char table[] = {
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
        };
        __putc('0');
        __putc('x');

        uint64 bytes = (uint64) ptr;

        for (int i = sizeof(void *) * 2; i > 0; i--) {
            // for shorter version uncomment code under this and remove 2 above for i
            // uint8 high = (bytes & 0xf0000000) >> 28;
            uint8 high = (bytes & 0xf000000000000000) >> 60;
            bytes <<= 4;
            __putc(table[high]);
        }

    }

    void print_str(const char *str) {
        int i = 0;
        while (true) {
            if (str[i] == '\0')
                break;
            __putc(str[i++]);
        }
    }

    void new_line() {
        __putc('\n');
    }


    void panic(const char *msg) {
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

    void print_status(uint64 *arr) {
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
}