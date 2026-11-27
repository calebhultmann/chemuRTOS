#include "arch_api.h"
#include "board_api.h"

#include "config.h"

void scheduler_start(void) {
    arch_systick_init(board_cpu_hz(), SYSTICK_HZ);
}

void kernel_tick(void) {
    // Pause current task
    // resume next ready task
    // pend pendsv
}