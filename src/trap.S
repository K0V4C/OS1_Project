.extern InterruptHandler
.global trap_supervisor
.align 4
trap_supervisor:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd fp, (sp)
    addi fp, sp, 16 # Debugger
    # Save regs
    addi sp, sp, -272 # Has to be aligned to 16 bytes
    csrw sscratch, x10
    csrr x10, sepc 
    sd x10   , 0x00(sp)
    csrr x10, sstatus 
    sd x10, 0x08(sp)
    csrr x10, sscratch
    # x0
    sd x1 , 0x010(sp)   # ra
    sd x2 , 0x018(sp)   # sp
    sd x3 , 0x020(sp)   # gp 
    sd x4 , 0x028(sp)   # tp 
    sd x5 , 0x030(sp)   # t0
    sd x6 , 0x038(sp)   # t1
    sd x7 , 0x040(sp)   # t2
    sd x8 , 0x048(sp)   # s0 or fp
    sd x9 , 0x050(sp)   # s1
    sd x10, 0x058(sp)   # a0
    sd x11, 0x060(sp)   # a1
    sd x12, 0x068(sp)   # a2
    sd x13, 0x070(sp)   # a3
    sd x14, 0x078(sp)   # a4
    sd x15, 0x080(sp)   # a5
    sd x16, 0x088(sp)   # a6
    sd x17, 0x090(sp)   # a7
    sd x18, 0x098(sp)   # s2
    sd x19, 0x0A0(sp)   # s3
    sd x20, 0x0A8(sp)   # s4
    sd x21, 0x0B0(sp)   # s5
    sd x22, 0x0B8(sp)   # s6
    sd x23, 0x0C0(sp)   # s7
    sd x24, 0x0C8(sp)   # s8
    sd x25, 0x0D0(sp)   # s9
    sd x26, 0x0D8(sp)   # s10
    sd x27, 0x0E0(sp)   # s11
    sd x28, 0x0E8(sp)   # t3
    sd x29, 0x0F0(sp)   # t4
    sd x30, 0x0F8(sp)   # t5
    sd x31, 0x0100(sp)  # t6
    

    call handle_supervisor_interrupt
    # Load regs
     # Has to be aligned to 16 bytes
    ld x10, 0x00(sp)
    csrw x10   , sepc
    ld x10, 0x08(sp)
    csrw x10, sstatus
        # x0
    ld x1 , 0x010(sp)   # ra
    ld x2 , 0x018(sp)   # sp
    ld x3 , 0x020(sp)   # gp 
    ld x4 , 0x028(sp)   # tp 
    ld x5 , 0x030(sp)   # t0b
    ld x6 , 0x038(sp)   # t1
    ld x7 , 0x040(sp)   # t2
    ld x8 , 0x048(sp)   # s0 or fp
    ld x9 , 0x050(sp)   # s1
    ld x10, 0x058(sp)   # a0
    ld x11, 0x060(sp)   # a1
    ld x12, 0x068(sp)   # a2
    ld x13, 0x070(sp)   # a3
    ld x14, 0x078(sp)   # a4
    ld x15, 0x080(sp)   # a5
    ld x16, 0x088(sp)   # a6
    ld x17, 0x090(sp)   # a7
    ld x18, 0x098(sp)   # s2
    ld x19, 0x0A0(sp)   # s3
    ld x20, 0x0A8(sp)   # s4
    ld x21, 0x0B0(sp)   # s5
    ld x22, 0x0B8(sp)   # s6
    ld x23, 0x0C0(sp)   # s7
    ld x24, 0x0C8(sp)   # s8
    ld x25, 0x0D0(sp)   # s9
    ld x26, 0x0D8(sp)   # s10
    ld x27, 0x0E0(sp)   # s11
    ld x28, 0x0E8(sp)   # t3
    ld x29, 0x0F0(sp)   # t4
    ld x30, 0x0F8(sp)   # t5
    ld x31, 0x0100(sp)  # t6
    addi sp, sp, 270

    ld ra, 8(sp)
    ld fp, (sp)
    addi sp, sp, 16
    sret

