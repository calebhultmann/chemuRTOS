#include "uart.h"
#include "board.h"

void board_uart_init(void) {
    // set BAUDDIV
    UART0->BAUDDIV = CPU_CLOCK_HZ / 115200u;
    UART0->CTRL = 1;
}

void board_putc(char c) {
    
}