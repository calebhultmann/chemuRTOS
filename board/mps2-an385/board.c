#include "board_api.h"

#include <stdint.h>

#include "board.h"

uint32_t board_cpu_hz(void) {
    return CPU_CLOCK_HZ;
}