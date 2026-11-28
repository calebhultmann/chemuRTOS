#include <stdint.h>

void kputc(char c);
void kputs(const char *c);

// void kprint_int(int32_t num, int base)
void kprintf(const char *fmt, ...);