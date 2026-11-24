#ifndef LCD_DRIVER_H
#define LCD_DRIVER_H

void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_init(void);
void lcd_string(char *ptr);

#endif
