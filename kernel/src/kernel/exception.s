[bits 32]

[global interrupt_done]

[extern kernel_panic]
[extern interrupt_done]

[global divide_by_zero_irq]
[extern divide_by_zero_handler]

    ;; TODO: Rest of handlers
        
divide_by_zero_irq:
        cli
        pushad
        cld

        call divide_by_zero_handler

        popad
        sti
        iret
        
[global general_protection_fault_irq]
[extern general_protection_fault_handler]

general_protection_fault_irq:
        cli
        pushad
        cld

        call general_protection_fault_handler

        popad
        sti
        iret 

[global page_fault_irq]
[extern page_fault_handler]

page_fault_irq:
        cli
        pushad
        cld

        call page_fault_handler

        popad
        sti
        iret
