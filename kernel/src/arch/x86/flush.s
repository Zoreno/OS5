global arch_x86_gdt_flush
global arch_x86_idt_flush

arch_x86_gdt_flush:
        mov     eax, [esp + 4] ; Get gdtr pointer
        lgdt    [eax]          ; Load GDT
        jmp     0x08:.reload_cs ; Far jump to reload CS
.reload_cs:
        mov     ax, 0x10        ; Reload rest of segment registers
        mov     ds, ax
        mov     es, ax
        mov     fs, ax
        mov     gs, ax
        mov     ss, ax
        ret                     ; Return
        
arch_x86_idt_flush:
        mov     eax, [esp + 4] ; Get idtr pointer
        lidt    [eax]          ; Load IDT
        ret                    ; Return
