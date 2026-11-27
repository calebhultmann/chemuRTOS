#ifndef ARCH_API_H
#define ARCH_API_H

#include <stdint.h>

void arch_systick_init(uint32_t cpu_hz, uint32_t tick_hz);
void arch_systick_start(void);

#endif