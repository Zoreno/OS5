
/* Define the entry point */
ENTRY(_start)

/* Define Sections */
SECTIONS
{
        /* Start at 1MB */
        . = 0xC0100000;

        .text : AT(ADDR(.text) - 0xC0000000)
        {
                *(.multiboot)
                *(.text)
        }

        .rodata : AT(ADDR(.rodata) - 0xC0000000)
        {
                *(.rodata)
        }

        .data ALIGN(0x1000) : AT(ADDR(.data) - 0xC0000000)
        {
                *(.data)
        }

        .bss : AT(ADDR(.bss) - 0xC0000000)
        {
                *(COMMON)
                *(.bss)
        }

        end = .;
        _end = .;
        __end = .;
}
