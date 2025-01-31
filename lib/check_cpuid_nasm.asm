section .text
global check_cpuid
global _check_cpuid

check_cpuid:
_check_cpuid:
%if __BITS__ = 64
    ; 64-bit
    pushfq                      ; Save RFLAGS
    pop     rax                 ; Load into RAX
    mov     rcx, rax            ; Save original RFLAGS

    xor     rax, 0x200000       ; Flip ID bit (bit 21)
    push    rax
    popfq                       ; Restore modified flags

    pushfq                      ; Read RFLAGS again
    pop     rax
    and     rax, 0x200000       ; Mask out the ID bit
    cmp     rax, 0x200000       ; Check if toggled
    sete    al                  ; AL = 1 if CPUID supported, else 0
    movzx   eax, al             ; Zero-extend AL into EAX (return value)
    ret
%else
    ; 32-bit
    pushfd                      ; Save EFLAGS
    pop     eax                 ; Load into EAX
    mov     ecx, eax            ; Save original EFLAGS

    xor     eax, 0x200000       ; Flip ID bit (bit 21)
    push    eax
    popfd                       ; Restore modified EFLAGS

    pushfd                      ; Read EFLAGS again
    pop     eax
    and     eax, 0x200000       ; Mask out the ID bit
    cmp     eax, 0x200000       ; Check if toggled
    sete    al                  ; AL = 1 if CPUID supported, else 0
    movzx   eax, al             ; Zero-extend AL into EAX (return value)
    ret
%endif
