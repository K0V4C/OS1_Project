#ifndef INTERRUPT_HANDLER
#define INTERRUPT_HANDLER

// Nemam pojma da li je ovo i potrebno cak

#include "../lib/hw.h"
extern "C" void handle_ecall_and_exception();
extern "C" void handle_third_lv_interrupt();
extern "C" void handle_hardware_interrupt();
#endif // INTERRUPT_HANDLER
