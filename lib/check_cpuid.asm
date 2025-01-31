; check_cpuid.asm
; Assembly code for the check_cpuid function

IFDEF RAX
.code

; Declare the function for the linker
PUBLIC _check_cpuid
PUBLIC check_cpuid

check_cpuid PROC
_check_cpuid PROC

    ; x64 Windows Calling Convention (Result in RAX)
    pushfq                          ; Push RFLAGS onto the stack
    pop     rax                     ; Pop it into RAX
    mov     rcx, rax                ; Save the original RFLAGS in RCX

    xor     rax, 200000h            ; Flip the ID bit (bit 21)
    push    rax                     ; Push modified RFLAGS onto the stack
    popfq                           ; Write it back to RFLAGS

    pushfq                          ; Push RFLAGS again
    pop     rax                     ; Pop it back into RAX
    and     rax, 200000h            ; Mask out everything but the ID flag
    cmp     rax, 200000h            ; Compare the ID flag
    sete    al                      ; AL = 1 if ID flag was toggled, else 0
    movzx   eax, al                 ; Zero-extend AL into EAX
    ret
ELSE
.686
.XMM
.model flat, C
.code

; Declare the function for the linker
PUBLIC _check_cpuid
PUBLIC check_cpuid

check_cpuid PROC
_check_cpuid PROC
    ; x86 Windows Calling Convention (Result in EAX)
    pushfd                          ; Push EFLAGS onto the stack
    pop     eax                     ; Pop it into EAX
    mov     ecx, eax                ; Save the original EFLAGS in ECX

    xor     eax, 200000h            ; Flip the ID bit (bit 21)
    push    eax                     ; Push modified EFLAGS onto the stack
    popfd                           ; Write it back to EFLAGS

    pushfd                          ; Push EFLAGS again
    pop     eax                     ; Pop it back into EAX
    and     eax, 200000h            ; Mask out everything but the ID flag
    cmp     eax, 200000h            ; Compare the ID flag
    sete    al                      ; AL = 1 if ID flag was toggled, else 0
    movzx   eax, al                 ; Zero-extend AL into EAX
    ret
ENDIF

_check_cpuid ENDP
check_cpuid ENDP

END
