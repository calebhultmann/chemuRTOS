#include "board_api.h"

#include <stdarg.h>
#include <stdint.h>

#include "kprintf.h"

void kputc(char c) {
    board_putc(c);
}

void kputs(const char *s) {
    while (*s) {
        kputc(*s);
        s++;
    }
}

// void kprint_int(int32_t num, int base) {
//     if (num == 0) {
//         kputc('0');
//         return;
//     }

//     if (num < 0 && base == 10) {
//         kputc('-');
//         num = -num;
//     }
//     while (uval > 0) {
//         buf[i++] = digits[uval % base];
//         uval /= base;
//     }
// }


void kprintf(const char *fmt, ...) {
    va_list args;
    va_start (args, fmt);

    for (const char *p = fmt; *p != '\0'; p++) {
        if (*p != '%') {
            kputc(*p);
            continue;
        }

        p++;
        
        /*  %f / %lf — floating-point / double
            %p — pointer address */
        switch (*p) {
            case 's':
                kputs(va_arg(args, char*));
                break;
            case 'u':
                // %u - unsigned decimal integer
                // kprint_uint(va_arg(args, uint32_t))
                break;
            case 'd':
            case 'i':
                // kprint_int(va_arg(args, int32_t), 10)
                break;
            case 'x':
                // %x - hexadecimal integer (lowercase)
                // kprint_int(va_arg(args, uint32_t), 16);
                break;
            case 'X':
                // %X - hexadecimal integer (uppercase)
                // kprint_int(va_arg(args, uint32_t), 16);
                break;
            case 'c':
                kputc((char)va_arg(args, int));
                break;
        }
    }
}