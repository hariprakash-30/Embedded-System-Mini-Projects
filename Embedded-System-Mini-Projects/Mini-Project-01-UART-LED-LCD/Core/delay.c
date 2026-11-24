#include <LPC21xx.h>
#include "delay.h"

/* Clock assumption: PCLK = 60 MHz. */
#define TIMER0_PCLK_HZ 60000000UL

void delay_sec(unsigned int sec)
{
    if (sec == 0U)
    {
        return;
    }

    T0TCR = 0x02U; /* Reset Timer0. */
    T0PR = TIMER0_PCLK_HZ - 1UL; /* One TC increment per second. */
    T0TC = 0U;
    T0PC = 0U;
    T0TCR = 0x01U; /* Start Timer0. */

    while (T0TC < sec)
    {
        /* Wait for the requested number of seconds. */
    }

    T0TCR = 0x00U;
}

void delay_ms(unsigned int ms)
{
    if (ms == 0U)
    {
        return;
    }

    T0TCR = 0x02U; /* Reset Timer0. */
    T0PR = (TIMER0_PCLK_HZ / 1000UL) - 1UL; /* One TC increment per ms. */
    T0TC = 0U;
    T0PC = 0U;
    T0TCR = 0x01U; /* Start Timer0. */

    while (T0TC < ms)
    {
        /* Wait for the requested number of milliseconds. */
    }

    T0TCR = 0x00U;
}
