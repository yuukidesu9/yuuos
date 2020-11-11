#include "timer.h"
#include "isr.h"
#include "ports.h"
#include "../libc/function.h"

u32 tick = 0;

static void timer_callback(registers_t regs) {
    tick++;
    UNUSED(regs);
}

void init_timer(u32 freq) {
    /* Install the function we just wrote */
    register_interrupt_handler(IRQ0, timer_callback);

    // Get the PIT value: hardware clock at 1193180 Hz
    u32 divisor = 1193180 / freq;
    u8 low  = (u8)(divisor & 0xFF);
    u8 high = (u8)( (divisor >> 8) & 0xFF);
    // Send the command through port 0x43.
    outb(0x43, 0x36);
    outb(0x40, low);
    outb(0x40, high);
}

