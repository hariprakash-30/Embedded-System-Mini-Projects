#include <LPC21xx.h>
#include "uart_driver.h"
#include "lcd_driver.h"
#include "delay.h"

#define LED_MASK ((1U << 17) | (1U << 18) | (1U << 19))

int main(void)
{
    unsigned char received;
    unsigned int count;
    unsigned int bit_index;
    char binary[4];

    /* Configure P0.17, P0.18 and P0.19 as GPIO outputs. */
    IODIR0 |= LED_MASK;

    /* Active-LOW LEDs: HIGH means OFF. */
    IOSET0 = LED_MASK;

    uart0_init(9600U);
    lcd_init();

    lcd_cmd(0x80);
    lcd_string("UART LED CNTRL");

    while (1)
    {
        received = uart0_rx();
        uart0_tx(received); /* Echo received character to PC. */

        if (received == '1')
        {
            IOCLR0 = LED_MASK;

            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("TURN ON ALL LEDS");
        }
        else if (received == '0')
        {
            IOSET0 = LED_MASK;

            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("TURN OFF ALL LEDS");
        }
        else if (received == '2')
        {
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("LED BIN COUNT");

            for (count = 0U; count <= 7U; count++)
            {
                /* Turn all LEDs OFF before applying the new pattern. */
                IOSET0 = LED_MASK;

                /* Bit 0 -> P0.17, bit 1 -> P0.18, bit 2 -> P0.19. */
                IOCLR0 = ((count << 17U) & LED_MASK);

                for (bit_index = 0U; bit_index < 3U; bit_index++)
                {
                    if ((count & (1U << (2U - bit_index))) != 0U)
                    {
                        binary[bit_index] = '1';
                    }
                    else
                    {
                        binary[bit_index] = '0';
                    }
                }
                binary[3] = '\\0';

                lcd_cmd(0xC0);
                lcd_string("Value: ");
                lcd_string(binary);

                delay_ms(2000U);
            }

            IOSET0 = LED_MASK;
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_string("DONE");
        }
        /* Other received characters are echoed and otherwise ignored. */
    }

    /* Not reached. */
    return 0;
}
