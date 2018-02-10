
/*
  ================================================================================
  Project Layout
  ================================================================================

  Kernel:

  OS5.bin - Main executable
  libk.a - Kernel-relevant subset of libc
  OS5gui.a - Graphics implementation

  Drivers:

  device.driver - Driver Module
  libc.a - C standard library

  Userspace:

  program.elf - Main executable
  libc.a - C standard library
  libOS5.a - Kernel Interface (May be merged with libc.a depending on functionality)

*/

/*
  ================================================================================
  Improvements over OS4:
  ================================================================================

  Arch:

  *Better interface to CPU-specific features to ease porting to other platforms

  Binary Structure:

  *Separate a simple kernel c library (LIBK) with kernel-relevant subset of libc

  ACPI:

  *Better parsing of AML and uniform table parsing. Make sure to parse before paging
  to avoid memory mapping trouble.

  CLI:

  *Better handling of CLI functions with argument passing.
  *Scrolling
  *Command History
  *Auto complete
  *Working directory

  Multiuser:

  *Login
  *Profile
  *Home Directory
  *Profile Picture
  *Desktop Background

  Multitasking:

  *Better handling and synchronization of threads and it's resources.
  *Priorities and skipping blocked threads

  IPC:

  *Ways of communicating between processes and threads.
  *Tree of properties (Windows Registry)
  *Pipes (Communication tunnels)

  File System:

  *Read/Write for multiple file formats
  *Support for pipes and special files

  Drivers:

  *Uniform handling and assigning of drivers to detected devices.

  Executables:

  *Passing of arguments to executed files
  *LIBC
  *Dynamic loading
  *Improved memory management for executed files (heap, stack, image, shared libraries, etc.).

  GUI:

  *Better VGA/VESA handling (preferrably through PCI)
  *Major speed improvements (recalculate based on performance and not each mouse irq)
  *Window Management
  *Application creates it's own window through GUI api.
  *Robust repaint calculations

  USB:

  *Implement

  Network:

  *Implement

  Sound:

  *Implement
  *Play sound files

  Debugging:

  *Better ways of debugging the kernel and it's executed programs (DDD and gdb)
  *Unit tests

  Native Scripting/Programming language:

  *Built-in parser for script-like programming (bash / bat)
  *Support for running commands, file IO, basic calculations, etc.

  Built-in programs:

  *Calculator
  *Text editor
  *Browser
  *Sound Player
  *Picture Viewer
  *Simple Games(Chess, Asteroids)

  */

/*
  ================================================================================
  Roadmap:
  ================================================================================

  Initialize CPU: (ARCH x86)

  *GDT - Done
  *IDT - Done
  *CPUID - Done
  *IRQ - Done
  *PIC - Done
  *PIT - Done
  *FPU

  Initialize Debug Facilities:

  *Debug Terminal - Done
  *Debug Keyboard Input
  *Debug Serial Communication + protocols
  *Command Line interface

  Ramdisk:

  *Load ramdisk from multiboot
  *Store Programs and files useful until main disk is booted and mounted.

  ACPI:

  *Parse Tables
  *Parse AML Code
  *Get Shutdown Information
  *Get Century Register

  Initialize Memory:

  *Physical Memory Manager
  *Virtual Memory Manager
  *Dynamic Allocation Manager (Heap)

  Util Datastructures:

  *List
  *Ring
  *Map
  *Tree

  Misc Features:

  *CMOS Clock

  Multitasking:

  *Initialize Scheduler
  *Process
  *Thread
  *Setup IPC
  *Mutex & other semaphores

  Executables:

  *Launch and Execute Processes (ELF)
  *System Calls

  Setup Virtual File System:

  *Mount Devices
  *Read/Write
  *FAT32
  *ext2
  *NTFS

  Drivers:

  *Initialize Driver Manager
  *PCI
  *Initialize Driver

  *HDD
  *Mouse
  *Keyboard
  *Graphics Adapter
  *USB (OHCI, UHCI, EHCI, XHCI)
  *Network Card

  Graphics: (separate archive)

  *Window Manager
  *Standard Controls and Widgets
  *Application <-> Window Manager Interface

  Networking:

  *Network Adapter E1000
  *ARP
  *Ethernet
  *IPv4
  *IPv6
  *UDP
  *TCP
  *Sockets

  */

/*
  ================================================================================
  Name suggestion list:
  ================================================================================

  *Lumos
  *OS5

  */

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <kernel/debug_terminal.h>
#include <kernel/memory_manager.h>
#include <kernel/multiboot.h>

#include <arch/arch.h>

#include <acpi/acpi.h>

#include <math.h>

//==============================================================================
// Function forward declarations
//==============================================================================

void initialize_kernel(multiboot_info_t* mb_info);

void install_interrupts();

extern void divide_by_zero_irq(void);
extern void debug_irq(void);
extern void non_maskable_interrupt_irq(void);
extern void breakpoint_irq(void);
extern void overflow_irq(void);
extern void bound_range_irq(void);
extern void invalid_opcode_irq(void);
extern void device_not_available_irq(void);
extern void double_fault_irq(void);
extern void invalid_tss_irq(void);
extern void seg_not_present_irq(void);
extern void stack_seg_fault_irq(void);
extern void general_protection_fault_irq(void);
extern void page_fault_irq(void);
extern void FPU_exception_irq(void);
extern void alignment_check_irq(void);
extern void machine_check_irq(void);
extern void SIMD_floating_point_irq(void);
extern void virtualization_irq(void);
extern void security_irq(void);


//==============================================================================
// Implementation private data
//==============================================================================

//==============================================================================
// Function definitions
//==============================================================================

void set_fpu_cw(const uint16_t cw)
{
    asm volatile("fldcw %0" :: "m"(cw));
}

void enable_fpu()
{
    printf("Enabling FPU\n");

    size_t cr4;
    asm volatile ("mov %%cr4, %0" : "=r"(cr4));
    cr4 |= 0x200;
    asm volatile ("mov %0, %%cr4" :: "r"(cr4));
    set_fpu_cw(0x37F);
}

int comp(const void *a, const void *b)
{
    return *((int*)a) < *((int*)b);
}

extern uint32_t end;

char* strMemoryTypes[] = {

    {"None"},
    {"Available"},          // memory_region.type==1
    {"Reserved"},           // memory_region.type==2
    {"ACPI Reclaim"},       // memory_region.type==3
    {"ACPI NVS Memory"}     // memory_region.type==4
};

void initialize_kernel(multiboot_info_t* mb_info)
{
    debug_terminal_initialize();

    printf("Kernel booting... Please wait.\n");

    printf("mmap_length: %i, mmap_addr: %#010p\n",
           mb_info->mmap_length,
           mb_info->mmap_addr);

    printf("mods_count: %i, mods_addr: %#010p\n",
           mb_info->mods_count,
           mb_info->mods_addr);

    uint32_t memSize = 1024 + mb_info->mem_lower + mb_info->mem_upper;

    uint32_t kernel_end = (uint32_t)(&end);

    uint32_t kernel_size = kernel_end - 0xC0100000;

    pmmngr_init(memSize, 0xC0000000 + kernel_size);

    int mmap_entries = mb_info->mmap_length / sizeof(multiboot_memory_map_t);
    multiboot_memory_map_t* mem_map = (multiboot_memory_map_t*)(mb_info->mmap_addr+0xC0000000);

    for(int i = 0; i < mmap_entries; ++i)
    {
        if(mem_map[i].type == 1)
        {
            pmmngr_init_region(mem_map[i].addr_low + 0xC0000000, mem_map[i].len_low);
            printf("Addr: %#010x\n", mem_map[i].addr_low);
            printf("len: %i\n", mem_map[i].len_low);
        }
    }

    pmmngr_deinit_region(0xC0100000, kernel_size);

    printf("Initializing VMM\n");

    vmmngr_initialize();

    printf("Initializing Kernel Heap\n");

    init_kernel_heap();

    arch_initialize();

    printf("Arch Initialized!\n");

    install_interrupts();

    //acpi_initialize();

    printf("ACPI Initialized!\n");

    enable_fpu();

    enable_interrupts();


/*
    while(1)
    {
        printf("PIT Ticks: %i\n", get_tick_count());
    }
*/

}

void install_interrupts()
{
    setvect(0, (IRQ_HANDLER)divide_by_zero_irq, 0);
    setvect(1, (IRQ_HANDLER)debug_irq, 0);
    setvect(2, (IRQ_HANDLER)non_maskable_interrupt_irq, 0);
    setvect(3, (IRQ_HANDLER)breakpoint_irq, 0);
    setvect(4, (IRQ_HANDLER)overflow_irq, 0);
    setvect(5, (IRQ_HANDLER)bound_range_irq, 0);
    setvect(6, (IRQ_HANDLER)invalid_opcode_irq, 0);
    setvect(7, (IRQ_HANDLER)device_not_available_irq, 0);
    setvect(8, (IRQ_HANDLER)double_fault_irq, 0);
    setvect(10, (IRQ_HANDLER)invalid_tss_irq, 0);
    setvect(11, (IRQ_HANDLER)seg_not_present_irq, 0);
    setvect(12, (IRQ_HANDLER)stack_seg_fault_irq, 0);
    setvect(13, (IRQ_HANDLER)general_protection_fault_irq, 0);
    setvect(14, (IRQ_HANDLER)page_fault_irq, 0);
    setvect(16, (IRQ_HANDLER)FPU_exception_irq, 0);
    setvect(17, (IRQ_HANDLER)alignment_check_irq, 0);
    setvect(18, (IRQ_HANDLER)machine_check_irq, 0);
    setvect(19, (IRQ_HANDLER)SIMD_floating_point_irq, 0);
    setvect(20, (IRQ_HANDLER)virtualization_irq, 0);
    setvect(30, (IRQ_HANDLER)security_irq, 0);
}

/*
  void test_fpu()
  {
  float f1 = 13.f;
  float f2 = 14.f;

  float f3 = fmaxf(f1, f2);

  if(f3 - f2 < 0.01f)
  {
  printf("fmaxf test passed\n");
  }

  }
*/

void on_tick(void)
{
    printf("test\n");
}

void kernel_main(multiboot_info_t* mb_info, uint32_t mb_magic)
{
    initialize_kernel(mb_info);

    set_on_tick_handler(on_tick);

    for(;;);

    printf("Kernel Finished. Halting...\n");
}
