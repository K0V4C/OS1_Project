#include "../h/tcb.hpp"
#include "../h/utility.hpp"
#include "../h/output.hpp"
#include "../h/syscall_c.h"
#include "../h/bit_masks.hpp"

typedef TCB* thread_t;

/* TODO:
    MAKE SEM_CLOSE WORK WITH -1
    MAKE PERIODIC THREAD
    REFACTOR
    maybe change how change_privalage works
    what does pop spp spie do?
    join for cpp
 */

auto main() -> int {
    riscv::set_interrupt_routine();
    riscv::thread_setup();
    riscv::enable_interrupts();
    // Create user main thread and change privilege
    change_privilege();
    thread_t user_main;
    thread_create(&user_main, riscv::user_main_wrapper, nullptr);
    // Wait for user main to finish
    thread_join(user_main);
    return 0;
}
