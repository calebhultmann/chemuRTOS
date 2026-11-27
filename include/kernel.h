#ifndef CHEMU_KERNEL_H
#define CHEMU_KERNEL_H

#include <stdint.h>

void scheduler_start(void);
uint32_t create_task(void (*entry)(void *), void *args, const char *name);

#endif