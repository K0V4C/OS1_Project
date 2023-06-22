.global _ZN3TCB14context_switchEPNS_7ContextES1_
.type _ZN3TCB14context_switchEPNS_7ContextES1_, @function
# don't know other way then namemangle
_ZN3TCB14context_switchEPNS_7ContextES1_:
    #a0 old context
    #a1 new context
    sd ra, 0 * 8(a0)
    sd sp, 1 * 1(a0)

    ld ra, 0 * 8(a1)
    ld sp, 1 * 8(a1)
    ret
