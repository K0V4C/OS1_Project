.extern InterruptHandler
.global trap_supervisor
.align 4
trap_supervisor:

    # Save regs

    addi sp, sp, -16
    sd ra, 0x00(sp)

    call handle_supervisor_interrupt
    
    # Load regs
    ld ra, 0x00(sp)
    addi sp, sp, 16

    sret

