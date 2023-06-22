.global _ZN3TCB14context_switchEPNS_7ContextES1_
.type _ZN3TCB14context_switchEPNS_7ContextES1_, @function
# don't know other way then namemangle
_ZN3TCB14context_switchEPNS_7ContextES1_:
    #a0 old context
    #a1 new context
    sd sp, 0(a0)

    ld sp, 0(a0)

    ret
