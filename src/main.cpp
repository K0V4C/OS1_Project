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
    REFACTOR
    maybe change how change_privalage works
    what does pop spp spie do?
    add destructors for threads?
 */

/* TODO:
    Test sem -1
    Test Periodic thread
    Test join
    clear all tasks
 */
