#include "../h/utility.hpp"

auto main() -> int {
    riscv::setup_interrupt_routine();
    riscv::set_main_and_idle();
    riscv::enable_interrupts();
    // run_user_main has join that waits for user_main to finish
    riscv::run_user_main();
    return 0;
}

/* TODO:
    Test sem close for -1
    MAKE PERIODIC THREAD
    REFACTOR
    maybe change how change_privalage works
    what does pop spp spie do?
    join for cpp
    clear all tasks
    write tests
 */
