#include "../h/utility.hpp"
#include "../h/output.hpp"
#include "../h/syscall_c.h"
#include "../h/syscall_cpp.hpp"

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
    clear all tasks
 */

/* TODO:
    Test sem -1
    Test Periodic thread
    Test join
    clear all tasks
 */
