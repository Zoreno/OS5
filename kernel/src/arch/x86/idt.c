#include <arch/x86/idt.h>

#include <string.h>

#define DEBUG_IDT 0

extern void arch_x86_idt_flush(uint32_t idtr_ptr);

typedef struct
{
    uint16_t m_limit;
    uint32_t m_base;
} __attribute__((packed)) arch_x86_idtr;

arch_x86_idt_descriptor _idt[ARCH_X86_IDT_MAX_INTERRUPTS];
arch_x86_idtr _idtr;

void arch_x86_default_irq_handler();

void arch_x86_default_irq_handler()
{
    printf("Unhandled exception\n");
    for(;;);
}

arch_x86_idt_descriptor *arch_x86_get_ir(uint32_t i)
{
    if(i > ARCH_X86_IDT_MAX_INTERRUPTS)
        return NULL;

    return &_idt[i];
}

void arch_x86_install_ir(
    uint32_t i,
    uint16_t flags,
    uint16_t sel,
    IRQ_HANDLER irq_handler)
{
    if(i > ARCH_X86_IDT_MAX_INTERRUPTS)
        return;

    if(!irq_handler)
        return;

    memset(&_idt[i], 0, sizeof(arch_x86_idt_descriptor));

    uint64_t uiBase = (uint64_t)&(*irq_handler);

    _idt[i].baseLo = (uint16_t)(uiBase & 0xFFFF);
    _idt[i].baseHi = (uint16_t)((uiBase >> 16) & 0xFFFF);
    _idt[i].reserved = 0;
    _idt[i].flags = (uint8_t)(flags);
    _idt[i].sel = sel;
}

extern void default_irq_handler(void);

void arch_x86_initialize_idt(uint16_t code_sel)
{
#if DEBUG_IDT

    printf("Initializing IDT...\n");

#endif
    _idtr.m_limit = sizeof(arch_x86_idt_descriptor) * ARCH_X86_IDT_MAX_INTERRUPTS;
    _idtr.m_base = (uint32_t)&_idt[0];

    int num_ints = ARCH_X86_IDT_MAX_INTERRUPTS;

    for(int i = 0; i < num_ints; ++i)
    {
        arch_x86_install_ir(
            i,
            ARCH_X86_IDT_DESC_BIT32 |
            ARCH_X86_IDT_DESC_PRESENT,
            code_sel,
            (IRQ_HANDLER)default_irq_handler);
    }

    arch_x86_idt_flush((uint32_t)&_idtr);

#if DEBUG_IDT

    printf("IDT Initialized!\n");

#endif
}
