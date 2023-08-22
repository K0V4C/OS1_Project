#include "../h/utility.hpp"

auto main() -> int {
    riscv::setup_interrupt_routine();
    riscv::set_main_and_idle();
    riscv::enable_interrupts();
    // run_user_main has join that waits for user_main to finish
    riscv::run_user_main();
    return 0;
}

/*
    Helped in development:

    A memory allocator class, which was influenced by the second question from the April 2014 curriculum.
    A semaphore class, taking cues from the content found on page 273 of "Osnovi Operativnih sistema."
    The Console class, which was influenced by the first question of the second curriculum from June 2018.
    The TCB class and context switch mechanism were made with help from instructional videos.
 */
