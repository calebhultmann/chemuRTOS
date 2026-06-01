#include <stdint.h>
#include "board.h"
#include "arch.h"

void systick_init(uint32_t cpu_hz) {
    SysTick->LOAD = (cpu_hz / SYSTICK_HZ) - 1; // Configure RVR
    SysTick->VAL = 0;                          // Zero CVR

    SysTick->CTRL =
        (1 << 2) | // CLKSOURCE = CPU Clock
        (1 << 1) | // TICKINT   = Enable interrupts
        (1 << 0);  // ENABLE    = Start counter
}

void system_init(void) {
    systick_init(CPU_CLOCK_HZ);
}