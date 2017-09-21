/**
 * @file    memory_manager.h
 * @author  Joakim Bertils
 * @date    2017-09-20
 * @brief   Interface of the kernel memory manager.
 */

#ifndef _MEMORY_MANAGER_H
#define _MEMORY_MANAGER_H

#include <stdint.h>

//==============================================================================
// Physical Memory Manager
//==============================================================================

/**
 * Type representing a physical address.
 */
typedef uint32_t phys_addr;

/**
 * @brief Initiates the physical memory manager.
 * 
 * @param mem_size Size of the memory.
 * @param bitmap_addr Address where the memory manager can store the bitmap.
 */
void pmmngr_init(size_t mem_size, phys_addr bitmap_addr);

/**
 * @brief Initiates a region for the physical memory manager to use.
 * 
 * @param base Base address of the region.
 * @param size Size of the region to be initiated.
 */
void pmmngr_init_region(phys_addr base, size_t size);

/**
 * @brief Deinitiates a region for the physical memory manager not to use.
 *
 * @param base Base address of the region.
 * @param size Size of the region.
 */
void pmmngr_deinit_region(phys_addr base, size_t size);

/**
 * @brief Allocates a block of memory.
 * 
 * @return Address of start of allocated block if successful, else 0.
 */
void* pmmngr_alloc_block(void);

/**
 * @brief Allocates a zeroed block of memory.
 * 
 * @return Address of start of allocated block if successful, else 0.
 */
void* pmmngr_alloc_block_z(void);

/**
 * @brief Frees a block, marking it available to use.
 *
 * @param addr Address of block to free.
 */
void pmmngr_free_block(void* addr);

/**
 * @brief Allocates multiple blocks.
 * 
 * @param size Number of blocks to allocate
 *
 * @return Address of start of block
 */
void* pmmngr_alloc_blocks(size_t size);

/**
 * @brief Allocates multiple zeroed blocks.
 * 
 * @param size Number of blocks to allocate
 *
 * @return Address of start of block
 */
void* pmmngr_alloc_blocks_z(size_t size);

/**
 * @brief Frees multiple blocks.
 * 
 * @param p Address of block to free.
 * @param size Number of blocks to free
 */
void pmmngr_free_blocks(void* p, size_t size);

/**
 * @brief Gets the size of the memory of the physical memory manager.
 *
 * @return Memory size.
 */
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
    PTE_WRITETHROUGH = 8,
    PTE_NOT_CAHCEABLE = 0x10,
    PTE_ACCESS = 0x20,
    PTE_DIRTY = 0x40,
    PTE_PAT = 0x80, // Page attribute table
    PTE_CPU_GLOBAL = 0x100,
    PTE_LV4_GLOBAL = 0x200,
    PTE_FRAME = 0x7FFFF000
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

int pd_entry_is_present(pd_entry e);
int pd_entry_is_writable(pd_entry e);
int pd_entry_is_user(pd_entry e);
int pd_entry_is_pwt(pd_entry e);
int pd_entry_is_pcd(pd_entry e);
int pd_entry_is_accessed(pd_entry e);
int pd_entry_is_dirty(pd_entry e);
int pd_entry_is_4MB(pd_entry e);
int pd_entry_is_CPU_global(pd_entry e);
int pd_entry_is_LV4_global(pd_entry e);
phys_addr pd_entry_pfn(pd_entry e);

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

// maps phys to virtual address
void vmmngr_map_page(void* phys, void* virt);

// initialize the memory manager
void vmmngr_initialize ();

// allocates a page in physical memory
int vmmngr_alloc_page (pt_entry* e);

// frees a page in physical memory
void vmmngr_free_page (pt_entry* e);

// switch to a new page directory
int vmmngr_switch_pdirectory(pdirectory* dir);

// get current page directory
pdirectory* vmmngr_get_directory();

// flushes a cached translation lookaside buffer (TLB) entry
void vmmngr_flush_tlb_entry (virt_addr addr);

// clears a page table
void vmmngr_ptable_clear (ptable* p);

// convert virtual address to page table index
uint32_t vmmngr_ptable_virt_to_index (virt_addr addr);

// get page entry from page table
pt_entry* vmmngr_ptable_lookup_entry (ptable* p, virt_addr addr);

// convert virtual address to page directory index
uint32_t vmmngr_pdirectory_virt_to_index (virt_addr addr);

// clears a page directory table
void vmmngr_pdirectory_clear (pdirectory* dir);

// get directory entry from directory table
pd_entry* vmmngr_pdirectory_lookup_entry (pdirectory* p, virt_addr addr);

int vmmngr_createPageTable(pdirectory* dir, uint32_t virt, uint32_t flags);

void vmmngr_mapPhysicalAddress(pdirectory* dir, uint32_t virt, uint32_t phys, uint32_t flags);

void vmmngr_unmapPageTable(pdirectory* dir, uint32_t virt);

void vmmngr_unmapPhysicalAddress(pdirectory* dir, uint32_t virt);

pdirectory* vmmngr_createAddressSpace();

pdirectory* vmmngr_cloneAddressSpace();

void* vmmngr_getPhysicalAddress(pdirectory* dir, uint32_t virt);

//==============================================================================
// Dynamic Memory Manager
//==============================================================================

#endif
