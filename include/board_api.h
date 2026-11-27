#ifndef BOARD_API_H
#define BOARD_API_H

#include <stdint.h>

// Clocks, UART pins, anything board-specific
void board_init(void);

// Returns the CPU clock rate of the board
uint32_t board_cpu_hz(void);

#endif