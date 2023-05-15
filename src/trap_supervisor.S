.extern InterruptHandler
.global trap_supervisor
.align 4
trap_supervisor:

    # Prepare stack trace

    addi sp, sp, -16
    sd ra, 0x00(sp)

    # Save special regs

    addi sp, sp, -256
    csrw sscratch, t0
    csrr t0, sepc 
    addi t0, t0, 4
    sd   t0, 0x00(sp) # Save sepc of next instruction
    csrr t0, sstatus
    sd   t0, 0x08(sp) # Save sstatus
    csrr t0, sscratch
    
    # save regular regs
    .irp index 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd   x\index, \index*8(sp)
    .endr

    call handle_supervisor_interrupt

    # Load special regs
    ld   t0, 0x08(sp)
    csrw sstatus, t0
    ld   t0, 0x00(sp)
    csrw sepc, t0

    .irp index 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld   x\index, \index*8(sp)
    .endr

    addi sp, sp, 256

    ld   ra, 0x00(sp)
    addi sp, sp, 16

    sret

