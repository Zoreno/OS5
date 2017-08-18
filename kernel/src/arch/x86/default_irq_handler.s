[bits 32]

[global default_irq_handler]
[extern arch_x86_default_irq_handler]
[extern interrupt_done]

default_irq_handler:
        cli                     ; Disable Interrupts
        pushad                  ; Push all registers

        call arch_x86_default_irq_handler

        popad
        sti
        iretd
