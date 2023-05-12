
//
// Created by lazar on 5/12/23.
//

#ifndef UTILITY_H
#define UTILITY_H

#include "../lib/console.h"

namespace kvc {

    auto __assert(const void* a,const void* b) -> void{
        if(a == b)
            return;
        while(true){}
    }

    auto __assert(const uint64  a,const uint64 b) -> void{
        if(a == b)
            return;
        while(true){}
    }

    auto __assert(const int a,const int b) -> void{
        if(a == b)
            return;
        while(true){}
    }

    auto print_int(int val) -> void {

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

    auto print_uint64(uint64 val) -> void {

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

    auto print_void(void *ptr) -> void {

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

    auto print_str(const char *str) -> void {
        int i = 0;
        while (true) {
            if (str[i] == '\0')
                break;
            __putc(str[i++]);
        }
    }

    auto new_line() -> void {
        __putc('\n');
    }

}


#endif // UTILITY_H
