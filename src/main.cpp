#include "../tests/memory_allocator_test.hpp"
#include "../tests/sys_calls_test.hpp"
#include "../h/tcb.hpp"

extern "C" void trap_supervisor();

inline void set_stvec(){
   riscv::write_stvec((uint64)((char*)&trap_supervisor + 1));
}

void wa() {
    kvc::print_str("aaa");
    kvc::new_line();
    TCB::yield();

}

void wb() {
    kvc::print_str("bbb");
    kvc::new_line();

    TCB::yield();
}

auto main() -> int {

    kvc::print_str("Poceo\n");

    set_stvec();

    // Uncomment to test timers
    // riscv::write_sstatus(0x02);

//    memory_allocator_run();
//    sys_calls_run();

    TCB* threads[3];

    threads[0] = TCB::create_thread(nullptr);
    TCB::running = threads[0];

    threads[1] = TCB::create_thread(&wa);
    threads[2] = TCB::create_thread(&wb);

    TCB::yield();



    kvc::print_str("Uspeo\n");




    return 0;
}
