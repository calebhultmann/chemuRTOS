#include <stdint.h>
#include "board.h"
#include "arch.h"

void system_init(void) {
    systick_init(CPU_CLOCK_HZ);
    systick_start(); // This should occur AFTER tasks have been created
}