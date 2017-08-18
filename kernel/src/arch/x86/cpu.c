/**
 * @file    cpu.c
 * @author  Joakim Bertils
 * @date    2017-07-24
 * @brief   CPU Initailization and identification
 */

#include <arch/x86/cpu.h>
#include <arch/x86/gdt.h>
#include <arch/x86/idt.h>

#include <string.h>
#include <stdio.h>

/**
 * If debug messages should be printed to stdout
 */
#define DEBUG_CPUID 1

//==============================================================================
// CPUID Types and Structs
//==============================================================================

/**
 * Layout of all registers in memory for the CPUID instruction
 */
typedef struct
{
    union
    {
        struct
        {
            union
            {
                uint32_t reg;
                char bytes[4];
            } eax;

            union
            {
                uint32_t reg;
                char bytes[4];
            } ebx;

            union
            {
                uint32_t reg;
                char bytes[4];
            } ecx;

            union
            {
                uint32_t reg;
                char bytes[4];
            } edx;
        };

        char all_bytes[16];
    };

} __attribute__((packed)) arch_x86_cpuid_regs_t;

//==============================================================================
// Standard CPUID requests
//==============================================================================

/**
 * Get the cpu vendor string.
 */
#define CPUID_GET_VENDOR_STRING 0

/**
 * Get cpu feature flags
 */
#define CPUID_GET_FEATURES 1

/**
 * Get TLB and cache info
 */
#define CPUID_GET_TLB 2

/**
 * Get serial number
 */
#define CPUID_GET_SERIAL 3

/**
 * Get cache properties
 */
#define CPUID_GET_CACHE 4

// Extended CPUID requests

/**
 * Get extended cpu info
 */
#define CPUID_INTEL_EXTENDED 0x80000000

/**
 * Get intel extended features
 */
#define CPUID_INTEL_FEATURES 0x80000001

/**
 * Get first 16 bytes of brand string
 */
#define CPUID_INTEL_BRAND_STRING_0 0x80000002

/**
 * Get second 16 bytes of brand string
 */
#define CPUID_INTEL_BRAND_STRING_1 0x80000003

/**
 * Get last 16 bytes of brand string
 */
#define CPUID_INTEL_BRAND_STRING_2 0x80000004

//==============================================================================
// Vendor strings
//==============================================================================

/**
 * Old AMD vendor string
 */
#define CPUID_VENDOR_OLDAMD       "AMDisbetter!"

/**
 * AMD vendor string
 */
#define CPUID_VENDOR_AMD          "AuthenticAMD"

/**
 * Intel vendor string
 */
#define CPUID_VENDOR_INTEL        "GenuineIntel"

/**
 * VIA vendor string
 */
#define CPUID_VENDOR_VIA          "CentaurHauls"

/**
 * Old Transmeta vendor string
 */
#define CPUID_VENDOR_OLDTRANSMETA "TransmetaCPU"

/**
 * Transmeta vendor string
 */
#define CPUID_VENDOR_TRANSMETA    "GenuineTMx86"

/**
 * Cyrix vendor string
 */
#define CPUID_VENDOR_CYRIX        "CyrixInstead"

/**
 * Centaur vendor string
 */
#define CPUID_VENDOR_CENTAUR      "CentaurHauls"

/**
 * NexGen vendor string
 */
#define CPUID_VENDOR_NEXGEN       "NexGenDriven"

/**
 * UMC vendor string
 */
#define CPUID_VENDOR_UMC          "UMC UMC UMC "

/**
 * SIS vendor string
 */
#define CPUID_VENDOR_SIS          "SiS SiS SiS "

/**
 * NSC vendor string
 */
#define CPUID_VENDOR_NSC          "Geode by NSC"

/**
 * Rise vendor string
 */
#define CPUID_VENDOR_RISE         "RiseRiseRise"

/**
 * Vortex vendor string
 */
#define CPUID_VENDOR_VORTEX       "Vortex86 SoC"

/**
 * VIA vendor string
 */
#define CPUID_VENDOR_VIA          "VIA VIA VIA "

//==============================================================================
// Vendor string (virtual machines)
//==============================================================================

/**
 * VMware vendor string
 */
#define CPUID_VENDOR_VMWARE       "VMwareVMware"

/**
 * XenHVM vendor string
 */
#define CPUID_VENDOR_XENHVM       "XenVMMXenVMM"

/**
 * Microsoft HV vendor string
 */
#define CPUID_VENDOR_MICROSOFT_HV "Microsoft Hv"

/**
 * Parallels vendor string
 */
#define CPUID_VENDOR_PARALLELS    " lrpepyh vr"

/**
 * CPU Version info returned from CPUID EAX=1
 */
typedef struct
{
    /**
     * CPU Stepping ID
     */
    uint32_t steppingID : 4;

    /**
     * Model
     */
    uint32_t model : 4;

    /**
     * Family ID
     */
    uint32_t familyID : 4;

    /**
     * Processor Type
     */
    uint32_t processorType : 2;

    /**
     * Reserved
     */
    uint32_t res1 : 2;

    /**
     * Extended Model ID
     */
    uint32_t extModelID : 4;

    /**
     * Extended Family ID
     */
    uint32_t extFamilyID : 8;

    /**
     * Reserved
     */
    uint32_t res2 : 4;
} __attribute__((packed)) cpu_version_info;

/**
 * Primary Processor
 */
#define PROCESSOR_TYPE_PRIMARY 0b00

/**
 * Overdrive Processor
 */
#define PROCESSOR_TYPE_OVERDRIVE 0b01

/**
 * Secondary Processor
 */
#define PROCESSOR_TYPE_SECONDARY 0b10

/**
 * CPU Feature Flags returned in ECX and EDX.
 */
enum cpu_features
{
    CPUID_FEAT_ECX_SSE3         = 1 << 0,
    CPUID_FEAT_ECX_PCLMUL       = 1 << 1,
    CPUID_FEAT_ECX_DTES64       = 1 << 2,
    CPUID_FEAT_ECX_MONITOR      = 1 << 3,
    CPUID_FEAT_ECX_DS_CPL       = 1 << 4,
    CPUID_FEAT_ECX_VMX          = 1 << 5,
    CPUID_FEAT_ECX_SMX          = 1 << 6,
    CPUID_FEAT_ECX_EST          = 1 << 7,
    CPUID_FEAT_ECX_TM2          = 1 << 8,
    CPUID_FEAT_ECX_SSSE3        = 1 << 9,
    CPUID_FEAT_ECX_CID          = 1 << 10,
    CPUID_FEAT_ECX_FMA          = 1 << 12,
    CPUID_FEAT_ECX_CX16         = 1 << 13,
    CPUID_FEAT_ECX_ETPRD        = 1 << 14,
    CPUID_FEAT_ECX_PDCM         = 1 << 15,
    CPUID_FEAT_ECX_PCIDE        = 1 << 17,
    CPUID_FEAT_ECX_DCA          = 1 << 18,
    CPUID_FEAT_ECX_SSE4_1       = 1 << 19,
    CPUID_FEAT_ECX_SSE4_2       = 1 << 20,
    CPUID_FEAT_ECX_x2APIC       = 1 << 21,
    CPUID_FEAT_ECX_MOVBE        = 1 << 22,
    CPUID_FEAT_ECX_POPCNT       = 1 << 23,
    CPUID_FEAT_ECX_AES          = 1 << 25,
    CPUID_FEAT_ECX_XSAVE        = 1 << 26,
    CPUID_FEAT_ECX_OSXSAVE      = 1 << 27,
    CPUID_FEAT_ECX_AVX          = 1 << 28,
    CPUID_FEAT_ECX_F16C         = 1 << 29,
    CPUID_FEAT_ECX_RDRAND       = 1 << 30,

    CPUID_FEAT_EDX_FPU          = 1 << 0,
    CPUID_FEAT_EDX_VME          = 1 << 1,
    CPUID_FEAT_EDX_DE           = 1 << 2,
    CPUID_FEAT_EDX_PSE          = 1 << 3,
    CPUID_FEAT_EDX_TSC          = 1 << 4,
    CPUID_FEAT_EDX_MSR          = 1 << 5,
    CPUID_FEAT_EDX_PAE          = 1 << 6,
    CPUID_FEAT_EDX_MCE          = 1 << 7,
    CPUID_FEAT_EDX_CX8          = 1 << 8,
    CPUID_FEAT_EDX_APIC         = 1 << 9,
    CPUID_FEAT_EDX_SEP          = 1 << 11,
    CPUID_FEAT_EDX_MTRR         = 1 << 12,
    CPUID_FEAT_EDX_PGE          = 1 << 13,
    CPUID_FEAT_EDX_MCA          = 1 << 14,
    CPUID_FEAT_EDX_CMOV         = 1 << 15,
    CPUID_FEAT_EDX_PAT          = 1 << 16,
    CPUID_FEAT_EDX_PSE36        = 1 << 17,
    CPUID_FEAT_EDX_PSN          = 1 << 18,
    CPUID_FEAT_EDX_CLF          = 1 << 19,
    CPUID_FEAT_EDX_DTES         = 1 << 21,
    CPUID_FEAT_EDX_ACPI         = 1 << 22,
    CPUID_FEAT_EDX_MMX          = 1 << 23,
    CPUID_FEAT_EDX_FXSR         = 1 << 24,
    CPUID_FEAT_EDX_SSE          = 1 << 25,
    CPUID_FEAT_EDX_SSE2         = 1 << 26,
    CPUID_FEAT_EDX_SS           = 1 << 27,
    CPUID_FEAT_EDX_HTT          = 1 << 28,
    CPUID_FEAT_EDX_TM1          = 1 << 29,
    CPUID_FEAT_EDX_IA64         = 1 << 30,
    CPUID_FEAT_EDX_PBE          = 1 << 31
};

/**
 * Maximum number of cache descriptors
 */
#define CACHE_MAX_DESCRIPTORS 15

/**
 * General cache
 */
#define CACHE_TYPE_GENERAL 0

/**
 * Translation lookaside buffer
 */
#define CACHE_TYPE_TLB 1

/**
 * Cache
 */
#define CACHE_TYPE_CACHE 2

/**
 * Data TLB
 */
#define CACHE_TYPE_DTLB 3

/**
 * Shared TLB
 */
#define CACHE_TYPE_STLB 4

/**
 * Prefetch
 */
#define CACHE_TYPE_PREFETCH 5

/**
 * General cache
 */
#define CACHE_TARGET_GENERAL 0

/**
 * Data cache
 */
#define CACHE_TARGET_DATA 1

/**
 * Instruction cache
 */
#define CACHE_TARGET_INSTRUCTION 2

/**
 * Struct describing an entry in the cache descriptor array
 */
typedef struct
{
    // General Data

    /**
     * Cache type
     */
    uint32_t type;

    /**
     * Cache target
     */
    uint32_t target;

    /**
     * Associativity
     */
    uint32_t associativity;

    // Only for TLB

    /**
     * Number of TLB entries
     */
    uint32_t entries;

    /**
     * TLB page size.
     */
    uint32_t page_size; // In kbytes

    // Only for cache

    /**
     * Cache level
     */
    uint32_t level;

    /**
     * Cache size
     */
    uint32_t size; // In kbytes

    /**
     * Cahce line size
     */
    uint32_t line_size; // In bytes

    // Only for prefetch

    /**
     * Prefetch size
     */
    uint32_t prefetch_size; // In bytes
    
} tlb_cache_info;

/**
 * Struct containing cpu identification info gathered from CPUID instruction
 */
typedef struct
{
    /**
     * Non-zero indicates that this structure is initialized
     */
    int valid;

    /**
     * Maximum value supported by CPUID
     */
    uint32_t max_cpuid;

    /**
     * Maximum extended value supported by CPUID
     */
    uint32_t max_cpuid_extended;

    /**
     * CPU Vendor String
     */
    char vendor[13];

    /**
     * CPU Brand String
     */
    char brand[48];

    /**
     * CPU Version information
     */
    cpu_version_info version_info;

    /**
     * Brand ID
     */
    uint8_t brandID;

    /**
     * Size of cache line flushed by CLFLUSH instruction
     */
    uint8_t CLFLUSH;

    /**
     * Logical CPU times
     */
    uint8_t logicalCPUCount;

    /**
     * APIC ID
     */
    uint8_t APICID;

    /**
     * First set of processor features
     */
    uint32_t ecx_features;

    /**
     * Second set of processor features
     */
    uint32_t edx_features;

    /**
     * Table of cache descriptors
     */
    tlb_cache_info cache_table[CACHE_MAX_DESCRIPTORS];

    /**
     * Number of valid entries in cache descriptor table
     */
    uint32_t cache_table_entries;

} arch_x86_cpu_ident;

//==============================================================================
// CPUID Private functions forward declarations
//==============================================================================

/**
 * @brief Classifies a cache code
 * @param info Pointer to memory where result is stored.
 * @param descriptor Descriptor code
 * @return Non-zero if code was valid.
 */
static int classify_cache(tlb_cache_info* info, uint8_t descriptor);

/**
 * @brief Gathers CPU information
 */
static void arch_x86_run_cpuid();

/**
 * @brief C Wrapper for the CPUID instruction
 */
static inline void _cpuid(arch_x86_cpuid_regs_t* regs);

/**
 * @brief Isolates bits from a data field
 * @param data Data field
 * @param offset Offset to first bit
 * @param bits Number of bits to fetch
 * @return Isolated bits [offset ... offset + size]
 */
#define fetch_bits(data, offset, bits) ((((data) >> (offset))) & ((1 << (bits)) - 1))

/**
 * @brief Isolates a single bit
 * @param data Data field.
 * @param bit Bit to isolate
 * @return Non-zero if bit was set
 */
#define fetch_bit(data, bit) ((data) & (1 << (bit)))

//==============================================================================
// CPUID Private Data
//==============================================================================

/**
 * Global store of the CPU Identification information
 */
static arch_x86_cpu_ident _cpu_ident = {0};

//==============================================================================
// CPUID Private Function Definitions
//==============================================================================

// TODO Fill out from Intel Manual. These are only the ones found on my computer /Joakim
static int classify_cache(tlb_cache_info* info, uint8_t descriptor)
{
    switch(descriptor)
    {
    case 0x2C:
        info->type = CACHE_TYPE_CACHE;
        info->target = CACHE_TARGET_DATA;

        info->level = 1;
        info->size = 32;
        info->associativity = 8;
        info->line_size = 64;
        return 1;

    case 0x30:
        info->type = CACHE_TYPE_CACHE;
        info->target = CACHE_TARGET_INSTRUCTION;

        info->level = 1;
        info->size = 32;
        info->associativity = 8;
        info->line_size = 64;
        return 1;

    case 0x7D:
        info->type = CACHE_TYPE_CACHE;
        info->target = CACHE_TARGET_GENERAL;

        info->level = 2;
        info->size = 2048;
        info->associativity = 8;
        info->line_size = 64;
        return 1;

    default:
        return 0;
    }
}

static void arch_x86_run_cpuid()
{
    arch_x86_cpuid_regs_t regs;

    //======================================
    // CPUID 0x00000000 Vendor String
    //======================================

    regs.eax.reg = CPUID_GET_VENDOR_STRING;

    _cpuid(&regs);

    for(int i = 0; i < 4; ++i)
    {
        _cpu_ident.vendor[i] = regs.ebx.bytes[i];
        _cpu_ident.vendor[i+4] = regs.edx.bytes[i];
        _cpu_ident.vendor[i+8] = regs.ecx.bytes[i];
    }

    _cpu_ident.max_cpuid = regs.eax.reg;

    //======================================
    // CPUID 0x00000001 Features
    //======================================

    regs.eax.reg = CPUID_GET_FEATURES;

    _cpuid(&regs);

    _cpu_ident.version_info.steppingID = fetch_bits(regs.eax.reg, 0, 4);
    _cpu_ident.version_info.model = fetch_bits(regs.eax.reg, 4, 4);
    _cpu_ident.version_info.familyID = fetch_bits(regs.eax.reg, 8, 4);
    _cpu_ident.version_info.processorType = fetch_bits(regs.eax.reg, 12, 2);
    _cpu_ident.version_info.extModelID = fetch_bits(regs.eax.reg, 16, 4);
    _cpu_ident.version_info.extFamilyID = fetch_bits(regs.eax.reg, 20, 8);

    // TODO: Calculate Family ID acc. to Intel Manual Vol 2A CPUID Instuction Reference

    _cpu_ident.brandID = regs.ebx.bytes[0];
    _cpu_ident.CLFLUSH = regs.ebx.bytes[1];
    _cpu_ident.logicalCPUCount = regs.ebx.bytes[2];
    _cpu_ident.APICID = regs.ebx.bytes[3];

#if DEBUG_CPUID

    printf("Brand ID: %#04x, CLFLUSH: %#04x, CPU Count: %i, APIC ID: %i\n",
           _cpu_ident.brandID,
           _cpu_ident.CLFLUSH,
           _cpu_ident.logicalCPUCount,
           _cpu_ident.APICID);

#endif

    _cpu_ident.ecx_features = regs.ecx.reg;
    _cpu_ident.edx_features = regs.edx.reg;

    //======================================
    // CPUID 0x00000002
    //======================================

    regs.eax.reg = CPUID_GET_TLB;

    _cpuid(&regs);

#if DEBUG_CPUID

    printf("EAX:%#010x, EBX:%#010x, ECX:%#010x, EDX:%#010x\n",
           regs.eax.reg,
           regs.ebx.reg,
           regs.ecx.reg,
           regs.edx.reg);

#endif

    _cpu_ident.cache_table_entries = 0;

    if(regs.eax.bytes[0] == 0x01)
    {
        for(int i = 1; i < 16; ++i)
        {
            if(classify_cache(&_cpu_ident.cache_table[_cpu_ident.cache_table_entries],
                              regs.all_bytes[i]))
            {
                ++_cpu_ident.cache_table_entries;
            }
        }
    }

#if DEBUG_CPUID

    printf("Found %i valid descriptors\n",
           _cpu_ident.cache_table_entries);

#endif

    //======================================
    // CPUID 0x00000003
    //======================================

    // TODO: Fill Out

    //======================================
    // CPUID 0x00000004
    //======================================

    // TODO: Fill out

    //======================================
    // CPUID 0x80000000
    //======================================

    regs.eax.reg = CPUID_INTEL_EXTENDED;

    _cpuid(&regs);

    _cpu_ident.max_cpuid_extended = regs.eax.reg;


    //======================================
    // CPUID 0x80000001
    //======================================

    // TODO: Fill out

    //======================================
    // CPUID 0x80000002
    //======================================

    regs.eax.reg = CPUID_INTEL_BRAND_STRING_0;

    _cpuid(&regs);

    for(int i = 0; i < 16; ++i)
    {
        _cpu_ident.brand[i] = regs.all_bytes[i];
    }

    //======================================
    // CPUID 0x80000003
    //======================================

    regs.eax.reg = CPUID_INTEL_BRAND_STRING_1;

    _cpuid(&regs);

    for(int i = 0; i < 16; ++i)
    {
        _cpu_ident.brand[i+16] = regs.all_bytes[i];
    }

    //======================================
    // CPUID 0x80000004
    //======================================

    regs.eax.reg = CPUID_INTEL_BRAND_STRING_2;

    _cpuid(&regs);

    for(int i = 0; i < 16; ++i)
    {
        _cpu_ident.brand[i + 32] = regs.all_bytes[i];
    }

    //======================================
    // Finish
    //======================================

    // Mark that the structure is valid
    _cpu_ident.valid = 1;

#if DEBUG_CPUID

    printf("%s, Max CPUID: %#010x, Max CPUID Extended: %#010x\n",
           _cpu_ident.vendor,
           _cpu_ident.max_cpuid,
           _cpu_ident.max_cpuid_extended);

    printf("%s\n", _cpu_ident.brand);

#endif
}

static inline void _cpuid(arch_x86_cpuid_regs_t* regs)
{
    asm volatile ("cpuid"
                  : "=a"(regs->eax.reg),
                    "=b"(regs->ebx.reg),
                    "=c"(regs->ecx.reg),
                    "=d"(regs->edx.reg)
                  : "0"(regs->eax.reg));
}

//==============================================================================
// General CPU initialization
//==============================================================================

void arch_x86_initialize_cpu()
{
    // Initialize the GDT
    arch_x86_initialize_gdt();

    // Initialize the IDT
    arch_x86_initialize_idt(0x8);

    // Run the identification
    arch_x86_run_cpuid();
}

void arch_x86_shutdown_cpu()
{
    // We have nothing to do here yet...
}

const char* arch_x86_get_cpu_vendor()
{
    if(!_cpu_ident.valid)
    {
        return (const char*) NULL;
    }

    return (const char*) _cpu_ident.vendor;
}

const char* arch_x86_get_cpu_brand()
{
    if(!_cpu_ident.valid)
    {
        return (const char*) NULL;
    }

    return (const char*) _cpu_ident.brand;
}

uint32_t arch_x86_get_cpu_cache_descriptor_count()
{
    return _cpu_ident.cache_table_entries;
}

int arch_x86_cpu_identified()
{
    return _cpu_ident.valid;
}

int arch_x86_cpu_query_feature(int feature)
{
    if(!_cpu_ident.valid)
    {
        return 0;
    }

    switch(feature)
    {
    case CPU_FEAT_SSE3:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_SSE3;
    case CPU_FEAT_PCLMUL:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_PCLMUL;
    case CPU_FEAT_DTES64:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_DTES64;
    case CPU_FEAT_MONITOR:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_MONITOR;
    case CPU_FEAT_DS_CPL:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_DS_CPL;
    case CPU_FEAT_VMX:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_VMX;
    case CPU_FEAT_SMX:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_SMX;
    case CPU_FEAT_EST:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_EST;
    case CPU_FEAT_TM2:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_TM2;
    case CPU_FEAT_SSSE3:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_SSSE3;
    case CPU_FEAT_CID:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_CID;
    case CPU_FEAT_FMA:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_FMA;
    case CPU_FEAT_CX16:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_CX16;
    case CPU_FEAT_ETPRD:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_ETPRD;
    case CPU_FEAT_PDCM:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_PDCM;
    case CPU_FEAT_PCIDE:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_PCIDE;
    case CPU_FEAT_DCA:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_DCA;
    case CPU_FEAT_SSE4_1:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_SSE4_1;
    case CPU_FEAT_SSE4_2:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_SSE4_2;
    case CPU_FEAT_x2PIC:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_x2APIC;
    case CPU_FEAT_MOVBE:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_MOVBE;
    case CPU_FEAT_POPCNT:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_POPCNT;
    case CPU_FEAT_AES:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_AES;
    case CPU_FEAT_XSAVE:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_XSAVE;
    case CPU_FEAT_OSXSAVE:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_OSXSAVE;
    case CPU_FEAT_AVX:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_AVX;
    case CPU_FEAT_F16C:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_F16C;
    case CPU_FEAT_RDRAND:
        return _cpu_ident.ecx_features & CPUID_FEAT_ECX_RDRAND;

    case CPU_FEAT_FPU:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_FPU;
    case CPU_FEAT_VME:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_VME;
    case CPU_FEAT_DE:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_DE;
    case CPU_FEAT_PSE:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_PSE;
    case CPU_FEAT_TSC:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_TSC;
    case CPU_FEAT_MSR:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_MSR;
    case CPU_FEAT_PAE:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_PAE;
    case CPU_FEAT_MCE:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_MCE;
    case CPU_FEAT_CX8:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_CX8;
    case CPU_FEAT_APIC:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_APIC;
    case CPU_FEAT_SEP:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_SEP;
    case CPU_FEAT_MTRR:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_MTRR;
    case CPU_FEAT_PGE:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_PGE;
    case CPU_FEAT_MCA:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_MCA;
    case CPU_FEAT_CMOV:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_CMOV;
    case CPU_FEAT_PAT:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_PAT;
    case CPU_FEAT_PSE36:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_PSE36;
    case CPU_FEAT_PSN:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_PSN;
    case CPU_FEAT_CLF:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_CLF;
    case CPU_FEAT_DTES:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_DTES;
    case CPU_FEAT_ACPI:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_ACPI;
    case CPU_FEAT_MMX:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_MMX;
    case CPU_FEAT_FXSR:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_FXSR;
    case CPU_FEAT_SSE:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_SSE;
    case CPU_FEAT_SSE2:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_SSE2;
    case CPU_FEAT_SS:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_SS;
    case CPU_FEAT_HTT:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_HTT;
    case CPU_FEAT_TM1:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_TM1;
    case CPU_FEAT_IA64:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_IA64;
    case CPU_FEAT_PBE:
        return _cpu_ident.edx_features & CPUID_FEAT_EDX_PBE;
    default:
        return 0;
    }
}
