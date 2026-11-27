#include "kernel_port.h"

void hard_fault_handler(void) {
    while(1);
}

void systick_handler(void) {
    kernel_tick();
}

void default_handler(void) {
    while(1);
}