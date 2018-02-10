#ifndef _ARCH_X86_PIT_H
#define _ARCH_X86_PIT_H

#include <stdint.h>
#include <arch/arch.h>
#include <_null.h>

#define ARCH_X86_PIT_OCW_MASK_BINCOUNT      1
#define ARCH_X86_PIT_OCW_MASK_MODE          0xE
#define ARCH_X86_PIT_OCW_MASK_RL            0x30
#define ARCH_X86_PIT_OCW_MASK_COUNTER       0xC0

#define ARCH_X86_PIT_OCW_BINCOUNT_BINARY    0
#define ARCH_X86_PIT_OCW_BINCOUNT_BCD       1

#define ARCH_X86_PIT_OCW_MODE_TERMINALCOUNT 0
#define ARCH_X86_PIT_OCW_MODE_ONESHOT       0x2
#define ARCH_X86_PIT_OCW_MODE_RATEGEN       0x4
#define ARCH_X86_PIT_OCW_MODE_SQUAREWAVEGEN 0x6
#define ARCH_X86_PIT_OCW_MODE_SOFTWARETRIG  0x8
#define ARCH_X86_PIT_OCW_MODE_HARDWARETRIG  0xA

#define ARCH_X86_PIT_OCW_RL_LATCH           0
#define ARCH_X86_PIT_OCW_RL_LSBONLY         0x10
#define ARCH_X86_PIT_OCW_RL_MSBONLY         0x20
#define ARCH_X86_PIT_OCW_RL_DATA            0x30

#define ARCH_X86_PIT_OCW_COUNTER_0          0
#define ARCH_X86_PIT_OCW_COUNTER_1          0x40
#define ARCH_X86_PIT_OCW_COUNTER_2          0x80

void arch_x86_set_on_tick_handler(on_tick_handler_func on_tick_handler);
void arch_x86_pit_send_command(uint8_t cmd);
void arch_x86_pit_send_data(uint16_t counter, uint8_t data);
uint8_t arch_x86_pit_read_data(uint16_t counter);
uint32_t arch_x86_pit_set_tick_count(uint32_t i);
uint32_t arch_x86_pit_get_tick_count();
void arch_x86_pit_start_counter(uint32_t freq, uint8_t counter, uint8_t mode);
void arch_x86_pit_initialize();
int arch_X86_pit_is_initialzed();

#endif
