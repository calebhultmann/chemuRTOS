#include <stdint.h>
extern void scheduler_tick(void);

void hard_fault_handler(void) {
    while(1);
}

volatile uint64_t ticks = 0;
void systick_handler(void) {
    ticks++;
    scheduler_tick();
}

void default_handler(void) {
    while(1);
}