#define IVT_ARRAY_SIZE (16U)
extern unsigned int _stack;

// Forward declarations of exception handlers to suppress compiler warnings
void reset_handler(void);
void hard_fault_handler(void);
void default_handler(void);
void systick_handler(void);

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