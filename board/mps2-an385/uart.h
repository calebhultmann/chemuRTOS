#ifndef CHEMU_UART_H
#define CHEMU_UART_H

#include <stdint.h>

// DATA      - Data Value
//              [7:0] Data value.
//              Read Received data.
//              Write Transmit data.
// STATE     - TX/RX Buffer
//              [3] RX buffer overrun, write 1 to clear.
//              [2] TX buffer overrun, write 1 to clear.
//              [1] RX buffer full, read-only.
//              [0] TX buffer full, read-only.
// CTRL      - TX/RX Enable
//              [6] High-speed test mode for TX only.
//              [5] RX overrun interrupt enable.
//              [4] TX overrun interrupt enable.
//              [3] RX interrupt enable.
//              [2] TX interrupt enable.
//              [1] RX enable.
//              [0] TX enable.
// INTSTATUS - TX/RX Interrupt
//              [3] RX overrun interrupt. Write 1 to clear.
//              [2] TX overrun interrupt. Write 1 to clear.
//              [1] RX interrupt. Write 1 to clear.
//              [0] TX interrupt. Write 1 to clear.
// BAUDDIV   - Baud Rate Divider
//              [19:0] The minimum value is 16.
typedef struct {
    volatile uint32_t DATA;
    volatile uint32_t STATE;
    volatile uint32_t CTRL;
    volatile uint32_t INTSTATUS;
    volatile uint32_t BAUDDIV;
} UART_Registers;

#define UART0_BASE 0x40004000
#define UART1_BASE 0x40005000
#define UART2_BASE 0x40006000
#define UART3_BASE 0x40007000
#define UART4_BASE 0x40009000

#define UART0 ((UART_Registers*)UART0_BASE)
#define UART1 ((UART_Registers*)UART1_BASE)
#define UART2 ((UART_Registers*)UART2_BASE)
#define UART3 ((UART_Registers*)UART3_BASE)
#define UART4 ((UART_Registers*)UART4_BASE)

#define UART_STATE_TXFULL 1

void board_uart_init(void);
void board_putc(char c);

#endif