#include "arch_api.h"

#include <stdint.h>

#include "arch.h"

void arch_systick_init(uint32_t cpu_hz, uint32_t tick_hz) {
    SysTick->LOAD = (cpu_hz / tick_hz) - 1; // Configure RVR
    SysTick->VAL = 0;                          // Zero CVR
}

void arch_systick_start(void) {
    SysTick->CTRL =
        (1 << 2) | // CLKSOURCE = CPU Clock
        (1 << 1) | // TICKINT   = Enable interrupts
        (1 << 0);  // ENABLE    = Start counter
}