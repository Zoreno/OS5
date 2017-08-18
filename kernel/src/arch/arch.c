#include <arch/arch.h>

#ifdef ARCH_X86
#include <arch/x86/cpu.h>
#include <arch/x86/pic.h>
#include <arch/x86/pit.h>
#endif

void arch_initialize()
{
#ifdef ARCH_X86
    arch_x86_initialize_cpu();
    arch_x86_initialize_pic(0x20, 0x28);
    arch_x86_pit_initialize();
    arch_x86_pit_start_counter(
        100,
        ARCH_X86_PIT_OCW_COUNTER_0,
        ARCH_X86_PIT_OCW_MODE_SQUAREWAVEGEN);

    return;
#endif
}

void arch_shutdown()
{
    arch_x86_shutdown_cpu();
}


uint8_t inportb(uint16_t port)
{
    uint8_t ret;

    asm volatile ( "in %1, %0"
                   : "=a"(ret)
                   : "Nd"(port));

    return ret;

}

uint16_t inportw(uint16_t port)
{
    uint16_t ret;

    asm volatile ( "in %1, %0"
                   : "=a"(ret)
                   : "Nd"(port));

    return ret;
}

uint32_t inportl(uint16_t port)
{
    uint32_t ret;

    asm volatile ( "in %1, %0"
                   : "=a"(ret)
                   : "Nd"(port));

    return ret;
}

void outportb(uint16_t port, uint8_t value)
{
    asm volatile ( "out %0, %1"
                   :
                   : "a"(value), "Nd"(port));
}

void outportw(uint16_t port, uint16_t value)
{
    asm volatile ( "out %0, %1"
            :
                   : "a"(value), "Nd"(port));
}

void outportl(uint16_t port, uint32_t value)
{
    asm volatile ( "out %0, %1"
            :
                   : "a"(value), "Nd"(port));
}


void enable_interrupts()
{
    asm volatile ("sti");
}

void disable_interrupts()
{
    asm volatile ("cli");
}

void interrupt_done(uint32_t intno)
{
    // We have mapped IRQ0-15 to int 0x20-0x2F so we need to subtract to reference the IRQ:s.
    intno -= 0x20;
    
    if(intno > 16)
        return;

    if(intno > 8)
        arch_x86_pic_send_command(PIC_OCW2_MASK_EOI, 1);

    arch_x86_pic_send_command(PIC_OCW2_MASK_EOI, 0);
}

void setvect(int intno, IRQ_HANDLER vect, int flags)
{
    arch_x86_install_ir(
        intno,
        ARCH_X86_IDT_DESC_PRESENT | ARCH_X86_IDT_DESC_BIT32 | flags,
        0x8,
        vect);
}

uint32_t get_tick_count()
{
    return arch_x86_pit_get_tick_count();
}
