#ifndef _MEMORY_MANAGER_H
#define _MEMORY_MANAGER_H

#include <stdint.h>

//==============================================================================
// Physical Memory Manager
//==============================================================================

typedef uint32_t phys_addr;

void pmmngr_init(size_t mem_size, phys_addr bitmap_addr);

void pmmngr_init_region(phys_addr base, size_t size);

void pmmngr_deinit_region(phys_addr base, size_t size);

void* pmmngr_alloc_block(void);

void* pmmngr_alloc_block_z(void);

void pmmngr_free_block(void* addr);

void* pmmngr_alloc_blocks(size_t size);

void* pmmngr_alloc_blocks_z(size_t size);

void pmmngr_free_blocks(size_t size);

size_t pmmngr_get_memory_size();

uint32_t pmmngr_get_block_count();

uint32_t pmmngr_get_used_block_count();

uint32_t pmmngr_get_free_block_count();

uint32_t pmmngr_get_block_size();

void pmmngr_paging_enable(int b);

int pmmngr_is_paging();

void pmmngr_load_PBDR(phys_addr addr);

phys_addr pmmngr_get_PBDR();

//==============================================================================
// Page Table Entry
//==============================================================================

enum PTE_FLAGS
{
    PTE_PRESENT = 1,
    PTE_WRITABLE = 2,
    PTE_USER = 4,
    PTE_WRITEWTHROUGH = 8,
    PTE_NOT_CAHCEABLE = 0x10,
    PTE_ACCESS = 0x20,
    PTE_DIRTY = 0x40,
    PTE_PAT = 0x80, // Page attribute table
    PTE_CPU_GLOBAL = 0x100,
    PTE_LV4_GLOBAL = 0x200,
    PTE_FRAME 0x7FFFF000
};

typedef uint32_t pt_entry;

void pt_entry_add_attrib(pt_entry* e, uint32_t attrib);
void pt_entry_del_attrib(pt_entry* e, uint32_t attrib);
void pt_entry_set_frame(pt_entry* e, phys_addr addr);

int pt_entry_is_present(pt_entry e);
int pt_entry_is_writable(pt_entry e);
int pt_entry_is_user(pt_entry e);
int pt_entry_is_writethrough(pt_entry e);
int pt_entry_is_cacheable(pt_entry e);
int pt_entry_is_accessed(pt_entry e);
int pt_entry_is_dirty(pt_entry e);
int pt_entry_is_PAT(pt_entry e);
int pt_entry_is_CPU_global(pt_entry e);
int pt_entry_is_LV4_global(pt_entry e);
phys_addr pt_entry_pfn(pt_entry e);

//==============================================================================
// Page Directory Entry
//==============================================================================

enum PDE_FLAGS
{
    PDE_PRESENT = 1,
    PDE_WRITABLE = 2,
    PDE_USER = 4,
    PDE_PWT = 8,
    PDE_PCD = 0x10,
    PDE_ACCESSED = 0x20,
    PDE_DIRTY = 0x40,
    PDE_4MB = 0x80,
    PDE_CPU_GLOBAL = 0x100,
    PDE_LV4_GLOBAL = 0x200,
    PDE_FRAME = 0x7FFFF000
};

typedef uint32_t pd_entry;

void pd_entry_add_attrib(pd_entry* e, uint32_t attrib);
void pd_entry_del_attrib(pd_entry* e, uint32_t attrib);
void pd_entry_set_frame(pd_entry* e, phys_addr addr);

int pd_entry_is_present(pt_entry e);
int pd_entry_is_writable(pt_entry e);
int pd_entry_is_user(pt_entry e);
int pd_entry_is_pwt(pt_entry e);
int pd_entry_is_pcd(pt_entry e);
int pd_entry_is_accessed(pt_entry e);
int pd_entry_is_dirty(pt_entry e);
int pd_entry_is_4MB(pt_entry e);
int pd_entry_is_CPU_global(pt_entry e);
int pd_entry_is_LV4_global(pt_entry e);
phys_addr pd_entry_pfn(pt_entry e);

//==============================================================================
// Virtual Memory Manager
//==============================================================================

typedef uint32_t virt_addr;

#define PAGES_PER_TABLE 1024
#define PAGES_PER_DIR 1024

#define PAGE_DIRECTORY_INDEX(x) (((x) >> 22) & 0x3FF)
#define PAGE_TABLE_INDEX(x) (((x) >> 12) & 0x3FF)
#define PAGE_GET_PHYSICAL_ADDRESS(x) (*x & ~0xFFF)

typedef struct
{
    pt_entry m_entries[PAGES_PER_TABLE];
} ptable;

typedef struct
{
    pd_entry m_entries[PAGES_PER_DIR];
} pdirectory;

//==============================================================================
// Dynamic Memory Manager
//==============================================================================

#endif
