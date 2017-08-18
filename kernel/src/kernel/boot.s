global _start
extern kernel_main

_begin:
    ;; Setup Multiboot constants
    MBALIGN equ 1<<0        ; Multiboot align flag
    MEMINFO equ 1<<1        ; Memory Info flag

    FLAGS equ MBALIGN | MEMINFO ; Set multiboot flags
    MAGIC equ 0x1BADB002        ; Set multiboot magic number
    CHECKSUM equ -(MAGIC + FLAGS) ; Calculate Checksum

    KERNEL_VIRTUAL_BASE equ 0xC0000000
    KERNEL_PAGE_NUMBER equ (KERNEL_VIRTUAL_BASE >> 22)

    PD_FLAGS equ 0x83

    STACKSIZE equ 0x4000

section .data
    align 0x1000
BootPageDirectory:
    dd 0x00000000 | PD_FLAGS            ; ID map 4MB
    times (KERNEL_PAGE_NUMBER - 1) dd 0 ; Null some pages
    dd 0x00000000 | PD_FLAGS            ; Map kernel to 3GB
    times (1024 - KERNEL_PAGE_NUMBER - 1) dd 0; Null rest

section .multiboot
    align 4
    
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

    
section .text
    

_start:
    mov  ecx, (BootPageDirectory - KERNEL_VIRTUAL_BASE) ; Load physical address of boot page dir
    mov  cr3, ecx

    mov  ecx, cr4
    or   ecx, 0x00000010        ; Set PSE Bit
    mov  cr4, ecx

    mov  ecx, cr0
    or   ecx, 0x80000000        ; Set Paging Bit
    mov  cr0, ecx

    lea  ecx, [_start_high]     ; Load our high half loading code
    jmp  ecx                    ; Jump There
        
_start_high:

    mov dword [BootPageDirectory], 0 ; Unmap the ID-mapped first 4MB
    invlpg [0]                       ; Mark as invalid
        
    mov esp, stack_top ; Set stack pointer
        
    push eax ; Push multiboot magic number 
        
    add  ebx, KERNEL_VIRTUAL_BASE
    push ebx ; Push pointer to multiboot structure
        
    call kernel_main
    cli
    
.hang:    
    hlt
    jmp .hang
    
section .bss

align 16
stack_bottom:
    resb STACKSIZE
stack_top:
.end:
