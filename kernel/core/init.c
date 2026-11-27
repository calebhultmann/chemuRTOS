#include "config.h"
#include "kernel_port.h"

void scheduler_start(void) {
    arch_systick_init(board_cpu_hz(), SYSTICK_HZ);
}