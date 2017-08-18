#include <stdint.h>
#include <stdio.h>
#include <kernel/debug_terminal.h>

void kernel_panic(const char *msg)
{
    debug_terminal_setTextColor(VGA_COLOR_WHITE);
    debug_terminal_setBackColor(VGA_COLOR_BLUE);
    debug_terminal_clear();

    printf("KERNEL HAS ENCOUNTED AN ERROR AND HAS BEEN HALTED:\n%s", msg);
}
