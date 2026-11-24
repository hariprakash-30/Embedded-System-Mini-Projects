#include <LPC21xx.h>
#include "uart_driver.h"

#define UART0_THRE   (1U << 5)
#define UART0_RDR    (1U << 0)

/*
 * Clock assumption: CCLK = 60 MHz and VPBDIV = 1, therefore PCLK = 60 MHz.
 * Update this configuration if the board clock differs.
 */
#define UART0_PCLK_HZ 60000000UL

void uart0_init(unsigned int baud)
{
    unsigned long divisor;

    if (baud == 0U)
    {
        return;
    }

    /* Select TXD0 on P0.0 and RXD0 on P0.1 without changing other pin muxes. */
    PINSEL0 = (PINSEL0 & ~0x0FU) | 0x05U;

    VPBDIV = 0x01U; /* PCLK = CCLK */

    U0LCR = 0x83U; /* Enable divisor latch; 8 data bits, 1 stop, no parity. */

    divisor = UART0_PCLK_HZ / (16UL * baud);
    U0DLL = (unsigned char)(divisor & 0xFFU);
    U0DLM = (unsigned char)((divisor >> 8U) & 0xFFU);

    U0LCR = 0x03U; /* Disable divisor-latch access; retain 8-N-1 format. */
}

void uart0_tx(unsigned char data)
{
    while ((U0LSR & UART0_THRE) == 0U)
    {
        /* Wait until the transmit holding register is empty. */
    }

    U0THR = data;
}

unsigned char uart0_rx(void)
{
    while ((U0LSR & UART0_RDR) == 0U)
    {
        /* Wait until a character is received. */
    }

    return (unsigned char)U0RBR;
}

void uart0_tx_string(char *ptr)
{
    if (ptr == 0)
    {
        return;
    }

    while (*ptr != '\\0')
    {
        uart0_tx((unsigned char)*ptr);
        ptr++;
    }
}

/*
 * Receives at most len characters, stopping at carriage return.
 * Caller must provide a buffer of at least len + 1 bytes.
 */
void uart0_rx_string(char *ptr, int len)
{
    int i;
    unsigned char ch;

    if ((ptr == 0) || (len <= 0))
    {
        return;
    }

    for (i = 0; i < len; i++)
    {
        ch = uart0_rx();

        if (ch == '\\r')
        {
            break;
        }

        ptr[i] = (char)ch;
    }

    ptr[i] = '\\0';
}
