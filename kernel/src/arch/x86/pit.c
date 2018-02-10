#include <arch/x86/pit.h>

#define ARCH_X86_PIT_REG_COUNTER0 0x40
#define ARCH_X86_PIT_REG_COUNTER1 0x41
#define ARCH_X86_PIT_REG_COUNTER2 0x42
#define ARCH_X86_PIT_REG_COMMAND  0x43

static volatile uint32_t _pit_ticks = 0;
static int _is_initialized = 0;

static on_tick_handler_func _on_tick_handler = NULL;

void pit_irq();

void arch_x86_set_on_tick_handler(on_tick_handler_func on_tick_handler)
{
    _on_tick_handler = on_tick_handler;
}

void pit_irq()
{
    ++_pit_ticks;

    if(_on_tick_handler)
    {
        _on_tick_handler();
    }
}

void arch_x86_pit_send_command(uint8_t cmd)
{
    outportb(ARCH_X86_PIT_REG_COMMAND, cmd);
}

void arch_x86_pit_send_data(uint16_t counter, uint8_t data)
{
    uint8_t port = 0;

    switch(counter)
    {
    case ARCH_X86_PIT_OCW_COUNTER_0:
        port = ARCH_X86_PIT_REG_COUNTER0;
        break;
    case ARCH_X86_PIT_OCW_COUNTER_1:
        port = ARCH_X86_PIT_REG_COUNTER1;
        break;
    case ARCH_X86_PIT_OCW_COUNTER_2:
        port = ARCH_X86_PIT_REG_COUNTER2;
        break;

    default:
        // ERROR: Invalid counter
        break;
    }

    outportb(port, data);
}

uint8_t arch_x86_pit_read_data(uint16_t counter)
{
    uint8_t port = 0;

    switch(counter)
    {
    case ARCH_X86_PIT_OCW_COUNTER_0:
        port = ARCH_X86_PIT_REG_COUNTER0;
        break;
    case ARCH_X86_PIT_OCW_COUNTER_1:
        port = ARCH_X86_PIT_REG_COUNTER1;
        break;
    case ARCH_X86_PIT_OCW_COUNTER_2:
        port = ARCH_X86_PIT_REG_COUNTER2;
        break;

    default:
        // ERROR: Invalid counter
        break;
    }

    return inportb(port);
}

uint32_t arch_x86_pit_set_tick_count(uint32_t i)
{
    uint32_t old_val = _pit_ticks;
    _pit_ticks = i;
    return old_val;
}

uint32_t arch_x86_pit_get_tick_count()
{
    return _pit_ticks;
}

void arch_x86_pit_start_counter(uint32_t freq, uint8_t counter, uint8_t mode)
{
    if(freq == 0)
        return;

    uint32_t divisor = (uint16_t)(1193181/(uint16_t)freq);

    uint8_t ocw = 0;

    ocw = (ocw & ARCH_X86_PIT_OCW_MASK_MODE) | mode;
    ocw = (ocw & ARCH_X86_PIT_OCW_MASK_RL) | ARCH_X86_PIT_OCW_RL_DATA;
    ocw = (ocw & ARCH_X86_PIT_OCW_MASK_COUNTER) | counter;

    arch_x86_pit_send_command(ocw);

    arch_x86_pit_send_data(0, divisor & 0xFF);
    arch_x86_pit_send_data(0, (divisor >> 8) & 0xFF);

    _pit_ticks = 0;
}

extern void pit_irq_handler(void);

void arch_x86_pit_initialize()
{
    setvect(32, pit_irq_handler, 0);

    _is_initialized = 0;
}

int arch_X86_pit_is_initialzed()
{
    return _is_initialized;
}
