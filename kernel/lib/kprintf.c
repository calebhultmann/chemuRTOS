#include "board_api.h"

#include <stdarg.h>

#include "kprintf.h"

void kputc(char c) {
    board_putc(c);
}

void kprintf(const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);

    for (const char *p = fmt; *p != '\0'; p++) {
        if (*p != %) {
            kputc(*p);
            continue;
        }

        p++;
        
        switch (*p) {
            case 's':
                break;
            case 'u':
                break;
            case 'x':
                break;
            case 'c':
                kputc(va_arg(args, char));
                break;
        }
    }
}