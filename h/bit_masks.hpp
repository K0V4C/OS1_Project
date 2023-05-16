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


enum SStatus{
    SSTATUS_SPIE= 0x020,
    SSTATUS_SPP = 0x100,
    SSTATUS_SIE = 0x001,

};

enum TRAP_TYPE {
    software_interrupt_3rd_lv = 0x80000001,
    hardware_interrupt        = 0x80000009,
    illegal_instruction       = 0x00000002,
    illegal_read_address      = 0x00000005,
    illegal_write_address     = 0x00000007,
    user_ecall_interrupt      = 0x00000008,
    system_ecall_interrupt    = 0x00000009,

};

#endif // BIT_MASKS