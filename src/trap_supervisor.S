.extern InterruptHandler
.global trap_supervisor
.align 4
trap_supervisor:
    j ecall_and_exception
    j third_lv_interrupt
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    j hardware_interrupt

ecall_and_exception:
    # Save ra and leave luft for one more register
    addi sp, sp, -16
    sd ra, 0x00(sp)

    # Save SEPC(incresed by 4) and sstatus
    addi sp, sp, -256
    csrw sscratch, t0
    csrr t0, sepc
    addi t0, t0, 4
    sd   t0, 0x00(sp) # Save sepc of next instruction
    csrr t0, sstatus
    sd   t0, 0x08(sp) # Save sstatus
    csrr t0, sscratch

    # 16(sp), 10*8(sp) unused

    # save regular regs
    .irp index 3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd   x\index, \index*8(sp)
    .endr

    call handle_ecall_and_exception

    # Load special regs
    ld   t0, 0x08(sp)
    csrw sstatus, t0
    ld   t0, 0x00(sp)
    csrw sepc, t0
    # 10 does not exist -> a0
    .irp index 3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld   x\index, \index*8(sp)
    .endr

    addi sp, sp, 256

    ld   ra, 0x00(sp)
    addi sp, sp, 16

    sret

third_lv_interrupt:
    # Save ra and leave luft for one more register
    # NOT WORKING RIGHT NOW
    addi sp, sp, -16
    sd ra, 0x00(sp)

    # Save SEPC(incresed by 4) and sstatus
    addi sp, sp, -256
    csrw sscratch, t0
    csrr t0, sepc
    sd   t0, 0x00(sp) # Save sepc of next instruction
    # csrr t0, sstatus
    # sd   t0, 0x08(sp) # Save sstatus
    # csrr t0, sscratch

    # 16(sp), 10*8(sp) unused

    # save regular regs
    .irp index 3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd   x\index, \index*8(sp)
    .endr

    call handle_third_lv_interrupt

    # Load special regs
    # ld   t0, 0x08(sp)
    # csrw sstatus, t0
    ld   t0, 0x00(sp)
    csrw sepc, t0
    # 10 does not exist -> a0
    .irp index 3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld   x\index, \index*8(sp)
    .endr

    addi sp, sp, 256

    ld   ra, 0x00(sp)
    addi sp, sp, 16

    sret

hardware_interrupt:
    # NOT WORKING RIGHT NOW
    # to be added when i fugure out how these are done
    call handle_hardware_interrupt
    sret


