#ifndef _ARCH_X86_GDT_H
#define _ARCH_X86_GDT_H

#include <stdint.h>


/*
 Global descriptor table.

 Each system must have one GDT defined. One or more LDTs (local descriptor table) can optionally
 be defined, for example, for each task. The GDT is a structure in linear address space. The base
 and the limit of the GDT is loaded in the GDTR register. The GDT should be aligned on a 8 byte
 boundary for maximum performance (Intel 64 and IA-32 Architecture Software Manual: Volume 3A
 3.5.1).

 First descriptor is not used by CPU, and can be used to guarantee a GPF when accessing an unused
 segment selector. It will however not generate an exception when the segment is loaded.
 */

/**
 * Maximum number of descriptors in the GDT
 */
#define ARCH_X86_GDT_MAX_DESCRIPTORS 3U

/**
 * Segment is accessed
 */
#define ARCH_X86_GDT_DESC_ACCESS 0x0001

/**
 * Segment is writable
 */
#define ARCH_X86_GDT_DESC_READWRITE 0x0002

/**
 * Segment expands down
 */
#define ARCH_X86_GDT_DESC_EXPANSION 0x0004

/**
 * Segment is executable
 */
#define ARCH_X86_GDT_DESC_EXEC_CODE 0x0008

/**
 * Segment is code or data
 */
#define ARCH_X86_GDT_DESC_CODEDATA 0x0010

/**
 * Segment privilege level 0
 */
#define ARCH_X86_GDT_DESC_DPL0 0x0000

/**
 * Segment privilege level 1
 * @todo Check if bits are correct
 */
#define ARCH_X86_GDT_DESC_DPL1 0x0020

/**
 * Segment privilege level 2
 * @todo Check if bits are correct
 */
#define ARCH_X86_GDT_DESC_DPL2 0x0040

/**
 * Segment privilege level 3
 */
#define ARCH_X86_GDT_DESC_DPL3 0x0060
/**
 * Segment is present in memory
 */
#define ARCH_X86_GDT_DESC_MEMORY 0x0080

/**
 * High 4 bits of limit stored in granularity field.
 */
#define ARCH_X86_GDT_GRAN_LIMITHI 0x0F

/**
 * @TODO What is this?
 */
#define ARCH_X86_GDT_GRAN_OS 0x10

/**
 * Default operation size is 32bit
 */
#define ARCH_X86_GDT_GRAN_32BIT 0x40

/**
 * Granularity is 4kbyte
 */
#define ARCH_X86_GDT_GRAN_4K 0x80

/**
 * Struct matching an entry in the Global Descriptor Table which describes a segment.
 */
typedef struct
{
    /**
     * Low 16 bits of the segment limit
     */
    uint16_t limit;

    /**
     * Low 16 bits of the base address.
     */
    uint16_t baseLo;

    /**
     * Mid 16 bits of the base address.
     */
    uint8_t baseMid;

    /**
     * Segment access and description flags.
     */
    uint8_t flags;

    /**
     * Granularity of the segment.
     */
    uint8_t granularity;

    /**
     * High 8 bits of the base address.
     */
    uint8_t baseHi;
} __attribute__((packed, aligned(8))) arch_x86_gdt_descriptor;

/**
 * @brief Constructs an entry in the GDT.
 * @param i Entry index.
 * @param base Base address of the segment.
 * @param limit Limit of the segment.
 * @param access Access flags for the segment.
 * @param granularity Granularity flags for the segment.
 */
void arch_x86_gdt_set_descriptor(
    int i,
    uint64_t base,
    uint64_t limit,
    uint8_t access,
    uint8_t granularity);

/**
 * @brief Gets a descriptor from the table
 * @param i Index.
 * @return Pointer to descriptor if existing, else NULL.
 */
arch_x86_gdt_descriptor* arch_x86_get_descriptor(int i);

/**
 * @brief Initializes the GDT
 */
void arch_x86_initialize_gdt();

#endif
