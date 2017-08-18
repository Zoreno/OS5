#include <memory_manager.h>

//==============================================================================
// Physical Memory Manager
//==============================================================================

#define PMMNGR_BLOCKS_PER_BYTE 8
#define PMMNGR_BLOCK_SIZE 4096
#define PMMNGR_BLOCK_ALIGN PMMNGR_BLOCK_SIZE

static uint32_t _pmmngr_memory_size = 0;
static uint32_t _pmmngr_used_blocks = 0;
static uint32_t _pmmngr_max_blocks = 0;
static uint32_t* _pmmngr_memory_map = 0;

void mmap_set(int bit);
void mmap_unset(int bit);
int mmap_test(int bit);

size_t mmap_first_free();
size_t mmap_first_free_n(size_t n);

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
		++entry){

		// If the entry is full, go to the next one
		if(_pmmngr_memory_map[entry] == 0xFFFFFFFF)
			continue;

		// Check each bit in the entry
		for(int bit = 0; bit < BITS_PER_ENTRY;  ++bit){
			if(!(_pmmngr_memory_map[entry] & (1<<bit))){
				return entry * BITS_PER_ENTRY + bit;
			}
		}
	}

	return -1;
}

size_t mmap_first_free_n(size_t n)
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
	for(int bit = firstFree; bit < pmmngr_get_block_count(); ++bit){
		// If bit is set (memory not free)
		if(mmap_test(bit)){
			// Reset counter
			free = 0;

			// Next bit is potential new start of chain.
			first_bit_in_chain = bit + 1;
		} else {
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
    _pmmngr_max_blocks = (pmmngr_get_block_count() * 1024)/ PMMNGR_BLOCK_SIZE;
    _pmmngr_used_blocks = _pmmngr_max_blocks;

    printf("PMM Bitmap Size: %i\n", pmmngr_get_block_count() / PMMNGR_BLOCKS_PER_BYTE);
    
    int entries = pmmngr_get_block_count() / BITS_PER_ENTRY;

    for(int i = 0; i < entries; ++i)
    {
        _pmmngr_memory_map[i] = 0xFFFFFFFF;
    }
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
    
}

void* pmmngr_alloc_block_z(void)
{
    
}

void pmmngr_free_block(void* addr)
{
    
}

void* pmmngr_alloc_blocks(size_t size)
{
    
}

void* pmmngr_alloc_blocks_z(size_t size)
{
    
}

void pmmngr_free_blocks(size_t size)
{
    
}

size_t pmmngr_get_memory_size()
{
    
}

uint32_t pmmngr_get_block_count()
{
    
}

uint32_t pmmngr_get_used_block_count()
{
    
}

uint32_t pmmngr_get_free_block_count()
{
    
}

uint32_t pmmngr_get_block_size();
{
    
}

void pmmngr_paging_enable(int b);
{
    
}

int pmmngr_is_paging()
{
    
}

void pmmngr_load_PBDR(phys_addr addr);
{
    
}

phys_addr pmmngr_get_PBDR()
{
    
}

//==============================================================================
// Virtual Memory Manager
//==============================================================================

//==============================================================================
// Dynamic Memory Manager
//==============================================================================
