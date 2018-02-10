#include <stdint.h>

extern void kernel_panic(const char *str);

void divide_by_zero_handler(void)
{
    kernel_panic("Divide by 0");
    for(;;);
}

void debug_handler(void)
{
    kernel_panic("Debug exception");
    for(;;);
}

void non_maskable_interrupt_handler(void)
{
    kernel_panic("Non-maskable interrupt");
    for(;;);
}

void breakpoint_handler(void)
{
    kernel_panic("Breakpoint");
    for(;;);
}

void overflow_handler(void)
{
    kernel_panic("Overflow exception");
    for(;;);
}

void bound_range_handler(void)
{
    kernel_panic("Bound range exception");
    for(;;);
}

void invalid_opcode_handler(void)
{
    kernel_panic("Invalid Opcode exception");
    for(;;);
}

void device_not_available_handler(void)
{
    kernel_panic("Device not available exception");
    for(;;);
}

void double_fault_handler(void)
{
    kernel_panic("Double fault exception");
    for(;;);
}

void invalid_tss_handler(void)
{
    kernel_panic("Debug exception");
    for(;;);
}

void seg_not_present_handler(void)
{
    kernel_panic("Segment not present exception");
    for(;;);
}

void stack_seg_fault_handler(void)
{
    kernel_panic("Stack segment fault exception");
    for(;;);
}

void general_protection_fault_handler(void)
{
    kernel_panic("General Protection Fault");
    for(;;);
}

void page_fault_handler(void)
{
    kernel_panic("Page Fault");
    for(;;);
}

void FPU_exception_handler(void)
{
    kernel_panic("FPU exception");
    for(;;);
}

void alignment_check_handler(void)
{
    kernel_panic("Alignment check exception");
    for(;;);
}

void machine_check_handler(void)
{
    kernel_panic("Machine check exception");
    for(;;);
}

void SIMD_floating_point_handler(void)
{
    kernel_panic("SIMD floating point exception");
    for(;;);
}

void virtualization_handler(void)
{
    kernel_panic("Virtualization exception");
    for(;;);
}

void security_handler(void)
{
    kernel_panic("Security exception");
    for(;;);
}
