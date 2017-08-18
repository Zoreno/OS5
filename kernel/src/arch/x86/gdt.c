#include <arch/x86/gdt.h>

#include <string.h>

extern void arch_x86_gdt_flush(uint32_t gdt_ptr);

#define DEBUG_GDT 0

// The layout of the x86 register GDTR
typedef struct
{
    // Limit (size) of the table
    uint16_t m_limit;

    // Base address of the table
    uint32_t m_base;
} __attribute__((packed)) arch_x86_gdtr;

// Our GDT
arch_x86_gdt_descriptor _gdt[ARCH_X86_GDT_MAX_DESCRIPTORS];

// Where to store GDTR content
arch_x86_gdtr _gdtr;

void arch_x86_gdt_set_descriptor(
    int i,
    uint64_t base,
    uint64_t limit,
    uint8_t access,
    uint8_t granularity)
{
    // Sanity Check
    if(i > ARCH_X86_GDT_MAX_DESCRIPTORS)
    {
        return;
    }

    // Null out descriptor
    memset((void*)&_gdt[i], 0, sizeof(arch_x86_gdt_descriptor));

    // Store base address
    _gdt[i].baseLo = (uint16_t)(base & 0xFFFF);
    _gdt[i].baseMid = (uint8_t)((base >> 16) & 0xFF);
    _gdt[i].baseHi = (uint8_t)((base >> 24) & 0xFF);

    // Store limit
    _gdt[i].limit = (uint16_t)(limit & 0xFFFF);

    // Store flags
    _gdt[i].flags = access;

    // Store granularity
    _gdt[i].granularity = (uint8_t)((limit >> 16) & 0x0F);
    _gdt[i].granularity |= granularity & 0xF0;

#if DEBUG_GDT

    printf("Setting GDT entry: %i\n", i);

#endif
}

arch_x86_gdt_descriptor* arch_x86_get_descriptor(int i)
{
    if(i > ARCH_X86_GDT_MAX_DESCRIPTORS)
    {
#if DEBUG_GDT

        printf("Invalid GDT index accessed: %i\n", i);

#endif

        return NULL;
    }

    return &_gdt[i];
}

void arch_x86_initialize_gdt()
{

#if DEBUG_GDT

    printf("Initializing GDT...\n");

#endif

    // Construct GDTR
    _gdtr.m_limit = (uint16_t)(sizeof(arch_x86_gdt_descriptor) * ARCH_X86_GDT_MAX_DESCRIPTORS - 1);
    _gdtr.m_base = (uint32_t)(&_gdt[0]);

    // Set null descriptor

    arch_x86_gdt_set_descriptor(0, 0, 0, 0, 0);

    // Set default code segment
    arch_x86_gdt_set_descriptor(
        1,
        0,
        0xFFFFFFFF,
        ARCH_X86_GDT_DESC_READWRITE |
        ARCH_X86_GDT_DESC_EXEC_CODE |
        ARCH_X86_GDT_DESC_CODEDATA |
        ARCH_X86_GDT_DESC_DPL0 |
        ARCH_X86_GDT_DESC_MEMORY,

        ARCH_X86_GDT_GRAN_4K |
        ARCH_X86_GDT_GRAN_32BIT |
        ARCH_X86_GDT_GRAN_LIMITHI);

    // Set default code segment
    arch_x86_gdt_set_descriptor(
        2,
        0,
        0xFFFFFFFF,
        ARCH_X86_GDT_DESC_READWRITE |
        ARCH_X86_GDT_DESC_CODEDATA |
        ARCH_X86_GDT_DESC_DPL0 |
        ARCH_X86_GDT_DESC_MEMORY,

        ARCH_X86_GDT_GRAN_4K |
        ARCH_X86_GDT_GRAN_32BIT |
        ARCH_X86_GDT_GRAN_LIMITHI);

    // Load our gdt into the CPU register
    arch_x86_gdt_flush((uint32_t)(&_gdtr));

#if DEBUG_GDT

    printf("GDT initialized!\n");

    // TODO: Should check if GDT got loaded at the correct place with correct values

#endif

}
