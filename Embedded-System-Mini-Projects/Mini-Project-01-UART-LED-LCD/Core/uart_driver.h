#ifndef UART_DRIVER_H
#define UART_DRIVER_H

void uart0_init(unsigned int baud);
void uart0_tx(unsigned char data);
unsigned char uart0_rx(void);
void uart0_tx_string(char *ptr);
void uart0_rx_string(char *ptr, int len);

#endif
