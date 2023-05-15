//
// Created by lazar on 5/15/23.
//

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

    void print_void(void *ptr)  {

        const char table[] = {
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
        };
        __putc('0');
        __putc('x');

        uint64 bytes = (uint64) ptr;

        for (int i = sizeof(void *); i > 0; i--) {
            uint8 high = (bytes & 0xf0000000) >> 28;
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

    void ms_sstatus(uint64 mask){
        __asm__ volatile(
                "csrs sstatus, %[mask]"
                :
                : [mask] "r" (mask)
        );
    }
    // mask clear?
    uint64 read_sstatus(){
        uint64 volatile val;
        __asm__ (
                "csrr %[val], sstatus"
                : [val] "=r" (val)
        );
        return val;
    }
    void write_sstatus(uint64 val){
        __asm__ volatile(
                "csrw sstatus, %[val]"
                :
                : [val] "r" (val)
        );

    }

    uint64 read_scause(){
        uint64 volatile val;
        __asm__ (
                "csrr %[val], scause"
                : [val] "=r" (val)
        );
        return val;
    }
    void write_scause(uint64 val){
        __asm__ volatile(
                "csrw scause, %[val]"
                :
                : [val] "r" (val)
        );

    }

    uint64 read_sepc(){
        uint64 volatile val;
        __asm__ (
                "csrr %[val], sepc"
                : [val] "=r" (val)
        );
        return val;
    }
    void write_sepc(uint64 val){
        __asm__ volatile(
                "csrw sepc, %[val]"
                :
                : [val] "r" (val)
        );

    }

    uint64 read_stvec(){
        uint64 volatile val;
        __asm__ (
                "csrr %[val], stvec"
                : [val] "=r" (val)
        );
        return val;
    }
    void write_stvec(uint64 val){
        __asm__ volatile(
                "csrw stvec, %[val]"
                :
                : [val] "r" (val)
        );

    }

    uint64 read_stval(){
        uint64 volatile val;
        __asm__ (
                "csrr %[val], stval"
                : [val] "=r" (val)
        );
        return val;
    }
    void write_stval(uint64 val){
        __asm__ volatile(
                "csrw stval, %[val]"
                :
                : [val] "r" (val)
        );

    }

}