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
// Virtual Memory Manager
//==============================================================================

//==============================================================================
// Dynamic Memory Manager
//==============================================================================

#endif
