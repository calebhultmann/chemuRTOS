extern int main(void);

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

void reset_handler(void) {
    copy_data();
    clear_bss();
    
    main();

    while(1);
}

void hard_fault_handler(void) {
    while(1);
}

#define IVT_ARRAY_SIZE (16U)
typedef void (*isr_t)(void);
__attribute((used, section(".ivt"))) // used is for compiler not optimizing it away
static const isr_t ivt[IVT_ARRAY_SIZE] = 
{
    (isr_t)&_stack,
    reset_handler,
    0, // NMI
    hard_fault_handler,

    // common practice ohterwise is to give these a default handler and attribute them weak
    // todo: learn wtf that means
};