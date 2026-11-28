#include "board_api.h"

#include "uart.h"
#include "board.h"

void board_uart_init(void) {
    UART0->BAUDDIV = CPU_CLOCK_HZ / 115200u;
    UART0->CTRL = 1;
}

void board_putc(char c) {
    if (c == '\n') {
        while (UART0->STATE & UART_STATE_TXFULL) {}
        UART0->DATA = (uint32_t)(uint8_t)'\r';
    }

    while (UART0->STATE & UART_STATE_TXFULL) {}

    UART0->DATA = (uint32_t)(uint8_t)c;
}