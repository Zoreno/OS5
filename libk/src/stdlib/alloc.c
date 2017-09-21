/**
 * @file    alloc.c
 * @author  Joakim Bertils
 * @date    2017-09-21
 * @brief   Memory allocation
 */

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

extern void* kernel_malloc(size_t size);
extern void kernel_free(void* addr);

void* calloc(size_t nitems, size_t size)
{
    void* mem = kernel_malloc(nitems * size);

    if(mem)
    {
        memset(mem, 0, nitems * size);
    }

    return mem;
}

void free(void* ptr)
{
    kernel_free(ptr);
}

void* malloc(size_t size)
{
    return kernel_malloc(size);
}

