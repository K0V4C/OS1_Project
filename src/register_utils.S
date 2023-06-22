.global push_registers
.type push_registers, @function
push_registers:
    addi sp, sp, -256

    .irp index 1,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    sd x\index, \index*8(sp)
    .endr

    ret

# I am saving ra also i ope it isn't a mistake

.global pop_registers
.type pop_registers, @function
pop_registers:

    .irp index 1,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
    ld x\index, \index*8(sp)
    .endr

    addi sp, sp, 256
    ret
