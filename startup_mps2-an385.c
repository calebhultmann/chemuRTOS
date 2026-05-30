#include <stdint.h>
#include "mps2-an385.h"


// Note: This is a system-specific setup file. Determine if any of this
// is non-system-specific and can be moved to a generic startup file


extern int main(void);
extern void __libc_init_array(void);

// Symbols defined by the linker script
extern unsigned int _stack;
extern unsigned int _idata;
extern unsigned int _data;
extern unsigned int _edata;
extern unsigned int _bss;
extern unsigned int _ebss;

static void copy_data(void) {
    unsigned int *src_data_ptr = &_idata;
    unsigned int *dst_data_ptr = &_data;
    while (dst_data_ptr < &_edata) {
        *dst_data_ptr++ = *src_data_ptr++;
    }
}

static void clear_bss(void) {
    unsigned int *bss_ptr = &_bss;
    while (bss_ptr < &_ebss) {
        *bss_ptr++ = 0;
    }
}

// TODO: Move this definition to a common.h file
#define SYSTICK_HZ 1000

void systick_init(uint32_t cpu_hz) {
    SysTick->LOAD = (cpu_hz / SYSTICK_HZ) - 1; // Configure RVR
    SysTick->VAL = 0;                          // Zero CVR

    SysTick->CTRL =
        (1 << 2) | // CLKSOURCE = CPU Clock
        (1 << 1) | // TICKINT   = Enable interrupts
        (1 << 0);  // ENABLE    = Start counter
}

void system_init(void) {
    systick_init(CPU_CLOCK_HZ);
}

// Normally provided by Newlib's runtime file crti.o, but we compile without
// (-nostartfiles) Inserted by __libc_init_array because newlib was compiled with
// _HAVE_INIT_FINI. We don't need it, so add an empty stub
void _init(void) {}

void reset_handler(void) {
    system_init();
    
    copy_data();
    clear_bss();
    
    __libc_init_array();

    main();

    // For a more feature-rich C runtime, you may link with the C runtime files
    // files (crt0.o, crti.o...) from Newlib. To do so, remove "-nostartfiles"
    // and replace __libc_init_array() and main() with a call to _start().
    // The runtime files from Newlib includes semi-hosting, profiling,
    // transactional memory, function hooks, and so on. Note, this will likely
    // require some additions in the linker script as well.
    // _start();

    while(1);
}

void hard_fault_handler(void) {
    while(1);
}

volatile uint64_t ticks = 0;
void systick_handler(void) {
    ticks++;
    // scheduler_tick();
}

static void default_handler(void) {
    while(1);
}

typedef void (*isr_t)(void);
__attribute((used, section(".ivt"))) // used is for compiler not optimizing it away
static const isr_t ivt[IVT_ARRAY_SIZE] = 
{
    (isr_t)&_stack,
    reset_handler,
    default_handler, // NMI
    hard_fault_handler,
    default_handler, // Mem management
    default_handler, // bus fault
    default_handler, // usage fault
    0, 0, 0, 0, // reserved
    default_handler, // svcall
    0, 0, //reserved
    default_handler, //pendsv
    systick_handler
};