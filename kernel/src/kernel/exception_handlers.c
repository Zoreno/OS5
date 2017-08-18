#include <stdint.h>

extern void kernel_panic(const char *str);

void divide_by_zero_handler(void)
{
    kernel_panic("Divide by 0");
    for(;;);
}

void general_protection_fault_handler(void)
{
    kernel_panic("GPF");
    for(;;);
}

void page_fault_handler(void)
{
    kernel_panic("PF");
    for(;;);
}
