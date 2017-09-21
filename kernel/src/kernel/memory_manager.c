/**
 * @file    memory_manager.c
 * @author  Joakim Bertils
 * @date    2017-09-20
 * @brief   Implementation of the kernel memory manager.
 */

#include <kernel/memory_manager.h>

//==============================================================================
// Physical Memory Manager
//==============================================================================

/**
 * Number of blocks per byte in bitmap.
 */
#define PMMNGR_BLOCKS_PER_BYTE 8

/**
 * Size in bytes of a single block.
 */
#define PMMNGR_BLOCK_SIZE 4096

/**
 * Block alignment granularity.
 */
#define PMMNGR_BLOCK_ALIGN PMMNGR_BLOCK_SIZE

/**
 * Size of physical memory managed by memory manager.
 */
static uint32_t _pmmngr_memory_size = 0;

/**
 * Number of blocks currently in use.
 */
static uint32_t _pmmngr_used_blocks = 0;

/**
 * Maximum number of blocks.
 */
static uint32_t _pmmngr_max_blocks = 0;

/**
 * Pointer to memory map
 */
static uint32_t* _pmmngr_memory_map = 0;

/**
 * @brief Sets a bit in the memory bitmap
 *
 * @param bit Bit to set.
 */
void mmap_set(int bit);

/**
 * @brief Unsets a bit in the memory bitmap.
 *
 * @param bit Bit to unset.
 */
void mmap_unset(int bit);

/**
 * @brief Tests a bit in the memory bitmap.
 *
 * @param bit Bit to test.
 * @return Non-zero if bit is set.
 */
int mmap_test(int bit);

/**
 * @brief Finds the first free bit in bitmap.
 *
 * @return Index of found bit.
 */
size_t mmap_first_free();

/**
 * @brief Finds the first free bit chain in bitmap.
 *
 * @param n Minimum number of blocks in chain.
 *
 * @return Index of first found bit.
 */
size_t mmap_first_free_s(size_t n);

/**
 * Number of bits per entry in bitmap.
 */
#define BITS_PER_ENTRY 32U

void mmap_set(int bit)
{
    _pmmngr_memory_map[bit / BITS_PER_ENTRY] |= (1<<(bit % BITS_PER_ENTRY));
}

void mmap_unset(int bit)
{
    _pmmngr_memory_map[bit / BITS_PER_ENTRY] &= ~(1<<(bit % BITS_PER_ENTRY));
}

int mmap_test(int bit)
{
    return _pmmngr_memory_map[bit / BITS_PER_ENTRY] & (1<<(bit % BITS_PER_ENTRY));
}

size_t mmap_first_free()
{
    for(uint32_t entry = 0;
        entry < pmmngr_get_block_count() / BITS_PER_ENTRY;
        ++entry)
    {

        // If the entry is full, go to the next one
        if(_pmmngr_memory_map[entry] == 0xFFFFFFFF)
            continue;

        // Check each bit in the entry
        for(int bit = 0; bit < BITS_PER_ENTRY;  ++bit)
        {
            if(!(_pmmngr_memory_map[entry] & (1<<bit)))
            {
                return entry * BITS_PER_ENTRY + bit;
            }
        }
    }

    return -1;
}

size_t mmap_first_free_s(size_t size)
{
    uint32_t firstFree = mmap_first_free();

    // We could not find any free blocks.
    if(firstFree == -1)
        return -1;

    // Don't allocate if there is nothing to allocate
    if(size == 0)
        return -1;

    // If we only want to allocate one block, we can pick first free
    if(size == 1)
        return firstFree;

    // Number of free contiguous blocks found.
    uint32_t free = 0;

    // First free bit of chain
    uint32_t first_bit_in_chain = firstFree;

    // Loop through each bit from firstFree to end of memory
    for(int bit = firstFree; bit < pmmngr_get_block_count(); ++bit)
    {
        // If bit is set (memory not free)
        if(mmap_test(bit))
        {
            // Reset counter
            free = 0;

            // Next bit is potential new start of chain.
            first_bit_in_chain = bit + 1;
        }
        else
        {
            // Bit is free. Increase counter
            ++free;
        }

        // If we found enough bits, we are done
        if(free == size)
            return first_bit_in_chain;
    }

    //We went through all blocks in memory and did not find a chain
    return -1;
}

void pmmngr_init(size_t mem_size, phys_addr bitmap_addr)
{
    _pmmngr_memory_size = mem_size;
    _pmmngr_memory_map = (uint32_t*) bitmap_addr;
    _pmmngr_max_blocks = (pmmngr_get_memory_size() * 1024)/ PMMNGR_BLOCK_SIZE;
    _pmmngr_used_blocks = _pmmngr_max_blocks;

    printf("PMM Bitmap Size: %i\n", pmmngr_get_block_count() / PMMNGR_BLOCKS_PER_BYTE);

    int entries = pmmngr_get_block_count() / BITS_PER_ENTRY;

    for(int i = 0; i < entries; ++i)
    {
        _pmmngr_memory_map[i] = 0xFFFFFFFF;
    }

    printf("PMM init. with bitmap at: %#010x, (Entries: %i)\n", _pmmngr_memory_map, entries);
}

void pmmngr_init_region(phys_addr base, size_t size)
{
    int align = (base - 0xC0000000) / PMMNGR_BLOCK_ALIGN;
    int blocks = size / PMMNGR_BLOCK_SIZE;

    printf("[PHYSMEM] Initiating region with size: %i\n", size);

    while(blocks-->=0)
    {
        mmap_unset(align++);
        _pmmngr_used_blocks--;
    }

    mmap_set(0);
}

void pmmngr_deinit_region(phys_addr base, size_t size)
{
    int align = (base - 0xC0000000) / PMMNGR_BLOCK_ALIGN;
    int blocks = size / PMMNGR_BLOCK_SIZE;

    printf("[PHYSMEM] De-initiating region with size: %i\n", size);

    while(blocks-->=0)
    {
        mmap_set(align++);
        _pmmngr_used_blocks++;
    }
}

void* pmmngr_alloc_block(void)
{
    if(pmmngr_get_block_count() <= 0)
    {
        printf("[PHYSMEM] No memory left(1)\n");
        return 0;
    }

    int frame = mmap_first_free();

    // Out of memory
    if(frame == -1)
    {
        printf("\n[PHYSMEM] No memory left(2)\n");
        return 0;
    }


    // Mark block as used
    mmap_set(frame);

    phys_addr addr = frame * PMMNGR_BLOCK_SIZE;
    _pmmngr_used_blocks++;

    // Return address of block start
    return (void*) addr;
}

void* pmmngr_alloc_block_z(void)
{
    // Check if we have memory left
    if(pmmngr_get_block_count() <= 0)
        return 0;

    int frame = mmap_first_free();

    // Out of memory
    if(frame == -1)
        return 0;

    // Mark block as used
    mmap_set(frame);

    phys_addr addr = frame * PMMNGR_BLOCK_SIZE;
    _pmmngr_used_blocks++;

    memset(addr, 0x00, PMMNGR_BLOCK_SIZE);

    // Return address of block start
    return (void*) addr;
}

void pmmngr_free_block(void* p)
{
    // Calculate frame of the address
    phys_addr addr = (phys_addr)p;
    int frame = addr / PMMNGR_BLOCK_SIZE;

    // Mark as free
    mmap_unset(frame);

    _pmmngr_used_blocks--;
}

void* pmmngr_alloc_blocks(size_t size)
{
    // Out of memory
    if(pmmngr_get_block_count() <= size)
        return 0;

    int frame = mmap_first_free_s(size);

    // Out of memory
    if(frame == -1)
        return 0;

    for(uint32_t i = 0; i < size; ++i)
    {
        mmap_set(frame + i);
    }

    phys_addr addr = frame * PMMNGR_BLOCK_SIZE;
    _pmmngr_used_blocks += size;

    return (void*) addr;
}

void* pmmngr_alloc_blocks_z(size_t size)
{
    // Out of memory
    if(pmmngr_get_block_count() <= size)
        return 0;

    int frame = mmap_first_free_s(size);

    // Out of memory
    if(frame == -1)
        return 0;

    for(uint32_t i = 0; i < size; ++i)
    {
        mmap_set(frame + i);
    }

    phys_addr addr = frame * PMMNGR_BLOCK_SIZE;
    _pmmngr_used_blocks += size;

    memset(addr, 0x00, PMMNGR_BLOCK_SIZE * size);

    return (void*) addr;
}

void pmmngr_free_blocks(void* p, size_t size)
{
    // Calculate start frame from the address
    phys_addr addr = (phys_addr)p;
    int frame = addr / PMMNGR_BLOCK_SIZE;

    for(uint32_t i = 0; i < size; ++i)
    {
        mmap_unset(frame + i);
    }

    _pmmngr_used_blocks -= size;
}

size_t pmmngr_get_memory_size()
{
    return _pmmngr_memory_size;
}

uint32_t pmmngr_get_block_count()
{
    return _pmmngr_max_blocks;
}

uint32_t pmmngr_get_used_block_count()
{
    return _pmmngr_used_blocks;
}

uint32_t pmmngr_get_free_block_count()
{
    return _pmmngr_max_blocks - _pmmngr_used_blocks;
}

uint32_t pmmngr_get_block_size()
{
    return PMMNGR_BLOCK_SIZE;
}

void pmmngr_paging_enable(int b)
{
    uint32_t cr0_reg;

    asm volatile ("mov %%cr0, %0" : "=r"(cr0_reg));

    if(b)
    {
        cr0_reg |= 0x80000000;
    }
    else
    {
        cr0_reg &= ~0x80000000;
    }

    asm volatile ("mov %0, %%cr0" :: "r"(cr0_reg));
}

int pmmngr_is_paging()
{
    uint32_t cr0_reg;

    // Fetch data in cr0
    asm volatile ("mov %%cr0, %0" : "=r"(cr0_reg));

    return (cr0_reg & 0x80000000) ? 1 : 0;
}

void pmmngr_load_PBDR(phys_addr addr)
{
    asm volatile ("movl %0,%%eax"::"r"(addr):"%eax"); // Move addr to eax

    asm volatile ("movl %%eax,%%cr3":::"%eax"); // move eax to cr3
}

phys_addr pmmngr_get_PBDR()
{
    phys_addr PBDR;

    // Fetch data in cr3
    asm volatile ("mov %%cr3, %0" : "=r"(PBDR));

    return PBDR;
}

//==============================================================================
// Virtual Memory Manager
//==============================================================================


void pt_entry_add_attrib(pt_entry* e, uint32_t attrib)
{
    *e |= attrib;
}

void pt_entry_del_attrib(pt_entry* e, uint32_t attrib)
{
    *e &= ~attrib;
}

void pt_entry_set_frame(pt_entry* e, phys_addr addr)
{
    *e = (*e & ~PTE_FRAME) | addr;
}

int pt_entry_is_present(pt_entry e)
{
    return e & PTE_PRESENT;
}

int pt_entry_is_writable(pt_entry e)
{
    return e & PTE_WRITABLE;
}

int pt_entry_is_user(pt_entry e)
{
    return e & PTE_USER;
}

int pt_entry_is_writethrough(pt_entry e)
{
    return e & PTE_WRITETHROUGH;
}

int pt_entry_is_cacheable(pt_entry e)
{
    return !(e & PTE_NOT_CAHCEABLE);
}

int pt_entry_is_accessed(pt_entry e)
{
    return e & PTE_ACCESS;
}

int pt_entry_is_dirty(pt_entry e)
{
    return e & PTE_DIRTY;
}

int pt_entry_is_PAT(pt_entry e)
{
    return e & PTE_PAT;
}

int pt_entry_is_CPU_global(pt_entry e)
{
    return e & PTE_CPU_GLOBAL;
}

int pt_entry_is_LV4_global(pt_entry e)
{
    return e & PTE_LV4_GLOBAL;
}

phys_addr pt_entry_pfn(pt_entry e)
{
    return e & PTE_FRAME;
}

void pd_entry_add_attrib(pd_entry* e, uint32_t attrib)
{
    *e |= attrib;
}

void pd_entry_del_attrib(pd_entry* e, uint32_t attrib)
{
    *e &= ~attrib;
}

void pd_entry_set_frame(pd_entry* e, phys_addr addr)
{
    *e = (*e & ~PDE_FRAME) | addr;
}

int pd_entry_is_present(pd_entry e)
{
    return e & PDE_PRESENT;
}

int pd_entry_is_writable(pd_entry e)
{
    return e & PDE_WRITABLE;
}

int pd_entry_is_user(pd_entry e)
{
    return e & PDE_USER;
}

int pd_entry_is_pwt(pd_entry e)
{
    return e & PDE_PWT;
}

int pd_entry_is_pcd(pd_entry e)
{
    return e & PDE_PCD;
}

int pd_entry_is_accessed(pd_entry e)
{
    return e & PDE_ACCESSED;
}

int pd_entry_is_dirty(pd_entry e)
{
    return e & PDE_DIRTY;
}

int pd_entry_is_4MB(pd_entry e)
{
    return e & PDE_4MB;
}

int pd_entry_is_CPU_global(pd_entry e)
{
    return e & PDE_CPU_GLOBAL;
}

int pd_entry_is_LV4_global(pd_entry e)
{
    return e & PDE_LV4_GLOBAL;
}

phys_addr pd_entry_pfn(pd_entry e)
{
    return e & PDE_FRAME;
}

#define PTABLE_ADDR_SPACE_SIZE 0x400000
#define DTABLE_ADDR_SPACE_SIZE 0x100000000
#define PAGE_SIZE 4096

pdirectory* _cur_directory = 0;

phys_addr _cur_pdbr = 0;

void vmmngr_map_page(void* phys, void* virt)
{
    pdirectory* pageDirectory = vmmngr_get_directory();

    pd_entry* e =
        &pageDirectory->m_entries[PAGE_DIRECTORY_INDEX((uint32_t) virt)];

    if(!pd_entry_is_present(*e))
    {

        // Allocate page table
        ptable* table = (ptable*)pmmngr_alloc_block();

        if(!table)
            return;

        memset(table,0,sizeof(ptable));

        pd_entry* entry =
            &pageDirectory->m_entries[PAGE_DIRECTORY_INDEX((uint32_t) virt)];

        pd_entry_add_attrib(entry, PDE_PRESENT);
        pd_entry_add_attrib(entry, PDE_WRITABLE);
        pd_entry_set_frame(entry, (phys_addr)table);
    }

    // Get table
    ptable* table = (ptable*) PAGE_GET_PHYSICAL_ADDRESS(e);

    // Get page
    pt_entry* page = &table->m_entries[PAGE_TABLE_INDEX((uint32_t) virt)];

    pt_entry_set_frame(page, (phys_addr)phys);
    pt_entry_add_attrib(page, PTE_PRESENT);
}

void vmmngr_initialize(){

    // allocate default page table
    ptable* table = (ptable*) pmmngr_alloc_block ();
    if (!table)
    {
        return;
    }


    // allocates 3gb page table
    ptable* table2 = (ptable*) pmmngr_alloc_block ();
    if (!table2)
    {
        return;
    }

    // clear page table
    memset (table, 0, sizeof (ptable));

    // 1st 4mb are idenitity mapped
    for (int i=0, frame=0x00000000, virt=0x00000000; i<1024; i++, frame+=4096, virt+=4096)
    {
        // create a new page
        pt_entry page=0;
        pt_entry_add_attrib (&page, PTE_PRESENT);
        pt_entry_set_frame (&page, frame);

        // ...and add it to the page table
        table->m_entries[PAGE_TABLE_INDEX(virt)] = page;
    }

    // map 1mb to 3gb (where we are at)
    for (int i=0, frame=0x00000000, virt=0xc0000000; i<1024; i++, frame+=4096, virt+=4096)
    {

        // create a new page
        pt_entry page=0;
        pt_entry_add_attrib (&page, PTE_PRESENT);
        pt_entry_set_frame (&page, frame);

        // ...and add it to the page table
        table2->m_entries [PAGE_TABLE_INDEX (virt) ] = page;
    }

    // create default directory table
    pdirectory* dir = (pdirectory*) pmmngr_alloc_blocks (3);
    if (!dir)
    {
        return;
    }

    // clear directory table and set it as current
    memset (dir, 0, sizeof (pdirectory));

    // get first entry in dir table and set it up to point to ourtable
    pd_entry* entry = &dir->m_entries [PAGE_DIRECTORY_INDEX (0x00000000)];
    pd_entry_add_attrib (entry, PDE_PRESENT);
    pd_entry_add_attrib (entry, PDE_WRITABLE);
    pd_entry_set_frame (entry, (phys_addr)table);

    pd_entry* entry2 = &dir->m_entries [PAGE_DIRECTORY_INDEX (0xC0000000) ];
    pd_entry_add_attrib (entry2, PDE_PRESENT);
    pd_entry_add_attrib (entry2, PDE_WRITABLE);
    pd_entry_set_frame (entry2, (phys_addr)table2);

    // store current PDBR
    _cur_pdbr = (phys_addr) &dir->m_entries;

    // switch to our page directory
    vmmngr_switch_pdirectory (dir);

    // enable paging
    pmmngr_paging_enable (1);
}

int vmmngr_alloc_page (pt_entry* e)
{
    void* p = pmmngr_alloc_block();

    if (!p)
        return 0;

    pt_entry_set_frame (e, (phys_addr)p);
    pt_entry_add_attrib (e, PTE_PRESENT);

    return 1;
}

void vmmngr_free_page (pt_entry* e)
{
    void* p = (void*)pt_entry_pfn (*e);

    if (p)
        pmmngr_free_block (p);

    pt_entry_del_attrib (e, PTE_PRESENT);
}

int vmmngr_switch_pdirectory (pdirectory* dir)
{
    if(!dir)
        return 0;

    _cur_directory = dir;

    printf("[VIRTMEM] Cur. PDBR: %#010p\n", _cur_pdbr);

    pmmngr_load_PBDR(_cur_pdbr);

    return 1;
}

pdirectory* vmmngr_get_directory ()
{
    return _cur_directory;
}

void vmmngr_flush_tlb_entry (virt_addr addr)
{
    asm volatile ("cli");
    asm volatile ("invlpg (%0)" ::"b"(addr): "memory");
    asm volatile ("sti");
}

void vmmngr_ptable_clear (ptable* p)
{
    if (p)
        memset(p, 0, sizeof(ptable));
}

uint32_t vmmngr_ptable_virt_to_index (virt_addr addr)
{

    //! return index only if address doesnt exceed page table address space size
    return (addr >= PTABLE_ADDR_SPACE_SIZE) ? 0 : addr / PAGE_SIZE;
}

pt_entry* vmmngr_ptable_lookup_entry (ptable* p, virt_addr addr)
{
    if(p)
        return &p->m_entries[PAGE_TABLE_INDEX(addr)];
    return 0;
}

uint32_t vmmngr_pdirectory_virt_to_index (virt_addr addr)
{
    //! return index only if address doesnt exceed 4gb (page directory address space size)
    return (addr >= DTABLE_ADDR_SPACE_SIZE) ? 0 : addr / PAGE_SIZE;
}

void vmmngr_pdirectory_clear (pdirectory* dir)
{
    if (dir)
        memset(dir, 0, sizeof(pdirectory));
}

pd_entry* vmmngr_pdirectory_lookup_entry (pdirectory* p, virt_addr addr)
{
    if(p)
        &p->m_entries[PAGE_TABLE_INDEX(addr)];
    return 0;
}

int vmmngr_createPageTable(pdirectory* dir, uint32_t virt, uint32_t flags)
{
    pd_entry* pagedir = dir->m_entries;

    if (pagedir[virt >> 22] == 0)
    {
        void* block = pmmngr_alloc_block();
        if (!block)
            return 0; /* Should call debugger */
        pagedir[virt >> 22] = ((uint32_t)block) | flags;
        memset((uint32_t*)pagedir[virt >> 22], 0, 4096);

        /* map page table into directory */
        vmmngr_mapPhysicalAddress(dir, (uint32_t)block, (uint32_t)block, flags);
    }
    return 1; /* success */
}

void vmmngr_mapPhysicalAddress(pdirectory* dir, uint32_t virt, uint32_t phys, uint32_t flags)
{
    pd_entry* pagedir = dir->m_entries;
    if (pagedir[virt >> 22] == 0)
        vmmngr_createPageTable(dir, virt, flags);
    ((uint32_t*)(pagedir[virt >> 22] & ~0xfff))[virt << 10 >> 10 >> 12] = phys | flags;
}

void vmmngr_unmapPageTable(pdirectory* dir, uint32_t virt)
{
    pd_entry* pagedir = dir->m_entries;
    if (pagedir[virt >> 22] != 0) {

        /* get mapped frame */
        void* frame = (void*)(pagedir[virt >> 22] & 0x7FFFF000);

        /* unmap frame */
        pmmngr_free_block(frame);
        pagedir[virt >> 22] = 0;
    }
}

void vmmngr_unmapPhysicalAddress(pdirectory* dir, uint32_t virt)
{
    /* note: we don't unallocate physical address here; callee does that */
    pd_entry* pagedir = dir->m_entries;
    if (pagedir[virt >> 22] != 0)
        vmmngr_unmapPageTable(dir, virt);
    //      ((uint32_t*) (pagedir[virt >> 22] & ~0xfff))[virt << 10 >> 10 >> 12] = 0;
}

pdirectory* vmmngr_createAddressSpace()
{
    pdirectory* dir = 0;

    /* allocate page directory */
    dir = (pdirectory*)pmmngr_alloc_block();
    if (!dir)
        return 0;

    /* clear memory (marks all page tables as not present) */
    memset(dir, 0, sizeof(pdirectory));
    return dir;
}

pdirectory* vmmngr_cloneAddressSpace()
{
    pdirectory* dir = vmmngr_createAddressSpace();

    pdirectory* current = vmmngr_get_directory();

    memcpy(&dir->m_entries[768], &current->m_entries[768], 256*sizeof(pd_entry));

    return dir;
}

void* vmmngr_getPhysicalAddress(pdirectory* dir, uint32_t virt)
{
    pd_entry* pagedir = dir->m_entries;
    if (pagedir[virt >> 22] == 0)
        return 0;
    return (void*)((uint32_t*)(pagedir[virt >> 22] & ~0xfff))[virt << 10 >> 10 >> 12];
}

//==============================================================================
// Dynamic Memory Manager
//==============================================================================

#define PLACEMENT_BEGIN 0xD0000000U
#define PLACEMENT_END 0xD0200000U

#define KERNEL_HEAP_START 0xD0200000U
#define KERNEL_HEAP_END 0xE0000000U

#define PAGE_SIZE 4096U

typedef struct
{
    uint32_t size;
    uint32_t number;
    uint8_t reserved;
} __attribute__((packed)) region_t;

static region_t* regions = 0;
static uint32_t regionCount = 0;
static uint32_t regionMaxCount = 0;
static uint32_t firstFreeRegion = 0;
static void* firstFreeAddr = (void*)KERNEL_HEAP_START;
static const uint8_t* HEAP_START = (const uint8_t*)KERNEL_HEAP_START;
static uint32_t heapSize = 0;
static const uint32_t HEAP_MIN_GROWTH = 0x10000;

uint32_t alignUp(uint32_t val, uint32_t alignment);
uint32_t alignDown(uint32_t val, uint32_t alignment);
void* pmalloc(size_t size, uint32_t alignment);
int heap_grow(size_t size, uint8_t* heapEnd, int continuous);
void* kmalloc_imp(size_t size, uint32_t alignment);


uint32_t alignUp(uint32_t val, uint32_t alignment)
{
    if(!alignment)
    {
        return val;
    }

    --alignment;

    return (val + alignment) & ~alignment;
}

uint32_t alignDown(uint32_t val, uint32_t alignment)
{
    if(!alignment)
    {
        return val;
    }

    return val & ~(alignment - 1);
}

void* pmalloc(size_t size, uint32_t alignment)
{
    static uint8_t* nextPlacement = (uint8_t*)PLACEMENT_BEGIN;

    size = alignUp(size, 4);

    uint8_t* currPlacement = (uint8_t*) alignUp((uint32_t) nextPlacement, alignment);

    if(((uint32_t)currPlacement + size) > PLACEMENT_END)
    {
        return 0;
    }

    nextPlacement = currPlacement + size;


    return (void*) currPlacement;
    
}

int heap_grow(size_t size, uint8_t* heapEnd, int continuous)
{
    if((regionCount > 0) && regions[regionCount - 1].reserved && (regionCount >= regionMaxCount))
    {
        return 0;
    }

    uint32_t offset = 0;

    while(offset < size)
    {
        phys_addr addr = pmmngr_alloc_block();

        vmmngr_mapPhysicalAddress(
            vmmngr_get_directory(),
            (uint32_t)heapEnd + offset,
            (uint32_t)addr,
            PTE_PRESENT | PTE_WRITABLE);

        offset += PAGE_SIZE;
    }

    if((regionCount > 0) && !regions[regionCount - 1].reserved)
    {
        regions[regionCount - 1].size += size;
    }
    else
    {
        regions[regionCount].reserved = 0;
        regions[regionCount].size = size;
        regions[regionCount].number = 0;

        ++regionCount;
    }

    heapSize += size;

    return 1;
}

#define mm_max(A, B) (((A) > (B)) ? (A): (B))

void* kmalloc_imp(size_t size, uint32_t alignment)
{
    static uint32_t consecutiveNumber = 0;

    size_t within = 0xFFFFFFFF;

    if(alignment & HEAP_WITHIN_PAGE)
    {
        within = PAGE_SIZE;
    }
    else if(alignment & HEAP_WITHIN_64K)
    {
        within = 0x10000;
    }

    int continuous = (alignment & HEAP_CONTINUOUS) ? 1 : 0;

    alignment &= HEAP_ALIGNMENT_MASK;

    if(regions == 0)
    {
        return pmalloc(size, alignment);
    }

    size = alignUp(size, 0);

    int foundFree = 0;

    uint8_t* regionAddress = (uint8_t*) firstFreeAddr;

    for(uint32_t i = firstFreeRegion; i < regionCount; ++i)
    {
        if(regions[i].reserved)
        {
            foundFree = 1;
        }
        else if(!foundFree)
        {
            firstFreeRegion = i;
            firstFreeAddr = regionAddress;
        }

        uint8_t* alignedAddress = (uint8_t*)alignUp((uintptr_t) regionAddress, alignment);
        uintptr_t additionalSize = (uintptr_t) alignedAddress - (uintptr_t)regionAddress;

        if(!regions[i].reserved && (regions[i].size >= size + additionalSize) &&
           (within - (uintptr_t)regionAddress % within >= additionalSize))
        {
            if(continuous)
            {
                int iscontinuous = 1;

                for(uint32_t virt1 = (uint32_t) alignDown((uintptr_t)alignedAddress, PAGE_SIZE);
                    (uintptr_t)((uint32_t)virt1 + PAGE_SIZE) <=
                        (uintptr_t)(alignedAddress + size);
                    virt1 += PAGE_SIZE)
                {
                    uintptr_t phys1 = (uintptr_t) vmmngr_getPhysicalAddress(
                        vmmngr_get_directory(),
                        (uint32_t)virt1);
                    
                    uintptr_t phys2 = (uintptr_t) vmmngr_getPhysicalAddress(
                        vmmngr_get_directory(),
                        (uint32_t)virt1 + PAGE_SIZE);

                    if(phys1 + PAGE_SIZE != phys2)
                    {
                        iscontinuous = 0;
                        break;
                    }
                }
                
                if(!iscontinuous)
                {
                    continue;
                }
                    
            }

            if(alignedAddress != regionAddress)
            {
                if(regionCount >= regionMaxCount)
                {
                    return 0;
                }

                memmove(regions + i + 1, regions + i, (regionCount - i) * sizeof(region_t));

                ++regionCount;

                regions[i].size = alignedAddress - regionAddress;

                regions[i].reserved = 0;

                regions[i + 1].size -= regions[i].size;

                regionAddress += regions[i].size;

                ++i;
            }

            if(regions[i].size > size + additionalSize)
            {
                if(regionCount + 1 > regionMaxCount)
                {
                    return 0;
                }

                memmove(
                    regions + i + 2,
                    regions + i + 1,
                    (regionCount - i - 1) * sizeof(region_t));

                ++regionCount;

                regions[i + 1].size = regions[i].size - size;
                regions[i + 1].reserved = 0;
                regions[i + 1].number = 0;

                regions[i].size = size;
            }

            regions[i].reserved = 1;
            regions[i].number = ++consecutiveNumber;

            return (regionAddress);
        }

        regionAddress += regions[i].size;
    }

    uint32_t sizeToGrow = mm_max(HEAP_MIN_GROWTH, alignUp(size * 3 / 2, PAGE_SIZE));

    int success = heap_grow(
        sizeToGrow,
        (uint8_t*)((uintptr_t)HEAP_START + heapSize),
        continuous);

    if(!success)
    {
        return 0;
    }

    return kmalloc_imp(size, alignment);
}

void* heap_get_current_end()
{
    return (void*)(HEAP_START + heapSize);
}

void init_kernel_heap()
{
    uint32_t i = PLACEMENT_BEGIN;

    for(i; i < PLACEMENT_END; i += PAGE_SIZE)
    {
        vmmngr_mapPhysicalAddress(
            vmmngr_get_directory(),
            i,
            (uint32_t)pmmngr_alloc_block(),
            PTE_PRESENT | PTE_WRITABLE);
    }

    regions = (region_t*)pmalloc(0,0);

    regionCount = 0;
    regionMaxCount = (PLACEMENT_END - (uint32_t)regions) / sizeof(region_t);
}

void* kernel_malloc(size_t size)
{
    return kmalloc_imp(size, 0);
}

void* kernel_malloc_a(size_t size, uint32_t alignment)
{
    return kmalloc_imp(size, alignment);
}

void kernel_free(void* addr)
{
    if(!addr)
    {
        return;
    }

    uint8_t* regionAddress = (uint8_t*) HEAP_START;

    for(uint32_t i = 0; i < regionCount; ++i)
    {
        if(regionAddress == addr && regions[i].reserved)
        {
            regions[i].number = 0;
            regions[i].reserved = 0;

            if(((i + 1) < regionCount) && !regions[i + 1].reserved)
            {
                regions[i].size += regions[i + 1].size;

                memmove(regions + i + 1,
                        regions + i + 2,
                        (regionCount - 2) * sizeof(region_t));

                --regionCount;
            }

            if(i > 0 && !regions[i - 1].reserved)
            {
                regions[i - 1].size += regions[i].size;

                memmove(regions + i,
                        regions + i + 1,
                        (regionCount - 1 - i) * sizeof(region_t));

                --regionCount;
            }

            if(i < firstFreeRegion)
            {
                firstFreeRegion = i;
                firstFreeAddr = regionAddress;
            }

            return;
        }

        regionAddress += regions[i].size;
    }
}

