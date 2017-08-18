#ifndef _ARCH_X86_IDT_H
#define _ARCH_X86_IDT_H

#include <stdint.h>

#define ARCH_X86_IDT_MAX_INTERRUPTS 256U

#define ARCH_X86_IDT_DESC_BIT16 0x06
#define ARCH_X86_IDT_DESC_BIT32 0x0E

#define ARCH_X86_IDT_DESC_RING1 0x40
#define ARCH_X86_IDT_DESC_RING2 0x20
#define ARCH_X86_IDT_DESC_RING3 0x60

#define ARCH_X86_IDT_DESC_PRESENT 0x80

typedef void (*IRQ_HANDLER)(void);

typedef struct
{
    uint16_t baseLo;
    uint16_t sel;
    uint8_t reserved;
    uint8_t flags;
    uint16_t baseHi;
} __attribute__((packed)) arch_x86_idt_descriptor;

arch_x86_idt_descriptor *arch_x86_get_ir(uint32_t i);

void arch_x86_install_ir(
    uint32_t i,
    uint16_t flags,
    uint16_t sel,
    IRQ_HANDLER irq_handler);

void arch_x86_initialize_idt(uint16_t code_sel);

#endif
