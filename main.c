#include "kernel_port.h"

volatile int dummy_data = 1;  // forces a .data symbol
volatile int dummy_bss;       // forces a .bss symbol

int main(void) {
    // create_task(1);
    // create_task(2);
    // create_task(3);
    scheduler_start();
    return 0;
}