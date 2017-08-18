[bits 32]

[global pit_irq_handler]
[extern pit_irq]
[extern interrupt_done]
        
pit_irq_handler:
        pushad
        cli
        cld
                
        call pit_irq
        
        push 0x20
        call interrupt_done
        add  esp, 4

        popad
        sti
        iretd
