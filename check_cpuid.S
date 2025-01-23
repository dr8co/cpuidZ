    .section .text
    .global check_cpuid

check_cpuid:
#ifdef __x86_64__
    # x86-64: Use RFLAGS
    pushfq                          # Push RFLAGS onto the stack
    popq %rax                       # Pop it into RAX
    movq %rax, %rcx                 # Save the original RFLAGS in RCX

    # Toggle the ID flag (bit 21) in RFLAGS
    xorq $0x200000, %rax            # Flip the ID bit (21)
    pushq %rax                      # Push modified RFLAGS onto the stack
    popfq                           # Pop it back into RFLAGS

    # Check if the ID flag is writable
    pushfq                          # Push RFLAGS again
    popq %rax                       # Pop it back into RAX
    andq $0x200000, %rax            # Mask out everything but the ID flag
    cmpq $0x200000, %rax            # Compare the ID flag to see if it was toggled
    sete %al                        # Set AL = 1 if the flag is writable, else 0
    movzx %al, %eax                 # Zero-extend AL into EAX
    ret                             # Return result in EAX
#else
    # x86: Use EFLAGS
    pushf                           # Push EFLAGS onto the stack
    popl %eax                       # Pop it into EAX
    movl %eax, %ecx                 # Save the original EFLAGS in ECX

    # Toggle the ID flag (bit 21) in EFLAGS
    xorl $0x200000, %eax            # Flip the ID bit (21)
    pushl %eax                      # Push modified EFLAGS onto the stack
    popf                            # Pop it back into the EFLAGS register

    # Check if the ID flag is writable
    pushf                           # Push EFLAGS again
    popl %eax                       # Pop it back into EAX
    andl $0x200000, %eax            # Mask out everything but the ID flag
    cmpl $0x200000, %eax            # Compare the ID flag to see if it was toggled
    sete %al                        # Set AL = 1 if the flag is writable, else 0
    movzbl %al, %eax                # Zero-extend AL into EAX
    ret                             # Return result in EAX
#endif

    # Ensure the stack is not executable
    .section .note.GNU-stack,"",@progbits
