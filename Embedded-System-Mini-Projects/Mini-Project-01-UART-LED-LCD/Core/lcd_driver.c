#include <LPC21xx.h>
#include "lcd_driver.h"
#include "delay.h"

/*
 * 4-bit LCD mapping used by this driver:
 * RS=P1.17, RW=P1.18, EN=P1.19, D4-D7=P1.20-P1.23.
 */

#define LCD_RS   (1U << 17)
#define LCD_RW   (1U << 18)
#define LCD_EN   (1U << 19)
#define LCD_DATA_MASK (0x0FU << 20)
#define LCD_PIN_MASK  (LCD_RS | LCD_RW | LCD_EN | LCD_DATA_MASK)

static void lcd_write_nibble(unsigned char nibble, unsigned char is_data)
{
    unsigned int pins = ((unsigned int)(nibble & 0x0FU) << 20U);

    IOCLR1 = LCD_PIN_MASK;
    IOSET1 = pins;

    if (is_data != 0U)
    {
        IOSET1 = LCD_RS;
    }
    else
    {
        IOCLR1 = LCD_RS;
    }

    /* Write-only operation: RW is held LOW. */
    IOCLR1 = LCD_RW;

    IOSET1 = LCD_EN;
    delay_ms(1U);
    IOCLR1 = LCD_EN;
    delay_ms(1U);
}

void lcd_data(unsigned char data)
{
    lcd_write_nibble((unsigned char)(data >> 4U), 1U);
    lcd_write_nibble((unsigned char)(data & 0x0FU), 1U);
}

void lcd_cmd(unsigned char cmd)
{
    lcd_write_nibble((unsigned char)(cmd >> 4U), 0U);
    lcd_write_nibble((unsigned char)(cmd & 0x0FU), 0U);

    /* Clear/home commands require longer execution time on common HD44780 LCDs. */
    if ((cmd == 0x01U) || (cmd == 0x02U))
    {
        delay_ms(2U);
    }
}

void lcd_init(void)
{
    IODIR1 |= LCD_PIN_MASK;
    PINSEL2 = 0U; /* Configure Port 1 pins as GPIO on supported LPC21xx parts. */

    IOCLR1 = LCD_PIN_MASK;
    delay_ms(20U);

    /*
     * Standard 4-bit initialization sequence.
     * Send raw nibbles while the LCD is in its power-on 8-bit state.
     */
    lcd_write_nibble(0x03U, 0U);
    delay_ms(5U);
    lcd_write_nibble(0x03U, 0U);
    delay_ms(1U);
    lcd_write_nibble(0x03U, 0U);
    delay_ms(1U);
    lcd_write_nibble(0x02U, 0U);

    lcd_cmd(0x28U); /* 4-bit, 2-line, 5x8 font. */
    lcd_cmd(0x0CU); /* Display ON, cursor OFF. */
    lcd_cmd(0x06U); /* Entry mode: increment cursor. */
    lcd_cmd(0x01U); /* Clear display. */
}

void lcd_string(char *ptr)
{
    if (ptr == 0)
    {
        return;
    }

    while (*ptr != '\\0')
    {
        lcd_data((unsigned char)*ptr);
        ptr++;
    }
}
