#ifndef BIT_MASKS
#define BIT_MASKS

enum OP_CODES{
    c_allocate_memory = 0x01,
    c_free_memory     = 0x02,
    c_create_thread   = 0x11,
    c_thread_exit     = 0x12,
    c_thread_dispatch = 0x13,
    c_thread_join     = 0x14,
    c_sem_open        = 0x21,
    c_sem_close       = 0x22,
    c_sem_wait        = 0x23,
    c_sem_signal      = 0x24,
    c_time_sleep      = 0x31,
    c_getc            = 0x41,
    c_putc            = 0x42
};

enum SIP {
    SIP_SSIP = (1 << 1),
    SIP_STIP = (1 << 5),
    SIP_SEIP = (1 << 9),
};

enum SStatus{
    SSTATUS_SIE = (1 << 1), // Enable / disable interrupts
    SSTATUS_SPIE= (1 << 5), // Last SIE
    SSTATUS_SPP = (1 << 8), // Mode user kernel

};

enum TRAP_TYPE {
    software_interrupt_3rd_lv = 0x8000000000000001,
    hardware_interrupt        = 0x8000000000000009,
    illegal_instruction       = 0x0000000000000002,
    illegal_read_address      = 0x0000000000000005,
    illegal_write_address     = 0x0000000000000007,
    user_ecall_interrupt      = 0x0000000000000008,
    system_ecall_interrupt    = 0x0000000000000009,

};

#endif // BIT_MASKS