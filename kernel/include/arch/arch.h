#ifndef _ARCH_H
#define _ARCH_H

#include <stdint.h>

#include <arch/x86/idt.h>

#define ARCH_X86

typedef void(*on_tick_handler_func)(void);

void arch_initialize();
void arch_shutdown();

uint8_t inportb(uint16_t port);
uint16_t inportw(uint16_t port);
uint32_t inportl(uint16_t port);

void outportb(uint16_t port, uint8_t value);
void outportw(uint16_t port, uint16_t value);
void outportl(uint16_t port, uint32_t value);

void enable_interrupts();
void disable_interrupts();

void interrupt_done(uint32_t intno);

void setvect(int intno, IRQ_HANDLER vect, int flags);

uint32_t get_tick_count();

void set_on_tick_handler(on_tick_handler_func on_tick_handler);

#endif
