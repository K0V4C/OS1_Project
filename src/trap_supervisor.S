.extern handle_ecall_and_exception
.extern handle_third_lv_interrupt
.extern handle_hardware_interrupt
.global trap_supervisor
.align 4
trap_supervisor:
    j ecall_and_exception
    j third_lv_interrupt
    nop
    nop
    nop
    nop # make these jump to panic!
    nop
    nop
    nop
    j hardware_interrupt

ecall_and_exception:
    addi sp, sp, -256
    # save regular regs
    .irp index 1,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd   x\index, \index*8(sp)
    .endr

    call handle_ecall_and_exception

    # 10 does not exist -> a0
    .irp index 1,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld   x\index, \index*8(sp)
    .endr
    addi sp, sp, 256

    # inc sepc by 4
    csrw sscratch, t0
    csrr t0, sepc
    addi t0, t0, 4
    csrw sepc, t0
    csrr t0, sstatus

    sret

third_lv_interrupt:
    addi sp, sp, -256
    # save regular regs
    .irp index 1,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd   x\index, \index*8(sp)
    .endr

    call handle_third_lv_interrupt

    # 10 does not exist -> a0
    .irp index 1,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld   x\index, \index*8(sp)
    .endr
    addi sp, sp, 256

    sret

hardware_interrupt:

    addi sp, sp, -256
    # save regular regs
    .irp index 1,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd   x\index, \index*8(sp)
    .endr

    call handle_hardware_interrupt

    # 10 does not exist -> a0
    .irp index 1,3,4,5,6,7,8,9,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld   x\index, \index*8(sp)
    .endr
    addi sp, sp, 256
    sret


