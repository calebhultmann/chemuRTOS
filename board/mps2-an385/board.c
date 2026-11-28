#include "board_api.h"

#include <stdint.h>

#include "board.h"
#include "uart.h"

uint32_t board_cpu_hz(void) {
    return CPU_CLOCK_HZ;
}

void board_init(void) {
    board_uart_init();
}